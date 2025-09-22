using System.Text;

namespace Ejercicio_2
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        public static string ToUserMessage(Exception ex)
        {
            return ex switch
            {
                DivideByZeroException => "No se puede dividir por cero.",
                FormatException => "Ingresá números válidos (usa punto decimal si corresponde).",
                FileNotFoundException => "El archivo no existe.",
                UnauthorizedAccessException => "La app no tiene permisos para acceder al archivo.",
                IOException => "Error de entrada/salida al manejar el archivo.",
                HttpRequestException => "Problema de conexión con el servicio. Intentá nuevamente.",
                TaskCanceledException => "La operación tardó demasiado (timeout).",
                ArgumentNullException => "Falta un dato requerido.",
                ArgumentOutOfRangeException => "El valor está fuera del rango permitido.",
                InvalidOperationException => "La operación no es válida en el estado actual.",
                _ => "Ocurrió un error inesperado. Volvé a intentar."
            };
        }
        public static class LogService
        {
            static readonly string LogPath = Path.Combine(FileSystem.AppDataDirectory, "errors.log");

            public static void WriteLine(string text)
            {
                try
                {
                    var line = $"[{DateTime.Now:yyyy-MM-dd HH:mm:ss}] {text}{Environment.NewLine}";
                    // using / IDisposable: libera el FileStream/StreamWriter aunque haya error
                    using var fs = new FileStream(LogPath, FileMode.Append, FileAccess.Write, FileShare.Read);
                    using var sw = new StreamWriter(fs, Encoding.UTF8);
                    sw.Write(line);
                }
                catch
                {
                    // En producción podrías enrutar a otro sink (AppCenter, etc.).
                    System.Diagnostics.Debug.WriteLine("Fallo al escribir log.");
                }
            }

            public static string ReadAll() =>
                File.Exists(LogPath) ? File.ReadAllText(LogPath) : "(sin errores registrados)";
        }

        string FullPath(string file) => Path.Combine(FileSystem.AppDataDirectory, file);

        async void OnGuardarClicked(object sender, EventArgs e)
        {
            try
            {
                var file = FileNameEntry.Text?.Trim();
                if (string.IsNullOrWhiteSpace(file))
                    throw new ArgumentNullException(nameof(file));

                var path = FullPath(file);

                // using/IDisposable: FileStream + StreamWriter
                using var fs = new FileStream(path, FileMode.Create, FileAccess.Write, FileShare.Read);
                using var sw = new StreamWriter(fs, Encoding.UTF8);
                await sw.WriteAsync(TextEditor.Text ?? string.Empty);

                StatusLabel.Text = $"Estado: guardado en {path}";
            }
            catch (Exception ex) when (ex is UnauthorizedAccessException || ex is IOException || ex is ArgumentNullException)
            {
                LogService.WriteLine($"[Guardar] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Error", ToUserMessage(ex), "OK");
            }
        }
        async void OnAbrirClicked(object sender, EventArgs e)
        {
            try
            {
                var file = FileNameEntry.Text?.Trim();
                if (string.IsNullOrWhiteSpace(file))
                    throw new ArgumentNullException(nameof(file));

                var path = FullPath(file);

                // Lanzará FileNotFoundException si no existe (lo capturamos)
                if (!File.Exists(path))
                    throw new FileNotFoundException("No existe", path);

                using var fs = new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
                using var sr = new StreamReader(fs, Encoding.UTF8);
                var content = await sr.ReadToEndAsync();

                TextEditor.Text = content;
                StatusLabel.Text = $"Estado: abierto {path}";
            }
            catch (Exception ex) when (ex is FileNotFoundException || ex is UnauthorizedAccessException || ex is IOException || ex is ArgumentNullException)
            {
                LogService.WriteLine($"[Abrir] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Error", ToUserMessage(ex), "OK");
            }
        }
    }
}

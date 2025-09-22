using System.Text;

namespace Ejercicio_4
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        public static class ExceptionMapper
        {
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
        async void OnArgNullClicked(object sender, EventArgs e)
        {
            try
            {
                string? nombre = null;

                // Prevención (guard):
                if (nombre is null)
                    throw new ArgumentNullException(nameof(nombre), "El nombre es requerido.");

                _ = nombre.Length; // si pasó el guard, no falla
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[ArgNull] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }

        async void OnAoorClicked(object sender, EventArgs e)
        {
            try
            {
                int edad = -3;

                if (edad < 0 || edad > 120)
                    throw new ArgumentOutOfRangeException(nameof(edad), "La edad debe estar entre 0 y 120.");

                _ = edad; // OK si es válido
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[Aoor] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }
        async void OnInvOpClicked(object sender, EventArgs e)
        {
            try
            {
                var cola = new Queue<int>();
                // Prevención: si Count == 0, no se puede Dequeue
                if (cola.Count == 0)
                    throw new InvalidOperationException("No se puede extraer de una cola vacía.");

                _ = cola.Dequeue();
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[InvalidOp] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }
        async void OnFormatClicked(object sender, EventArgs e)
        {
            try
            {
                var texto = "12,34"; // según cultura, puede fallar
                if (!double.TryParse(texto, out var _))
                    throw new FormatException("Formato numérico inválido para la cultura actual.");
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[Format] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }
        async void OnNullClicked(object sender, EventArgs e)
        {
            try
            {
                string? nombre = null;

                if (nombre is null)
                    throw new NullReferenceException("Referencia nula: variable no inicializada.");

                _ = nombre.Length; 
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[NullRef] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }
        async void OnIndexClicked(object sender, EventArgs e)
        {
            try
            {
                var numeros = new[] { 10, 20, 30 };
                int i = 3;

                if (i < 0 || i >= numeros.Length)
                    throw new IndexOutOfRangeException($"Índice {i} fuera de rango (0..{numeros.Length - 1}).");

                _ = numeros[i];
            }
            catch (Exception ex)
            {
                LogService.WriteLine($"[IndexOut] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Demo", ExceptionMapper.ToUserMessage(ex), "OK");
            }
        }
    }
}

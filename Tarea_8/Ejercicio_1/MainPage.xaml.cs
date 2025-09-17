using System.Text;

namespace Ejercicio_1
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
        async void OnCalcularCliked(object sender, EventArgs e)
        {
            try
            {
                // VALIDACIÓN: si TryParse falla, lanzamos FormatException explícita
                if (!double.TryParse(Num1Entry.Text, out var a) ||
                    !double.TryParse(Num2Entry.Text, out var b))
                    throw new FormatException("Entradas no numéricas.");

                var op = OpPicker.SelectedIndex;
                if (op < 0) throw new InvalidOperationException("Seleccioná una operación.");

                double r = op switch
                {
                    0 => a + b,
                    1 => a - b,
                    2 => a * b,
                    3 => b == 0 ? throw new DivideByZeroException() : a / b,
                    4 => a == 0 || b <= 1 ? throw new ArgumentOutOfRangeException() : Math.Pow(a, b),
                    5 => a < 0 ? throw new ArgumentOutOfRangeException() : Math.Sqrt(a),
                    _ => throw new InvalidOperationException("Operación desconocida.")
                };

                ResultLabel.Text = $"Resultado: {r}";
            }
            catch (Exception ex)
            {
                // Log técnico + mensaje seguro
                LogService.WriteLine($"[Calc] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Atención", ExceptionMapper.ToUserMessage(ex), "OK");
            }
            finally
            {
                // Ejemplo de finally: reestablecer UI
                (sender as Button)!.IsEnabled = true;
            }
        }

        async void onVerLogClicked(object sender, EventArgs e)
        {
            await DisplayAlert("Log", LogService.ReadAll(), "OK");
        }
    }
}

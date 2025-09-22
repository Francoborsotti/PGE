using System.Text;

namespace Ejercicio_3
{
    public partial class MainPage : ContentPage
    {
        public sealed class FakeAuthService
        {
            // Simula un “endpoint” remoto con delay y fallas controladas
            public async Task<bool> LoginAsync(string user, string pass, TimeSpan timeout, CancellationToken externalCt = default)
            {
                using var cts = CancellationTokenSource.CreateLinkedTokenSource(externalCt);
                cts.CancelAfter(timeout);

                // Reglas de demo:
                // - user == "timeout" → demora mucho hasta caer en TaskCanceledException
                // - user == "net"     → simular HttpRequestException
                // - resto: válido si pass == "1234"
                try
                {
                    if (user == "timeout")
                        await Task.Delay(TimeSpan.FromSeconds(10), cts.Token);
                    else
                        await Task.Delay(TimeSpan.FromSeconds(1.2), cts.Token);

                    if (user == "net")
                        throw new HttpRequestException("Simulada caída de red/servidor.");

                    return pass == "1234";
                }
                catch (OperationCanceledException oce) when (cts.IsCancellationRequested)
                {
                    // MAUI suele surfacear TaskCanceledException por timeout
                    throw new TaskCanceledException("Timeout simulado", oce);
                }
            }
        }


        readonly FakeAuthService _service = new();
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

        async void OnLoginClicked(object sender, EventArgs e)
        {
            try
            {
                Busy.IsVisible = Busy.IsRunning = true;
                LoginBtn.IsEnabled = false;

                // VALIDACIÓN de dominio (guard clauses)
                var user = UserEntry.Text?.Trim() ?? string.Empty;
                var pass = PassEntry.Text?.Trim() ?? string.Empty;

                if (string.IsNullOrWhiteSpace(user))
                    throw new ArgumentNullException(nameof(user), "Usuario vacío.");
                if (string.IsNullOrWhiteSpace(pass))
                    throw new ArgumentNullException(nameof(pass), "Clave vacía.");
                if (user.Length < 3 || user.Length > 20)
                    throw new ArgumentOutOfRangeException(nameof(user), "Usuario fuera de longitud (3–20).");
                if (pass.Length < 3 || pass.Length > 20)
                    throw new ArgumentOutOfRangeException(nameof(pass), "Clave fuera de longitud (3–20).");

                // “Llamada” remota con timeout de 2.5s
                var ok = await _service.LoginAsync(user, pass, TimeSpan.FromSeconds(2.5));

                ResultLabel.Text = ok ? "Resultado: acceso concedido ✅" : "Resultado: credenciales inválidas ❌";
            }
            catch (Exception ex) when (ex is HttpRequestException || ex is TaskCanceledException || ex is ArgumentNullException || ex is ArgumentOutOfRangeException)
            {
                LogService.WriteLine($"[Login] {ex.GetType().Name} - {ex.Message}");
                await DisplayAlert("Atención", ExceptionMapper.ToUserMessage(ex), "OK");
                ResultLabel.Text = "Resultado: error de comunicación o validación";
            }
            finally
            {
                Busy.IsVisible = Busy.IsRunning = false;
                LoginBtn.IsEnabled = true;
            }
        }

        async void OnException1Clicked(object sender, EventArgs e)
        {

        }

        async void OnException2Clicked(object sender, EventArgs e)
        {

        }
    }
}

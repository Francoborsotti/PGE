namespace MauiApp1
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
        }

        private void OnSaludarClicked(object? sender, EventArgs e)
        {
            var nombre = txtNombre.text?.Trim();
            lblSaludo.text = string.IsNullOrWhiteSpace(nombre) ? "!Hola¡" : $"!Hola, {nombre}¡";
        }
    }
}

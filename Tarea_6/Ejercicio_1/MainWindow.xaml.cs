using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Ejercicio_1
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            double resultado;
            if (double.TryParse(grados.Text, NumberStyles.Float, CultureInfo.InvariantCulture, out resultado))
            {
                mensajeError.Content = "";
                resultado = double.Parse(grados.Text);
                resultado *= 1.8;
                resultado += 32;

                labelResultado.Content = resultado.ToString();
            }
            else
            {
                mensajeError.Content = "Introduzca un número!!";
            }
        }
    }
}

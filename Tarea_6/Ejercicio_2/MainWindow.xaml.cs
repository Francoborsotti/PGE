using System;
using System.Collections.Generic;
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

namespace Ejercicio_2
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool dibujo = false;
        Point ultimoPunto;

        Brush brushSelec()
        {
            var item = (ColorCombo.SelectedItem as ComboBoxItem)?.Content?.ToString() ?? "Negro";

            switch (item)
            {
                case "Rojo":    return Brushes.Red;
                case "Azul":    return Brushes.Blue;
                case "Verde":   return Brushes.Green;
                default:        return Brushes.Black;
            }
        }
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Lienzo_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                dibujo = true;
                ultimoPunto = e.GetPosition(Lienzo);
                Lienzo.CaptureMouse();
            }
        }

        private void Lienzo_MouseMove(object sender, MouseEventArgs e)
        {
            if (!dibujo) return;  // Si no esta Dibujando que no haga nada

            Point actual = e.GetPosition(Lienzo); // Toma la posicion actual del en el Lienzo

            var linea = new Line  // Creo la linea
            {
                X1 = ultimoPunto.X,
                Y1 = ultimoPunto.Y,
                X2 = actual.X,
                Y2 = actual.Y,
                Stroke = brushSelec(),
                StrokeThickness = GrosorSlider.Value
            };

            Lienzo.Children.Add(linea);
            ultimoPunto = actual;
        }

        private void Lienzo_MouseUp(object sender, MouseButtonEventArgs e)
        {
            dibujo = false;   // Termino de dibujar
            Lienzo.ReleaseMouseCapture();   // Dejo de capturar el mouse
        }

        private void Lienzo_MouseLeave(object sender, MouseEventArgs e)
        {
            if (dibujo)  // Si el mouse deja el Lienzo se deja de dibujar
            {
                dibujo = false;
                Lienzo.ReleaseMouseCapture();
            }
        }

        private void BtnLimpiar_Click(object sender, RoutedEventArgs e)
        {
            Lienzo.Children.Clear(); // Limpio el Lienzo luego de pulsar el boton
        }
    }
}

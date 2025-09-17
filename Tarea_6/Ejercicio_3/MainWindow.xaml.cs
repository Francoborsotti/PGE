using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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

namespace Ejercicio_3
{
    public class Gasto
    {
        public string Descripcion { get; set; } 
        public double Monto { get; set; }         // Moneda
    }
    public partial class MainWindow : Window
    {
        // Lista del listBox
        private readonly ObservableCollection<Gasto> _gastos = new ObservableCollection<Gasto>();

        private readonly Dictionary<string, double> _tasas = new Dictionary<string, double>
        {
            { "Pesos Argentinos", 1.0 }, // Identidad
            { "Dolares",          0.0012 },
            { "Euros",            0.0011 }
        };

        public MainWindow()
        {
            InitializeComponent();
            listaGastos.ItemsSource = _gastos;
        }

        private void btnAgregar_Click(object sender, RoutedEventArgs e)
        {
            // 1) Validar descripción
            string desc = (txtDesc.Text ?? "").Trim();
            if (string.IsNullOrWhiteSpace(desc))
            {
                MessageBox.Show("Ingresá una descripción.", "Validación",
                                MessageBoxButton.OK, MessageBoxImage.Warning);
                txtDesc.Focus(); return;
            }

            // 2) Validar monto (acepta punto o coma según tu Windows)
            // Si querés obligar a punto, usa CultureInfo.InvariantCulture.
            if (!double.TryParse(txtMonto.Text, NumberStyles.Float, CultureInfo.CurrentCulture, out double monto) || monto <= 0)
            {
                MessageBox.Show("Ingresá un monto numérico mayor a 0.", "Validación",
                                MessageBoxButton.OK, MessageBoxImage.Warning);
                txtMonto.Focus(); txtMonto.SelectAll(); return;
            }

            // 3) Agregar a la lista
            _gastos.Add(new Gasto { Descripcion = desc, Monto = monto });

            // 4) Limpiar inputs
            txtDesc.Clear();
            txtMonto.Clear();
            txtDesc.Focus();
        }

        private void btnConvertir_Click(object sender, RoutedEventArgs e)
        {
            if (_gastos.Count == 0)
            {
                MessageBox.Show("No hay gastos cargados.", "Conversión",
                                MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            // Sumar total en moneda local
            double totalLocal = _gastos.Sum(g => g.Monto);

            // Tomar moneda destino del combo
            var item = cboMonedaDestino.SelectedItem as ComboBoxItem;
            string nombreMoneda = item?.Content?.ToString() ?? "Pesos Argentinos";

            // Buscar tasa
            if (!_tasas.TryGetValue(nombreMoneda, out double tasa))
            {
                MessageBox.Show("Moneda destino no soportada.", "Conversión",
                                MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            double totalConvertido = totalLocal * tasa;

            // Mostrar (formateo con separadores y 2 decimales)
            string localStr = totalLocal.ToString("N2", CultureInfo.CurrentCulture);
            string convStr = totalConvertido.ToString("N2", CultureInfo.CurrentCulture);

            lResultado.Content = $"Total local: {localStr}  |  Total convertido: {convStr} {nombreMoneda}";
        }
    }
}


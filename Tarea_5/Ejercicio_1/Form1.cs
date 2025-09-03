using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ejercicio_1
{
    public partial class Form1 : Form
    {
        private Timer timer;
        int selector = 0;
        public Form1()
        {
            InitializeComponent();

            // Crear y configurar el Timer
            timer = new Timer();
            timer.Interval = 5000; // 5000 ms = 5 segundos
            timer.Tick += Timer_Tick;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "Cargando..."; 
            selector = 0;
            timer.Start();
        }
        private void Timer_Tick(object sender, EventArgs e)
        {
            timer.Stop(); // detener el Timer (para que no se repita)
            switch (selector)
            {
                case 0:
                    {
                        label1.Text = "Texto de ejemplo para la sección Contenidos";
                    }
                    break;
                case 1:
                    {
                        label1.Text = "Texto de ejemplo para la sección Examenes";
                    }
                    break;
                case 2:
                    {
                        label1.Text = "Texto de ejemplo para la sección Docentes";
                    }
                    break;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            label1.Text = "Cargando...";
            selector = 1;
            timer.Start();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            label1.Text = "Cargando...";
            selector = 2;
            timer.Start();
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}

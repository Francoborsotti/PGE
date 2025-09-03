using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ejercicio_flash
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "Lunes";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            label1.Text = "Martes";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            label1.Text = "Miercoles";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            label1.Text = "Jueves";
        }

        private void button5_Click(object sender, EventArgs e)
        {
            label1.Text = "Viernes";
        }

        private void button6_Click(object sender, EventArgs e)
        {
            label1.Text = "Sabado";
        }

        private void button7_Click(object sender, EventArgs e)
        {
            label1.Text = "Domingo";
        }
    }
}

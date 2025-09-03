using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Ejercicio_6
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "La suma es igual a :";
            int num1 = int.Parse(textBox1.Text);
            int num2 = int.Parse(textBox2.Text);
            label1.Text += (num1 +  num2).ToString();
        }
    }
}

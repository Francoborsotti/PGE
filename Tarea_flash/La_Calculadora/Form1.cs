using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace La_Calculadora
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        int num1 = 0;
        int num2 = 0;
        int operacion = 0;

        private void button3_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "1";
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "2";
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "0";
            }
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "3";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "4";
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "5";
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "6";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "7";
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "8";
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += "9";
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (label1.Text.Length < 12)
            {
                label1.Text += ".";
            }
        }
        //suma
        private void button16_Click(object sender, EventArgs e)
        {
            num1 = int.Parse(label1.Text);
            label1.Text = null;
            operacion = 1;
        }
        //resta
        private void button15_Click(object sender, EventArgs e)
        {
            num1 = int.Parse(label1.Text);
            label1.Text = null;
            operacion = 2;
        }
        //multiplicacion
        private void button14_Click(object sender, EventArgs e)
        {
            num1 = int.Parse(label1.Text);
            label1.Text = null;
            operacion = 3;
        }
        //division
        private void button13_Click(object sender, EventArgs e)
        {
            num1 = int.Parse(label1.Text);
            label1.Text = null;
            operacion = 4;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            num2 = int.Parse(label1.Text);
            label1.Text = null;
            switch (operacion)
            {
                case 1:
                    {
                        label1.Text = (num1 + num2).ToString();
                    }
                    break;
                case 2:
                    {
                        label1.Text = (num1 - num2).ToString();
                    }
                    break;
                case 3:
                    {
                        label1.Text = (num1 * num2).ToString();
                    }
                    break;
                case 4:
                    {
                        label1.Text = (num1 / num2).ToString();
                    }
                    break;
            }
        }

        private void button17_Click(object sender, EventArgs e)
        {
            label1.Text = null;
            num1 = 0;
            num2 = 0;
        }
    }
}

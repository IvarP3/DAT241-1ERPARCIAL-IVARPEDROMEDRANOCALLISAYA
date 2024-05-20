using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication3
{
    public partial class Form2 : Form
    {
        double n, d;
        String c;

        public Form2()
        {
            InitializeComponent();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if(textBox1.Text == "0")
                textBox1.Text = null;
            Button boton = (Button)sender;
            string contenidoBoton = boton.Text;

            if (textBox1.Text.Length > 0)
            {
                char ultimoCaracter = textBox1.Text[textBox1.Text.Length - 1];
                if (EsOperador(ultimoCaracter) && EsOperador(contenidoBoton[0]))
                {
                    return;
                }
            }

            if (contenidoBoton == "." && textBox1.Text.Contains("."))
            {
                return;
            }

            if (contenidoBoton == ")")
            {
                textBox1.Text += contenidoBoton;
                return;
            }

            if (contenidoBoton == "(")
            {
                if (textBox1.Text.Length > 0)
                {
                    char ultimoCaracter = textBox1.Text[textBox1.Text.Length - 1];
                    if (char.IsDigit(ultimoCaracter))
                    {
                        textBox1.Text += "*";
                    }
                }
            }

            if (contenidoBoton == "^")
            {
                if (textBox1.Text.Length > 0)
                {
                    char ultimoCaracter = textBox1.Text[textBox1.Text.Length - 1];
                    if (char.IsDigit(ultimoCaracter))
                    {
                        textBox1.Text += "^";
                    }
                }
            }

            c = textBox1.Text + contenidoBoton;
            textBox1.Text += contenidoBoton;
        }
        private void button12_Click(object sender, EventArgs e)
        {
            c = n.ToString() + ((Button)sender).Text;
            n = Convert.ToDouble(c+0);
            textBox1.Text = c;
        }
        private void button13_Click(object sender, EventArgs e)
        {
            textBox1.Text = null;
        }
        private void button14_Click(object sender, EventArgs e)
        {
            string expresion = c;
            double resultado = EvaluarExpresion(expresion);
            textBox1.Text = resultado.ToString();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            n = 0;
            textBox1.Text = n.ToString();
        }
        private int Precedencia(char operador)
        {
            switch (operador)
            {
                case '+':
                    return 1;
                case '-':
                    return 1;
                case '*':
                    return 2;
                case '/':
                    return 2;
                case '^':
                    return 3;
                default:
                    return -1;
            }
        }

        private bool EsOperador(char caracter)
        {
            return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^');
        }

        private double AplicarOperador(double operando1, double operando2, char operador)
        {
            switch (operador)
            {
                case '+':
                    return operando1 + operando2;
                case '-':
                    return operando1 - operando2;
                case '*':
                    return operando1 * operando2;
                case '/':
                    if (operando2 != 0)
                        return operando1 / operando2;
                    else
                        throw new ArgumentException("División por cero");
                case '^':
                    return Math.Pow(operando1, operando2);
                default:
                    throw new ArgumentException("Operador no válido");
            }
        }

        private double EvaluarExpresion(string expresion)
        {
            Stack<double> pila = new Stack<double>();

            for (int i = 0; i < expresion.Length; i++)
            {
                char caracter = expresion[i];

                if (char.IsDigit(caracter) || caracter == '.')
                {
                    string numero = caracter.ToString();

                    while (i + 1 < expresion.Length && (char.IsDigit(expresion[i + 1]) || expresion[i + 1] == '.'))
                    {
                        numero += expresion[i + 1];
                        i++;
                    }

                    pila.Push(double.Parse(numero));
                }
                else if (caracter == '(')
                {
                    pila.Push((double)caracter); 
                }
                else if (caracter == ')')
                {
                    while (pila.Peek() != '(')
                    {
                        double operando2 = pila.Pop();
                        char operador = (char)pila.Pop();
                        double operando1 = pila.Pop();
                        pila.Push(AplicarOperador(operando1, operando2, operador));
                    }
                    pila.Pop();
                }
                else if (EsOperador(caracter))
                {
                    while (pila.Count > 0 && pila.Peek() != '(' && Precedencia(caracter) <= Precedencia((char)pila.Peek()))
                    {
                        double operando2 = pila.Pop();
                        char operador = (char)pila.Pop();
                        double operando1 = pila.Pop();
                        pila.Push(AplicarOperador(operando1, operando2, operador));
                    }
                    pila.Push((double)caracter);
                }
            }

            while (pila.Count > 1)
            {
                double operando2 = pila.Pop();
                char operador = (char)pila.Pop();
                double operando1 = pila.Pop();
                pila.Push(AplicarOperador(operando1, operando2, operador));
            }

            return pila.Pop();
        }

    }
}

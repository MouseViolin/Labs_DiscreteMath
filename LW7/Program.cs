using System;
using System.IO;

namespace LW7
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] matrix = LoadMatrixFromFile("/Users/user/Documents/Labs_DiscreteMath/LW7/g41.txt");

            Shimbell shimbell = new Shimbell(matrix);

            Console.Write("Введите количество переходов: ");
            int steps = int.Parse(Console.ReadLine());

            Console.Write("Искать минимальные пути? (да/нет): ");
            string mode = Console.ReadLine().ToLower();

            bool findMinimum = mode == "да" || mode == "y" || mode == "yes";

            shimbell.ComputePaths(steps, findMinimum);
        }

        static int[,] LoadMatrixFromFile(string filePath)
        {
            string[] lines = File.ReadAllLines(filePath);
            int size = lines.Length;
            int[,] matrix = new int[size, size];

            for (int i = 0; i < size; i++)
            {
                string[] values = lines[i].Split(' ');
                for (int j = 0; j < size; j++)
                {
                    matrix[i, j] = int.Parse(values[j]);
                }
            }

            return matrix;
        }
    }
}
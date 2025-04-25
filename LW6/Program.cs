using System;
using System.IO;

namespace LW6
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] matrix = LoadMatrixFromFile("/Users/user/Documents/Labs_DiscreteMath/LW6/matrix3.txt");
            
            SpanningTree spanningTree = new SpanningTree(matrix);
            spanningTree.FindMinimumSpanningTree();
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
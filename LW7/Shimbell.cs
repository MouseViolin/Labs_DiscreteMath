using System;

namespace LW7
{
    public class Shimbell
    {
        private int[,] graph;
        private int size;
        

        public Shimbell(int[,] matrix)
        {
            graph = matrix;
            size = graph.GetLength(0);
        }

        public void ComputePaths(int steps, bool findMinimum = true)
        {
            int[,] A1 = graph;

            int[,] result = (int[,])A1.Clone();

            for (int s = 1; s < steps; s++)
            {
                result = Multiply(result, A1, findMinimum);
            }

            Console.WriteLine($"\nМатрица значений для {steps} переходов ({(findMinimum ? "Минимальные" : "Максимальные")} пути):");
            PrintMatrix(result);
        }

        private int[,] Multiply(int[,] A, int[,] B, bool findMinimum)
        {
            int[,] result = new int[size, size];

            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {

                    
                    int temp = findMinimum ? int.MaxValue : int.MinValue;
                    bool hasValidValue = false;

                    for (int k = 0; k < size; k++)
                    {
                        int value = (A[i, k] == 0 || B[k, j] == 0)?  0 : A[i, k] + B[k, j];

                        if (value != 0)
                        {
                            temp = findMinimum ? Math.Min(temp, value) : Math.Max(temp, value);
                            hasValidValue = true;
                        }
                        
                    }

                    result[i, j] = hasValidValue ? temp : 0;
                }
            }

            return result;
        }

        private void PrintMatrix(int[,] matrix)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                        Console.Write(matrix[i, j] + "\t");
                }
                Console.WriteLine();
            }
        }
    }
}
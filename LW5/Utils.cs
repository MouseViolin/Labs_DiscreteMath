using System;
using System.IO;

namespace ComponentFinder
{
    public static class Utils
    {
        public static class MatrixReader
        {
            public static int[,] ReadMatrixFromFile(string filePath)
            {
                if (!File.Exists(filePath))
                    throw new FileNotFoundException("Файл не найден!", filePath);

                string[] lines = File.ReadAllLines(filePath);
                return ConvertLinesToMatrix(lines);
            }

            public static int[,] ReadMatrixFromString(string input)
            {
                string[] lines = input.Split(new[] { '\n', '\r' }, StringSplitOptions.RemoveEmptyEntries);
                return ConvertLinesToMatrix(lines);
            }

            private static int[,] ConvertLinesToMatrix(string[] lines)
            {
                int size = lines.Length;
                int[,] matrix = new int[size, size];

                for (int i = 0; i < size; i++)
                {
                    string[] elements = lines[i].Split(' ');
                    if (elements.Length != size)
                        throw new FormatException("Матрица должна быть квадратной!");

                    for (int j = 0; j < size; j++)
                    {
                        if (!int.TryParse(elements[j], out matrix[i, j]) || (matrix[i, j] != 0 && matrix[i, j] != 1))
                            throw new FormatException("Матрица должна содержать только 0 и 1!");
                    }
                }

                return matrix;
            }
        }
        
    }
}
using System;
using System.Collections.Generic;

namespace LW6
{
    public class SpanningTree
    {
        private int[,] matrix;
        private int size;

        public SpanningTree(int[,] args)
        {
            matrix = args;
            size = matrix.GetLength(0);
        }

        public void FindMinimumSpanningTree()
        {
            bool[] selected = new bool[size];
            List<(int, int, int)> edges = new List<(int, int, int)>();
            selected[0] = true;
            
            for (int edgeCount = 0; edgeCount < size - 1; edgeCount++)
            {
                int min = int.MaxValue;
                int x = -1, y = -1;
                
                for (int i = 0; i < size; i++)
                {
                    if (selected[i])
                    {
                        for (int j = 0; j < size; j++)
                        {
                            if (!selected[j] && matrix[i, j] > 0 && matrix[i, j] < min)
                            {
                                min = matrix[i, j];
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
                
                if (x != -1 && y != -1)
                {
                    edges.Add((x, y, min));
                    selected[y] = true;
                }
            }

            PrintSpanningTree(edges);
        }

        private void PrintSpanningTree(List<(int, int, int)> edges)
        {
            int totalWeight = 0;
            Console.WriteLine("Edges in the Minimum Spanning Tree:");
            foreach (var (u, v, weight) in edges)
            {
                Console.WriteLine($"{u} - {v} : {weight}");
                totalWeight += weight;
            }
            Console.WriteLine($"Total Weight of MST: {totalWeight}");
        }
    }
}

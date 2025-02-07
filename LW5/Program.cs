using ComponentFinder;
using System;
class Program{
    static void Main(string[] args){
        string filePath = "/Users/user/Documents/Labs_DiscreteMath/LW5/matrix.txt"; 
        try
        {
            int[,] matrix = Utils.MatrixReader.ReadMatrixFromFile(filePath); 
            ConnectedComponentFinder finder = new ConnectedComponentFinder(matrix); 
            
            Console.WriteLine("Исходная матрица смежности:");
            finder.PrintMatrix();

            finder.NormalizeGraph();
            Console.WriteLine("\nНормализованная матрица смежности:");
            finder.PrintMatrix();

            finder.FindConnectedComponents();
            finder.BuildReachabilityMatrix();

            Console.WriteLine("\nМатрица достижимости:");
            finder.PrintReachabilityMatrix();

            finder.PrintComponents();


        }
        catch (Exception ex)
        {
            Console.WriteLine("Ошибка: " + ex.Message);
        }
    }
}
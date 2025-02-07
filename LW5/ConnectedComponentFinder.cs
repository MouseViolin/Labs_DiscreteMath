
namespace ComponentFinder
{
    public class ConnectedComponentFinder{

        protected int[,] matrix;
        protected int[,] reachabilityMatrix;
        protected bool[] visited;
        protected List<List<int>> components = new List<List<int>>();

        public int [,] Matrix{ 
            get => matrix;
            set => matrix = value ?? throw new ArgumentNullException(nameof(value));
        }
        // public int this[int i, int j]
        // { 
        //     get => matrix[i, j];
        //     set => matrix[i, j] = value;
        // }

        public ConnectedComponentFinder(int[,] args){
            Matrix = args;
        }
        public ConnectedComponentFinder(){
            matrix = new int[0, 0];
        }

        public void PrintMatrix()
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write(matrix[i, j] + " ");
                }
                Console.WriteLine();
            }  
        }
        public void PrintReachabilityMatrix()
        {
            int rows = reachabilityMatrix.GetLength(0);
            int cols = reachabilityMatrix.GetLength(1);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write(reachabilityMatrix[i, j] + " ");
                }
                Console.WriteLine();
            }  
        }
        public void PrintComponents()
        {
            Console.WriteLine($"\nКоличество компонент связности: {components.Count}");
            for (int i = 0; i < components.Count; i++)
            {
                Console.WriteLine($"Компонента {i + 1}: {string.Join(", ", components[i])}");
            }
        }
        public void NormalizeGraph()
        {
            int size = matrix.GetLength(0);
            for (int i = 0; i < size; i++)
            {
                if (matrix[i, i] == 1) 
                    matrix[i, i] = 0;
                for (int j = 0; j < size; j++)
                {
                    if (matrix[i, j] == 1 || matrix[j, i] == 1)
                    {
                        matrix[i, j] = 1;
                        matrix[j, i] = 1;
                    }
                }
            }
        }
        public void FindConnectedComponents()
        {
            int size = matrix.GetLength(0);
            visited = new bool[size];
            for (int i = 0; i < size; i++)
            {
                if (!visited[i])
                {
                    List<int> component = new List<int>();
                    DFS(i, component);
                    components.Add(component);
                }
            }
        }
        protected void DFS(int v, List<int> component)
        {
            visited[v] = true;
            component.Add(v);
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                if (matrix[v, i] == 1 && !visited[i])
                {
                    DFS(i, component);
                }
            }
        }

        public void BuildReachabilityMatrix()
        {
            int size = matrix.GetLength(0);
            reachabilityMatrix = new int[size, size];
            
            for (int i = 0; i < size; i++)
            {
                bool[] tempVisited = new bool[size];
                DFSForReachability(i, tempVisited);
                for (int j = 0; j < size; j++)
                {
                    reachabilityMatrix[i, j] = tempVisited[j] ? 1 : 0;
                }
            }
        }

        // DFS для построения матрицы достижимости
        protected void DFSForReachability(int v, bool[] tempVisited)
        {
            int size = matrix.GetLength(0);
            tempVisited[v] = true;
            for (int i = 0; i < size; i++)
            {
                if (matrix[v, i] == 1 && !tempVisited[i])
                {
                    DFSForReachability(i, tempVisited);
                }
            }
        }


    }
}
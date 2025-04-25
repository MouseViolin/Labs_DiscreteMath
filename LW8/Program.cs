using System;

class Automaton
{
    static int[,] transitions = new int[5, 4]
    {
       
        { 4, 4, 1, 4 }, // 0 — начальное
        { 4, 4, 2, 4 }, // 1 — ловушка после первой c
        { 2, 3, 2, 2 }, // 2 — после cc, четное b
        { 3, 2, 3, 3 }, // 3 — после cc, нечетное b
        { 4, 4, 4, 4 }  // 4 — ловушка
    };

    static int CharToIndex(char ch)
    {
        return ch switch
        {
            'a' => 0,
            'b' => 1,
            'c' => 2,
            'd' => 3,
            _ => -1
        };
    }

    static bool IsAccepted(string word)
    {
        int state = 0;
        foreach (char ch in word)
        {
            int index = CharToIndex(ch);
            if (index == -1)
            {
                Console.WriteLine($"Недопустимый символ: {ch}");
                return false;
            }

            state = transitions[state, index];
        }

        return state == 2;
    }

    static void Main()
    {
        while (true)
        {
            Console.Write("Введите слово (или 0 для выхода): ");
            string input = Console.ReadLine();

            if (input == "0")
            {
                Console.WriteLine("Выход из программы.");
                break;
            }

            bool result = IsAccepted(input);
            Console.WriteLine(result ? "Слово принадлежит языку (YES)" : "Слово НЕ принадлежит языку (NO)");
            Console.WriteLine(); 
        }
    }
}
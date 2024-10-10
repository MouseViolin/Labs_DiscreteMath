#include "miltitude.h"
#include <iostream>

int main() {
  srand((unsigned int)time(0));

  int quantity;
  Multitude test;

  std::cout << "Укажите количество множеств" << std::endl;
  std::cin >> quantity;
  // test.changeSign(1);
  for (int i(0); i < quantity; i++) {

    std::cout << "Укажите кратность чисел: \n";
    int mult;
    std::cin >> mult;
    test.changeMultipl(mult);

    int sign;
    std::cout << "Укажите знак: 0 - '+/-', 1 - '+', 2 - '-' \n";
    std::cin >> sign;
    test.changeSign(sign);

    bool inp;
    std::cout << "Способ заполенения: 0 - ручной, 1 - автоматический \n";
    std::cin >> inp;
    switch (inp) {
    case 0: {
      std::cin >> test;
      break;
    }
    case 1: {
      int dimensionArray;
      std::cout
          << "Размерность множества: (Максимальное количество значений = 101) "
          << std::endl;
      std::cin >> dimensionArray;
      test.setMultitude(dimensionArray);
    }
    }
    // test.setMultitude(5);

    // std::cin >> test;
    std::cout << "\033[2J\033[1;1H";
  }
  // test.setMultitude(10);
  std::cout << std::endl;
  std::cout << test;
  std::cout << std::endl;

  int change;
  std::cout
      << "Выберете действие: \n0 - ввод формулы \n 1 - Объединение \n 2 - "
         "Пересечение \n 3 - Разность \n 4 - Сим.Разность \n 5 - Дополнение "
         "\n> ";
  std::cin >> change;
  switch (change) {
  case 0: {
    test.specifyingFormula();
    break;
  }
  case 1: {
    test.callCombining(0, 1);
    break;
  }
  case 2: {
    test.callIntersection(0, 1);
    break;
  }
  case 3: {
    test.callDifference(0, 1);
    break;
  }
  case 4: {
    test.callSymDifference(0, 1);
    break;
  }
  case 5: {
    test.callAddToUn(0);
    break;
  }
  }

  // test.specifyingFormula();
  // test.callCombining(0, 1);
  // test.callIntersection(0, 1);
  // test.callDifference(0, 1);
  // test.printMultitude(1);
  return 0;
}

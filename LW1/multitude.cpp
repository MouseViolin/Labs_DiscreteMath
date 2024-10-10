#include "miltitude.h"
#include <iostream>
#include <ostream>
#include <set>
#include <vector>

bool Multitude::isInUniverse(int num) {
  if (UNIVERSE[num - (-50)] == num)
    return 1;
  return 0;
}

bool Multitude::checkingDuplicate(int num) {
  if (occurrenceTracker[num - (-50)] == 0) {
    occurrenceTracker[num - (-50)] += 1;
    return 0;
  } else
    return 1;
}

std::ostream &operator<<(std::ostream &out, const Multitude &a) {
  if (a.vecOfArrays.size() == 0)
    out << "Empty" << std::endl;

  // NOTE: Можно дополнить (ради красоты) с помощью f-строк, дабы указывать
  // номер множества. Если печатать в отсортированном виде, тогда использовать
  // метод итераторов
  std::string alpha = "abcdefghijklmnopqrstuvwxyz";
  for (int i(0); i < a.vecOfArrays.size(); i++) {
    std::cout << alpha[i] << ": ";
    if (a.vecOfArrays[i].empty())
      std::cout << "{}";
    for (int j(0); j < a.vecOfArrays[i].size(); j++)
      out << a.vecOfArrays[i][j] << ' ';
    out << std::endl;
  }

  return out;
}

std::istream &operator>>(std::istream &in, Multitude &a) {
  std::vector<int> tmp;
  int dimensionArray;
  int var;

  std::cout
      << "Размерность множества: (Максимальное количество значений = 101) "
      << std::endl;
  std::cin >> dimensionArray;

  for (int i(0); i < dimensionArray && i < 101; i++) {
  start_input:
    std::cout << "Введите значения множества:" << std::endl;

    while (!(in >> var)) { // Пока ввод не является числом
      in.clear();          // Очищаем состояние ошибки
      in.ignore(std::numeric_limits<std::streamsize>::max(),
                '\n'); // Игнорируем некорректный ввод
      std::cout << "Ошибка! Введите именно число: ";
    }
    if (a.isInUniverse(var) && !a.checkingDuplicate(var) &&
        a.isMultiplicity(var) && a.isSign(var))
      tmp.push_back(var);
    else {
      std::cout << "Ошибка! Число нарушает условия. "
                   "Попробуйте снова.\n";
      goto start_input; // Переход обратно для повторного ввода
    }
  }
  a.vecOfArrays.push_back(tmp);
  a.resetArrTracker();
  a.changeMultipl(1);
  a.changeSign(0);
  return in;
}

void Multitude::resetArrTracker() {
  for (int i(0); i < 101; i++)
    occurrenceTracker[i] = 0;
}

void Multitude::printMultitude(int indx) {
  for (int i(0); i < vecOfArrays[indx].size(); i++)
    std::cout << vecOfArrays[indx][i] << ' ';
  std::cout << std::endl;
}

std::vector<int> Multitude::difference(std::vector<int> a, std::vector<int> b) {
  std::vector<int> result;
  for (int i : a) {
    if (std::find(b.begin(), b.end(), i) == b.end()) {
      result.push_back(i);
    }
  }

  return result;
}

std::vector<int> Multitude::intersection(std::vector<int> a,
                                         std::vector<int> b) {
  std::vector<int> result;
  for (int i : a) {
    if (std::find(b.begin(), b.end(), i) != b.end()) {
      result.push_back(i);
    }
  }
  return result;
}

std::vector<int> Multitude::combining(std::vector<int> a, std::vector<int> b) {
  std::set<int> result_set;
  for (int element : a) {
    result_set.insert(element);
  }

  for (int element : b) {
    result_set.insert(element);
  }

  std::vector<int> result(result_set.begin(), result_set.end());

  return result;
}

std::vector<int> Multitude::symDifference(std::vector<int> a,
                                          std::vector<int> b) {
  std::set<int> set_a(a.begin(), a.end());
  std::set<int> set_b(b.begin(), b.end());
  std::vector<int> result;

  // Добавляем элементы, которые есть в a, но нет в b
  for (int elem : set_a) {
    if (set_b.find(elem) == set_b.end()) {
      result.push_back(elem);
    }
  }

  // Добавляем элементы, которые есть в b, но нет в a
  for (int elem : set_b) {
    if (set_a.find(elem) == set_a.end()) {
      result.push_back(elem);
    }
  }

  return result;
}
std::vector<int> Multitude::additionToUniverse(std::vector<int> _) {
  std::vector<int> result;
  for (int i : UNIVERSE) {
    if (std::find(_.begin(), _.end(), i) == _.end()) {
      result.push_back(i);
    }
  }
  return result;
}
void Multitude::callIntersection(int numA, int numB) {
  std::cout << "Пересечение множеств (A ∩ B): ";
  if (intersection(vecOfArrays[numA], vecOfArrays[numB]).empty())
    std::cout << "{} \n";
  for (int element : intersection(vecOfArrays[numA], vecOfArrays[numB])) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void Multitude::callDifference(int numA, int numB) {
  std::cout << "Разница множеств (A \\ B): ";
  if (difference(vecOfArrays[numA], vecOfArrays[numB]).empty())
    std::cout << "{} \n";

  for (int element : difference(vecOfArrays[numA], vecOfArrays[numB])) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void Multitude::callCombining(int numA, int numB) {
  std::cout << "Объединение множеств (A U B): ";
  if (combining(vecOfArrays[numA], vecOfArrays[numB]).empty())
    std::cout << "{} \n";

  for (int element : combining(vecOfArrays[numA], vecOfArrays[numB])) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void Multitude::callSymDifference(int numA, int numB) {
  std::cout << "Симметрическая разность множеств (A Δ B): ";
  if (symDifference(vecOfArrays[numA], vecOfArrays[numB]).empty())
    std::cout << "{} \n";

  for (int element : symDifference(vecOfArrays[numA], vecOfArrays[numB])) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

void Multitude::callAddToUn(int _) {
  std::cout << "Дополнение множества A: ";
  if (additionToUniverse(vecOfArrays[_]).empty())
    std::cout << "{} \n";

  for (int element : additionToUniverse(vecOfArrays[_])) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
}

std::vector<int>
Multitude::evaluateFormula(const std::string &formula,
                           const std::map<char, std::vector<int>> &sets) {
  std::stack<std::vector<int>> operands;
  std::stack<std::string> operators; // Используем std::string для операторов

  auto apply_operator = [&]() {
    std::string op = operators.top();
    operators.pop();
    auto b = operands.top();
    operands.pop();

    // Для операций, которым требуется два операнда
    if (op == "+" || op == "*" || op == "-" || op == "/") {
      auto a = operands.top();
      operands.pop();

      if (op == "+") {
        operands.push(combining(a, b));
      } else if (op == "*") {
        operands.push(intersection(a, b));
      } else if (op == "-") {
        operands.push(difference(a, b));
      } else if (op == "/") {
        operands.push(symDifference(a, b));
      }
    }
    // Для унарных операторов, таких как дополнение (~)
    else if (op == "~") {
      operands.push(additionToUniverse(b));
    }
  };

  for (char ch : formula) {
    if (std::isalpha(ch)) {
      operands.push(sets.at(ch));
    } else if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '~') {
      operators.push(std::string(1, ch)); // Преобразуем char в строку
    } else if (ch == '(') {
      operators.push("(");
    } else if (ch == ')') {
      while (!operators.empty() && operators.top() != "(") {
        apply_operator();
      }
      operators.pop(); // Удалить '('
    }
  }

  while (!operators.empty()) {
    apply_operator();
  }

  return operands.top();
}
void Multitude::specifyingFormula() {
  std::cout << "+ - Объединение \n"
               "* - Пересечение \n- - Разность \n/  - Сим.Разность \n~ - "
               "Дополнение\n";
  std::cout << "Введите строку: " << std::endl;
  std::string formula;
  std::cin >> formula;

  std::string alpha = "abcdefghijklmnopqrstuvwxyz";
  std::map<char, std::vector<int>> sets;
  // sets['a'] = {1, 2, 3};
  // sets['b'] = {3, 4};
  for (int i(0); i < vecOfArrays.size(); i++)
    sets[alpha[i]] = vecOfArrays[i];

  std::vector<int> result = evaluateFormula(formula, sets);

  std::cout << "Результат: ";
  for (int elem : result) {
    std::cout << elem << " ";
  }
  if (result.empty())
    std::cout << "{}";
  std::cout << std::endl;
}

bool Multitude::isMultiplicity(int num) {
  if (num % multipl == 0)
    return true;
  return false;
}

void Multitude::changeMultipl(int _) { multipl = _; }

bool Multitude::isSign(int num) {
  if (sign == 0)
    return true;
  if (sign == 1) {
    if (num >= 0)
      return true;
    return false;
  }
  if (sign == 2) {
    if (num <= 0)
      return true;
    return false;
  }
  return false;
}

void Multitude::changeSign(int _) {
  if (0 <= _ && _ <= 2) {
    sign = _;
  }
}

void Multitude::setMultitude(int size) {
  int min = -50;
  int max = 50;
  std::vector<int> tmp;

  // std::srand(std::time(0));

  while (tmp.size() != size) {
    int randomNum = min + std::rand() % (max - min + 1);
    if (isInUniverse(randomNum) && !checkingDuplicate(randomNum) &&
        isMultiplicity(randomNum) && isSign(randomNum)) {
      tmp.push_back(randomNum);
      std::cout << randomNum << ' ';
    }
  }

  vecOfArrays.push_back(tmp);
  resetArrTracker();
  changeMultipl(1);
  changeSign(0);
}

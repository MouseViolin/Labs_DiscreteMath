#include "completeness.h"
#include <iostream>
#include <string>
#include <vector>

void Completeness::readVectors() {
  size_t cnt;
  std::cout << "Введите количество функций" << std::endl;
  std::cin >> cnt;

  for (int i(0); i < cnt; i++) {
    std::string tmp;
    std::cin >> tmp;
    vectorOfVectors.push_back(tmp);
  }
}

bool Completeness::checkT0(std::string vector) {

  if (vector[0] == '0')
    return true;
  return false;
}

bool Completeness::checkT1(std::string vector) {
  if (vector[vector.size() - 1] == '1')
    return true;
  return false;
}

bool Completeness::checkS(std::string vector) {
  for (int i(0); i < vector.size() / 2; i++)
    if (vector[i] == vector[vector.size() - 1 - i])
      return false;
  return true;
}

bool Completeness::checkM(std::string vector) {
  for (int i = 0; i < vector.size(); ++i) {
    for (int j = 0; j < vector.size(); ++j) {
      if ((i & j) == i) {
        if (vector[i] > vector[j]) {
          return false;
        }
      }
    }
  }
  return true;
}

bool Completeness::isLinear(const std::vector<int> &coeffs, int numVariables) {
  for (int i = numVariables; i < coeffs.size(); ++i)
    if (coeffs[i] != 0)
      return false;
  return true;
}

bool Completeness::checkL(std::string vector) {
  int n = vector.size();
  int cnt = log2(n);
  int c0 = vector[0] - '0';
  if (cnt == 2) {
    int cy = c0 ^ (vector[1] - '0');
    int cx = c0 ^ (vector[2] - '0');

    int cxy = c0 ^ cx ^ cy ^ (vector[3] - '0');

    if (cxy == 0)
      return true;
    return false;
  } else if (cnt == 3) {
    bool cz = c0 ^ (vector[1] - '0');
    bool cy = c0 ^ (vector[2] - '0');
    bool cx = c0 ^ (vector[4] - '0');

    bool cxz = c0 ^ cx ^ cz ^ (vector[5] - '0');
    bool czy = c0 ^ cz ^ cy ^ (vector[3] - '0');
    bool cxy = c0 ^ cx ^ cy ^ (vector[6] - '0');

    bool cxyz = c0 ^ cx ^ cy ^ cz ^ (vector[7] - '0');

    if (cxy == 0 && cxz == 0 && czy == 0 && cxyz == 0)
      return true;
    return false;
  } else if (cnt == 4) {
    bool cx = c0 ^ (vector[1] - '0'); // f(0, 0, 0, 1)
    bool cy = c0 ^ (vector[2] - '0'); // f(0, 0, 1, 0)
    bool cz = c0 ^ (vector[4] - '0'); // f(0, 1, 0, 0)
    bool cw = c0 ^ (vector[8] - '0'); // f(1, 0, 0, 0)

    bool cxz = c0 ^ cx ^ cz ^ (vector[5] - '0'); // f(0, 0, 1, 1)
    bool cxy = c0 ^ cx ^ cy ^ (vector[6] - '0'); // f(0, 1, 0, 1)
    bool czy = c0 ^ cz ^ cy ^ (vector[3] - '0'); // f(0, 1, 1, 0)

    bool cxyz = c0 ^ cx ^ cy ^ cz ^ (vector[7] - '0'); // f(0, 1, 1, 1)

    bool cwz = c0 ^ cw ^ cz ^ (vector[9] - '0');        // f(1, 0, 0, 1)
    bool cxwz = c0 ^ cw ^ cx ^ cz ^ (vector[10] - '0'); // f(1, 0, 1, 0)

    if (cxy == 0 && cxz == 0 && czy == 0 && cxyz == 0 && cwz == 0 && cxwz == 0)
      return true;
    return false;
  }
  return false;
}

void Completeness::computeMatrix() {
  int cntVectors = vectorOfVectors.size();
  complMatrix.resize(cntVectors, std::vector<bool>(5, false));
  for (int i = 0; i < cntVectors; ++i) {
    std::string vector = vectorOfVectors[i];

    complMatrix[i][0] = checkT0(vector);
    complMatrix[i][1] = checkT1(vector);
    complMatrix[i][2] = checkS(vector);
    complMatrix[i][3] = checkM(vector);
    complMatrix[i][4] = checkL(vector);
  }
}

void Completeness::printMatrix() {
  std::cout << "Index | T0 | T1 | S  | M  | L\n";
  std::cout << "--------------------------------\n";

  for (int i = 0; i < complMatrix.size(); ++i) {
    std::cout << " " << i << "    |";

    for (int j = 0; j < complMatrix[i].size(); ++j) {
      std::cout << " " << (complMatrix[i][j] ? "1" : "0") << "  |";
    }
    std::cout << "\n";
  }
  bool isComplete = true;
  for (int j = 0; j < complMatrix[0].size(); ++j) {
    bool isColumnComplete = true;
    for (int i = 0; i < complMatrix.size(); ++i) {
      if (!complMatrix[i][j]) {
        isColumnComplete = false;
        break;
      }
    }
    if (isColumnComplete) {
      isComplete = false;
      break;
    }
  }

  if (isComplete) {
    std::cout << "\nМножество функций полное.\n";
  } else {
    std::cout << "\nМножество функций не полное.\n";
  }
}

int main(int argc, char *argv[]) {
  Completeness test;
  test.readVectors();
  test.computeMatrix();
  test.printMatrix();
  return 0;
}

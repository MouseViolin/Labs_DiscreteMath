#include "attitude.h"
#include <iostream>

bool PropertiesAttitude::canReflex() {

  for (int i(0); i < matrix.size(); i++)
    if (matrix[i][i] != 1)
      return false;
  return true;
}

bool PropertiesAttitude::canTransitivity() {
  std::vector<std::vector<int>> result(matrix.size(),
                                       std::vector<int>(matrix.size(), 0));

  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      for (int k = 0; k < matrix.size(); ++k) {
        result[i][j] += matrix[i][k] * matrix[k][j];
      }
    }
  }

  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix.size(); ++j) {
      if (result[i][j] > 0 && matrix[i][j] == 0) {
        return false;
      }
    }
  }

  return true;
}

bool PropertiesAttitude::canSym() {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = i + 1; j < matrix.size(); j++) {
      if (matrix[i][j] != matrix[j][i]) {
        return false;
      }
    }
  }
  return true;
}
bool PropertiesAttitude::canAsym() {
  for (int i = 0; i < matrix.size(); ++i) {
    if (matrix[i][i] != 0) {
      return false;
    }
    for (int j = 0; j < matrix.size(); ++j) {
      if (i != j && matrix[i][j] == 1 && matrix[j][i] == 1) {
        return false;
      }
    }
  }
  return true;
}

bool PropertiesAttitude::canAntiSym() {
  bool flag = false;
  for (int i = 0; i < matrix.size(); i++) {
    if (matrix[i][i] == 1)
      flag = 1;

    for (int j = 0; j < matrix.size(); j++) {
      if (i != j) {
        if ((matrix[i][j] == 1 && matrix[j][i] == 1)) {
          return false;
        }
      }
    }
  }
  return flag;
}
bool PropertiesAttitude::canConnected() {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = i + 1; j < matrix.size(); j++) {
      if (matrix[i][j] == 0 && matrix[j][i] == 0) {
        return false;
      }
    }
  }
  return true;
}

void PropertiesAttitude::allPropAttMatrix() {
  isTrans = canTransitivity();
  isConn = canConnected();
  isAntiSym = canAntiSym();
  isSym = canSym();
  isAsym = canAsym();
  isReflex = canReflex();

  (isReflex) ? std::cout << "Матрица рефлексивна.\n"
             : std::cout << "Матрица антирефлексивна.\n";

  (isAntiSym) ? std::cout << "Матрица антисимметрична.\n"
              : std::cout << "Матрица не антисимметрична.\n";

  (isSym) ? std::cout << "Матрица симметрична.\n"
          : std::cout << "Матрица не симметрична.\n";

  (isTrans) ? std::cout << "Матрица транзитивна.\n"
            : std::cout << "Матрица не транзитивна.\n";

  (isConn) ? std::cout << "Матрица связна.\n"
           : std::cout << "Матрица не связна.\n";

  (isAsym) ? std::cout << "Матрица асимметрична.\n"
           : std::cout << "Матрица не асимметрична.\n";
}

int main() {
  PropertiesAttitude test;
  test.allPropAttMatrix();
  return 0;
}

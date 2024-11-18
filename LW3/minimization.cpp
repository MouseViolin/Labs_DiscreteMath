#include "minimization.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

void Minimization::readVector() {
  std::cout << "Введите вектор истинности:" << std::endl;
  std::cin >> vectBool;
  countVar = int(log2(vectBool.size()));
  // std::cout << countVar << std::endl;
  // std::cout << vectBool << std::endl;
}

void Minimization::createThuthTable() {
  // int idxPDNF = 0, idxPCNF = 0;
  std::vector<int> tmp;

  for (int i(0), tableIdx(0); i < pow(2, countVar); ++i) {
    for (int j(countVar - 1); j >= 0; --j) {
      // (vectBool[tableIdx] == '0') ? beforePCNF[idxPCNF].push_back((i >> j) &
      // 1)
      //                             : beforePDNF[idxPDNF].push_back((i >> j) &
      //                             1);
      tmp.push_back((i >> j) & 1);
    }
    (vectBool[tableIdx++] == '0') ? beforePCNF.push_back(tmp)
                                  : beforePDNF.push_back(tmp);
    tmp.clear();
  }
}

void Minimization::showNF() {
  std::cout << "СКНФ" << std::endl;
  for (int i(0); i < beforePCNF.size(); ++i) {
    for (int j(0); j < beforePCNF[i].size(); ++j) {
      std::cout << beforePCNF[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << "СДНФ" << std::endl;
  for (int i(0); i < beforePDNF.size(); ++i) {
    for (int j(0); j < beforePDNF[i].size(); ++j) {
      std::cout << beforePDNF[i][j];
    }
    std::cout << std::endl;
  }
}

void Minimization::gluing() {}

int main() {
  Minimization test;
  test.readVector();
  test.createThuthTable();
  test.showNF();

  return 0;
}

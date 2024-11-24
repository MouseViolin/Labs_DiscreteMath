#include "minimization.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>

void Minimization::readVector() {
  std::cout << "Введите вектор истинности:" << std::endl;
  std::cin >> vectBool;
  countVar = int(log2(vectBool.size()));
}

void Minimization::createThuthTable() {
  std::vector<int> tmp;

  for (int i(0), tableIdx(0); i < pow(2, countVar); ++i) {
    for (int j(countVar - 1); j >= 0; --j) {
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

bool Minimization::canCombine(const std::vector<int> &a,
                              const std::vector<int> &b,
                              std::vector<int> &result) {
  int diffCount = 0;
  result = a;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) {
      if (a[i] == -1 || b[i] == -1)
        return false;
      ++diffCount;
      result[i] = -1;
    }
  }
  std::cout << "Trying to combine: ";
  for (int v : a)
    std::cout << v;
  std::cout << " and ";
  for (int v : b)
    std::cout << v;
  std::cout << " -> " << (diffCount == 1 ? "Combined!" : "Cannot combine.")
            << "\n";

  return diffCount == 1;
}

std::vector<std::vector<int>>
Minimization::combineTerms(const std::vector<std::vector<int>> &terms,
                           std::set<int> &used) {
  std::vector<std::vector<int>> newTerms;
  int termCount = terms.size();
  std::vector<bool> usedFlag(termCount, false);

  for (int i = 0; i < termCount; ++i) {
    for (int j = i + 1; j < termCount; ++j) {
      std::vector<int> combined;
      if (canCombine(terms[i], terms[j], combined)) {
        newTerms.push_back(combined);
        usedFlag[i] = usedFlag[j] = true;
      }
    }
  }
  for (int i = 0; i < termCount; ++i) {
    if (!usedFlag[i]) {
      newTerms.push_back(terms[i]);
      used.insert(i);
    }
  }

  return newTerms;
}

std::vector<std::vector<int>> Minimization::buildImplicantMatrix() {

  std::vector<std::vector<int>> matrix(resultGluing.size(),
                                       std::vector<int>(beforePDNF.size(), 0));
  for (int i = 0; i < resultGluing.size(); ++i) {
    for (int j = 0; j < beforePDNF.size(); ++j) {
      bool covers = true;
      for (int k = 0; k < beforePDNF[j].size(); ++k) {
        if (resultGluing[i][k] != -1 &&
            resultGluing[i][k] != beforePDNF[j][k]) {
          covers = false;
          break;
        }
      }
      matrix[i][j] = covers ? 1 : 0;
    }
  }
  return matrix;
}

std::vector<std::vector<int>> Minimization::getPDNF() { return beforePDNF; }

void Minimization::gluing() {
  std::set<int> used;
  implicants = beforePDNF;

  while (true) {
    auto newImplicants = combineTerms(implicants, used);

    if (newImplicants == implicants)
      break;

    allCombinedTerms.push_back(newImplicants);
    implicants = newImplicants;
  }

  resultGluing = implicants;
}

std::string Minimization::termToString(const std::vector<int> &term) {
  std::string result;
  for (int bit : term) {
    if (bit == -1) {
      result += "-";
    } else {
      result += std::to_string(bit);
    }
  }
  return result;
}

std::vector<int>
Minimization::minimizeCover(const std::vector<std::vector<int>> &matrix) {
  std::vector<int> result;
  std::vector<bool> covered(matrix[0].size(), false);

  while (
      std::any_of(covered.begin(), covered.end(), [](bool c) { return !c; })) {
    int bestRow = -1, maxCover = -1;
    for (size_t i = 0; i < matrix.size(); ++i) {
      int coverCount = 0;
      for (size_t j = 0; j < matrix[i].size(); ++j) {
        if (matrix[i][j] && !covered[j]) {
          ++coverCount;
        }
      }
      if (coverCount > maxCover) {
        maxCover = coverCount;
        bestRow = i;
      }
    }

    if (bestRow != -1) {
      result.push_back(bestRow);
      for (size_t j = 0; j < matrix[bestRow].size(); ++j) {
        if (matrix[bestRow][j]) {
          covered[j] = true;
        }
      }
    }
  }
  return result;
}

void Minimization::printImplicants() {
  for (const auto &term : resultGluing) {
    std::cout << termToString(term) << "\n";
  }
}

void Minimization::printAllCombinedTerms() {
  std::cout << "Все этапы склеивания:\n";
  for (size_t step = 0; step < allCombinedTerms.size(); ++step) {
    std::cout << "Шаг " << step + 1 << ":\n";
    for (const auto &term : allCombinedTerms[step]) {
      for (int bit : term) {
        if (bit == -1) {
          std::cout << "-";
        } else {
          std::cout << bit;
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}

int main() {
  Minimization test;
  test.readVector();
  test.createThuthTable();
  test.showNF();

  test.gluing();
  test.printAllCombinedTerms();

  auto matrix = test.buildImplicantMatrix();
  std::cout << "Implicant Matrix:\n";
  for (const auto &row : matrix) {
    for (int cell : row) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }

  auto minimized = test.minimizeCover(matrix);
  std::cout << "Минимизированная форма:\n";
  for (int idx : minimized) {
    std::cout << test.termToString(test.getResultGluing()[idx]) << "\n";
  }

  std::cout << "Итоговые импликанты:\n";
  test.printImplicants();

  return 0;
}

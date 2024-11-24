#include <set>
#include <string>
#include <vector>
class Minimization {
public:
  void readVector();
  void createThuthTable();
  void showNF();
  std::vector<std::vector<int>> getPDNF();
  std::vector<std::vector<int>> getResultGluing() { return resultGluing; };
  std::vector<int> minimizeCover(const std::vector<std::vector<int>> &matrix);
  void printImplicants();
  std::string termToString(const std::vector<int> &term);
  void printAllCombinedTerms();

  bool canCombine(const std::vector<int> &a, const std::vector<int> &b,
                  std::vector<int> &result);
  std::vector<std::vector<int>>
  combineTerms(const std::vector<std::vector<int>> &terms, std::set<int> &used);
  std::vector<std::vector<int>> buildImplicantMatrix();
  void gluing();

private:
  std::vector<std::vector<int>> beforePCNF;
  std::vector<std::vector<int>> beforePDNF;
  std::vector<std::vector<int>> resultGluing;
  std::string vectBool;
  int countVar;
  std::vector<std::vector<int>> implicants;
  std::vector<std::vector<std::vector<int>>> allCombinedTerms;
};

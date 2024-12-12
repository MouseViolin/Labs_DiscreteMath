

#include <string>
#include <vector>
class Completeness {
public:
  void readVectors();
  bool checkT0(std::string);
  bool checkT1(std::string);
  bool checkS(std::string);
  bool checkM(std::string);
  bool checkL(std::string);
  bool solveSystem(std::vector<std::vector<int>> &matrix,
                   std::vector<int> &results);
  std::vector<int> computePolynom(const std::string &vector);
  bool isLinear(const std::vector<int> &coeffs, int numVariables);

  void computeMatrix();
  void printMatrix();

private:
  std::vector<std::vector<bool>> complMatrix;
  std::vector<std::string> vectorOfVectors;
};

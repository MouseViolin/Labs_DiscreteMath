
#include <vector>

class PropertiesAttitude {
public:
  void readMatrix();
  void allPropAttMatrix();

  bool canTransitivity();
  bool canReflex();
  bool canSym();
  bool canConnected();
  bool canAntiSym();
  bool canAsym();

private:
  // std::vector<std::vector<int>> matrix = {
  //     {1, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1},
  //     {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
  // std::vector<std::vector<int>> matrix = {
  //     {1, 0, 1, 0, 0, 1}, {0, 1, 0, 0, 0, 0}, {1, 0, 1, 0, 0, 1},
  //     {0, 0, 0, 1, 0, 0}, {0, 0, 0, 0, 1, 0}, {1, 0, 1, 0, 0, 1}};
  std::vector<std::vector<int>> matrix = {
      {0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 1},
      {1, 1, 1, 0, 0, 0}, {1, 1, 1, 1, 0, 0}, {0, 1, 0, 1, 1, 0}};
  // std::vector<std::vector<int>> matrix = {
  //     {0, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 0},
  //     {0, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 0}, {0, 1, 1, 1, 1, 0}};

  bool isTrans = 0;
  bool isSym = 0;
  bool isAntiSym = 0;
  bool isConn = 0;
  bool isAsym = 0;
  bool isReflex = 0;
};

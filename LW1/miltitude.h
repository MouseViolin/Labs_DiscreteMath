

#include <iostream>
#include <map>
#include <vector>

class Multitude {
private:
  int UNIVERSE[101] = {
      -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36,
      -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21,
      -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9,  -8,  -7,  -6,
      -5,  -4,  -3,  -2,  -1,  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
      10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,
      25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
      40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50};
  int occurrenceTracker[101];
  std::vector<std::vector<int>> vecOfArrays;
  int multipl = 1;
  int sign = 0;

public:
  Multitude() {}
  ~Multitude() {}

  bool isInUniverse(int num);
  bool checkingDuplicate(int num);
  bool isMultiplicity(int num);
  bool isSign(int num);

  void changeMultipl(int num);
  void changeSign(int _);

  std::vector<int> difference(std::vector<int> a, std::vector<int> b);
  std::vector<int> combining(std::vector<int> a, std::vector<int> b);
  std::vector<int> intersection(std::vector<int> a, std::vector<int> b);
  std::vector<int> symDifference(std::vector<int> a, std::vector<int> b);
  std::vector<int> additionToUniverse(std::vector<int> _);

  void specifyingFormula();
  std::vector<int>
  evaluateFormula(const std::string &formula,
                  const std::map<char, std::vector<int>> &sets);

  void callDifference(int numA, int numB);
  void callIntersection(int numA, int numB);
  void callSymDifference(int numA, int numB);
  void callCombining(int numA, int numB);
  void callAddToUn(int num);

  void printMultitude(int index);
  void setMultitude(int size);
  void resetArrTracker();

  friend std::ostream &operator<<(std::ostream &out, const Multitude &);
  friend std::istream &operator>>(std::istream &in, Multitude &a);
};

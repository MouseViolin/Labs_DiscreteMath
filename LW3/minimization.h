#include <string>
#include <vector>
class Minimization {
public:
  // Minimization();
  // Minimization(Minimization &&) = default;
  // Minimization(const Minimization &) = default;
  // Minimization &operator=(Minimization &&) = default;
  // Minimization &operator=(const Minimization &) = default;
  // ~Minimization();

  void readVector();
  void
  createThuthTable(); // формально уже распределяем значения для СКНФ и СДНФ
  void showNF();

  void
  writeVaribles(); // формирование строки с названиями переменных (не точно)
  void gluing();

private:
  std::vector<std::vector<int>> beforePCNF;
  std::vector<std::vector<int>> beforePDNF;
  std::vector<std::vector<int>> resultGluing;
  std::string variables;
  std::string vectBool;
  int countVar;
};

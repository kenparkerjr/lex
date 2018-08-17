#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
#include <map>
#include "Symbol.h"
using namespace std;

class Vm
{
public:
  Symbol *GetSymbol(string name);
  void Load(string path);
  void LoadProgram(string path);
private:
  tuple<string, string, string> NextCommand(string line);
  map<string, Symbol> symbolTable;
  
};


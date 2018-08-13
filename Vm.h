#include <string>
#include <sstream>
#include <fstream>
#include "Symbol.h"
using namespace std;

class Vm
{
public:
  void Load(string path);
private:
  tuple<string, string, string> NextCommand(string line);

};


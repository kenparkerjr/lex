#include <string>
using namespace std;

enum SymbolType
{
  Unk = -1,
  Label = 0,
  Int = 1,
  String = 2  
};

class Symbol
{
public:
  Symbol(SymbolType aType, string& aLabel, void *apValue) : type(aType), label(aLabel), pValue(apValue) {}
  const SymbolType Type() const { return type; }
  const string Label() const { return label; }
  const void *Value() const { return pValue; }
private:
  const SymbolType type;
  const string label;
  const void *pValue; 
};

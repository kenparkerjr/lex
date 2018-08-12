#include <string>
#include <cstring>
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
  Symbol(string &aLabel, int aValue) : type(SymbolType::Int), label(aLabel)
  {
    pValue = new int;
    memcpy((void*)pValue, (void *)&aValue, sizeof(int));
  }
  Symbol(string &aLabel, string& aValue) : type(SymbolType::String), label(aLabel)
  {
    pValue = new string(aValue);
    
  }
  const SymbolType Type() const { return type; }
  const string Label() const { return label; }
  const void *Value() const { return pValue; }
private:
  const SymbolType type;
  const string label;
  const void *pValue; 
};

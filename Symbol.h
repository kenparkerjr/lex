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
  static Symbol CreateLabel(string aLabel, int aAddress)
  {
    auto paAddress = new int;
    memcpy((void*)paAddress, (void *)&aAddress, sizeof(int));
    return Symbol(SymbolType::Label, aLabel, paAddress);
  }
  const SymbolType Type() const { return type; }
  const string Label() const { return label; }
  const void *Value() const { return pValue; }
private:
  const SymbolType type;
  const string label;
  const void *pValue; 
};

static SymbolType GetTypeFromName(string name)
{
  if(name[0] == '@')
    return SymbolType::Label;
  else if(name == "string")
    return SymbolType::String;
  else if(name == "int")
    return SymbolType::Int;
  else
    return SymbolType::Unk;
}


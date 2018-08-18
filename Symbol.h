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
  Symbol(SymbolType aType, string& aLabel, void *apValue, int aOffset) : type(aType), label(aLabel), pValue(apValue), offset(aOffset) {}
  Symbol(string &aLabel, int aValue, int aOffset) : type(SymbolType::Int), label(aLabel), offset(aOffset)
  {
    pValue = new int;
    memcpy((void*)pValue, (void *)&aValue, sizeof(int));
  }
  Symbol(string &aLabel, string& aValue, int aOffset) : type(SymbolType::String), label(aLabel), offset(aOffset)
  {
    pValue = new string(aValue);
    
  }
  Symbol(string &aLabel, int aOffset) : type(SymbolType::Label), label(aLabel), offset(aOffset)
  {
    pValue = new int;
    memcpy((void*)pValue, (void *)&aOffset, sizeof(int));

  } 
  static Symbol CreateLabel(string aLabel, int aAddress, int aOffset)
  {
    auto paAddress = new int;
    memcpy((void*)paAddress, (void *)&aAddress, sizeof(int));
    return Symbol(SymbolType::Label, aLabel, paAddress, aOffset);
  }
  const SymbolType Type() const { return type; }
  const string Label() const { return label; }
  const void *Value() const { return pValue; }
  const int Offset() const { return offset; }
private:
  const SymbolType type;
  const string label;
  const void *pValue; 
  const int offset;
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


#include "Vm.h"
#include <iostream>
#include <cstring>
using namespace std;

SymbolType GetTypeFromName(string name)
{
  if(name == "label")
    return SymbolType::Label;
  else if(name == "string")
    return SymbolType::String;
  else if(name == "int")
    return SymbolType::Int;
  else
    return SymbolType::Unk;
}

void Vm::Load(string path)
{
  ifstream f(path);

  string line;

  while(getline(f, line))
  {
    auto end_type = line.find_first_of(" ", 0);
    cout << end_type<< endl;
    auto s = line.substr(0, end_type); 
    cout << "[" << s << "]" <<  endl;
   
    auto start_label = line.find_first_not_of(" ", end_type); 
    auto end_label = line.find_first_of(" ", start_label);
    auto label_size = end_label - start_label;
    auto label = line.substr(start_label, label_size);
    cout << "[" << label << "]" << endl;

    auto start_value = line.find_first_not_of(" ", end_label);
    auto end_value = line.find_first_of(" ", start_value);
    auto value = line.substr(start_value, end_value);
    cout << "[" << value << "]" << endl;      

    
    SymbolType t = GetTypeFromName(s);        

    void *symbolValue;    
    
    if(t == SymbolType::String){
      string s = value.substr(1, value.length()-2);
      symbolValue = (void*)new string(s);
      cout << "--->" << *((string*)(symbolValue));
    }
    else if(t == SymbolType::Int){
      symbolValue = new int;
      int int_value = stoi(value);
      memcpy(symbolValue, (void*)(&int_value), 1);
      cout << "->>" <<  *((int*)(symbolValue)) << endl;  
    }
    
    Symbol symbol(t, label, symbolValue);
    
    cout << "{" << (int)symbol.Type() << ":" << symbol.Label() << ":" << *((string*)symbol.Value()) << "}" << endl;

  }
}

int main(int argc, char **argv)
{
  Vm vm;
  
  vm.Load("test.v");

  return 0;
}

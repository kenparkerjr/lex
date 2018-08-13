#include "Vm.h"
#include <iostream>
#include <cstring>
#include <map>
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
tuple<string, string, string> Vm::NextCommand(string line)
{
 
}
void Vm::Load(string path)
{
  ifstream f(path);

  string line;
  
  auto symbolTable = new map<string, Symbol>();

  while(getline(f, line))
  {
    if(line.size() <= 0) continue; //Ignore blank lines    

    auto cmd = NextCommand(line);
    

    auto end_type = line.find_first_of(" ", 0);
    end_type = end_type > line.length() ? line.length() : end_type; 
    auto s = line.substr(0, end_type); 
    if(s.size() > 0 && s[0] == '@')
    {
      cout << s << ":" << s.length() << ":" << end_type << endl;
      string lbl = s.substr(0, end_type);
      symbolTable->emplace(lbl, Symbol(lbl, 0));
      continue;
    }
    else if(s == "jump_lt" || s == "compare" || s == "print" || s == "load" || s == "inc")
      continue;  
 
    auto start_label = line.find_first_not_of(" ", end_type); 
    auto end_label = line.find_first_of(" ", start_label);
    auto label_size = end_label - start_label;
    auto label = line.substr(start_label, label_size);

    auto start_value = line.find_first_not_of(" ", end_label);
    auto end_value = line.find_first_of(" ", start_value);
    auto value = line.substr(start_value, end_value);

    
    SymbolType t = GetTypeFromName(s);        

    void *symbolValue;    
    
    if(t == SymbolType::String){
      string s = value.substr(1, value.length()-2);
      Symbol ls(label, s); 
      symbolTable->emplace(label, ls);
    }
    else if(t == SymbolType::Int){
      symbolValue = new int;
      int int_value = stoi(value);
      Symbol is(label, int_value);
      symbolTable->emplace(label, is);
    }
    
  }
  for(auto x = symbolTable->begin(); x != symbolTable->end(); ++x)
    cout << "{" << (symbolTable->find(x->first)->second).Label() << "}" <<  endl;
}

int main(int argc, char **argv)
{
  Vm vm;
  
  vm.Load("test.v");

  return 0;
}

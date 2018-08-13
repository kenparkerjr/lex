#include "Vm.h"
#include <iostream>
#include <cstring>
#include <map>
#include <tuple>
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
  tuple<string, string, string> cmd;

  //ignore blank lines
  if(line.size() <= 0) return cmd; 
  
  auto end = line.find_first_of(" ", 0);
  end = end > line.length() ? line.length() : end; 
  string s = line.substr(0, end);
  get<0>(cmd) = s;

  //return if it is a label
  if(s[0] == '@') return cmd;
  
  //return if not a symbol
  if(s == "jump_lt" || s == "compare" || s == "print" || s == "load" || s == "inc") return cmd;

  //parse first operand
  auto start = line.find_first_not_of(" ", end);
  end = line.find_first_of(" ", start);
  auto len = end - start;
  get<1>(cmd) = line.substr(start, len);


  start = line.find_first_not_of(" ", end);
  end = line.find_first_of(" ", start);
  len = end - start;
  get<2>(cmd) = line.substr(start, len);
  
 
}
void Vm::Load(string path)
{
  ifstream f(path);

  string line;
  
  auto symbolTable = new map<string, Symbol>();

  while(getline(f, line))
  {
    auto cmd = NextCommand(line);
    string command = get<0>(cmd);
    string op1 = get<1>(cmd);
    string op2 = get<2>(cmd);

    cout << ":" << command << ":" << op1 << ":" << op2 << endl;

    SymbolType t = GetTypeFromName(command);        
    
    void *symbolValue;    
    
    if(t == SymbolType::String){
      string s = op2.substr(1, op2.length()-2);
      Symbol ls(op1, s); 
      symbolTable->emplace(op1, ls);
    }
    else if(t == SymbolType::Int){
      symbolValue = new int;
      int int_value = stoi(op2);
      Symbol is(op2, int_value);
      symbolTable->emplace(op1, is);
    }
    else if(t == SymbolType::Label)
    {
      cout << "Label: " << command << endl;
    }
    else
    {
      cout << "NOT A SYMBOL" << endl;
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

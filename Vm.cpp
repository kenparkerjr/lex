#include "Vm.h"
#include "Command.h"
#include <iostream>
#include <cstring>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

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
using Instruction = tuple<int, int, int>;
void Vm::Load(string path)
{


  ifstream f(path);

  string line;
  
  auto symbolTable = new map<string, Symbol>();
  
  vector<Instruction> program;  

  int pc = 0; //Program Counter
  while(getline(f, line))
  {
    auto cmd = NextCommand(line);
    string command = get<0>(cmd);
    string op1 = get<1>(cmd);
    string op2 = get<2>(cmd);

    SymbolType t = GetTypeFromName(command);        
    
    
    if(t == SymbolType::String){
      string s = op2.substr(1, op2.length()-2);
      symbolTable->emplace(op1, Symbol(op1, s));
    }
    else if(t == SymbolType::Int)
      symbolTable->emplace(op1, Symbol(op1, stoi(op2)));
    else if(t == SymbolType::Label)
      symbolTable->emplace(op1, Symbol(op1, pc));
    else
    {
      //int cmd = CommandFromName(command);
      //cout << command << endl;
    }
    


    pc++;
  }

  

}

int main(int argc, char **argv)
{
  Vm vm;
  
  vm.Load("test.v");

  return 0;
}

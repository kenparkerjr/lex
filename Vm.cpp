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
  
  //parse first operand
  auto start = line.find_first_not_of(" ", end);
  if(start != string::npos)
  {
    end = line.find_first_of(" ", start);
    auto len = end - start;
    get<1>(cmd) = line.substr(start, len);
  }

  //parse last operand 
  start = line.find_first_not_of(" ", end);
  if(start != string::npos)
  {
    end = line.find_first_of(" ", start);
    auto len = end - start;
    get<2>(cmd) = line.substr(start, len);
  }
  return cmd; 
}
using Instruction = tuple<int, int, int>;
void Vm::Load(string path)
{
  ifstream f(path);
  string line;
  
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
      symbolTable.emplace(op1, Symbol(op1, s, pc));
    }
    else if(t == SymbolType::Int)
      symbolTable.emplace(op1, Symbol(op1, stoi(op2), pc));
    else if(t == SymbolType::Label)
      symbolTable.emplace(op1, Symbol::CreateLabel(op1, pc, pc));
    else
      ; //Do Nothing

    pc++;
  }

}
void Vm::LoadProgram(string path)
{
  vector<Instruction> program;
  ifstream f(path);
  string line;

  int pc = 0;  

  while(getline(f, line))
  {
    auto cmd = NextCommand(line);
    string command = get<0>(cmd);
    string op1 = get<1>(cmd);
    string op2 = get<2>(cmd);
   
    cout << command << ":" << op1 << ":" << op2 << endl;

    int command_code = CommandFromName(command);
    Instruction inst;    
    get<0>(inst) = command_code;
  
    
    //replace variable with value
    if(op1[0] == '$')
    {
      string s = op1.substr(1, op1.length()-1);
      auto result = symbolTable.find(s);
      if(result != symbolTable.end())
        cout << result->second.Offset() << endl;
      else
        cout << symbolTable.size() << "NOT FOUND: [" << op1 << "]" << endl;
    }
    program[pc] = inst;

 
  }
 
}

int main(int argc, char **argv)
{
  Vm vm;
  
  vm.Load("test.v");
  vm.LoadProgram("test.v");
  return 0;
}

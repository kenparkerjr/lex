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
  
  //Each element can be data or instructions
  vector<void *> program(1024);
  vector<void *> stack(1024);
  ifstream f(path);
  string line;

  int pc = 0;  

  while(getline(f, line))
  {
    auto cmd = NextCommand(line);
    string command = get<0>(cmd);
    string op1 = get<1>(cmd);
    string op2 = get<2>(cmd);
   
    int command_code = CommandFromName(command);
    //cout << command_code << ":" <<  command << ":" << op1 << ":" << op2 << endl;

    
    Symbol *op1_symbol;
 
    //replace variable with value
    if(op1[0] == '$')
    {
      string s = op1.substr(1, op1.length()-1);
      auto result = symbolTable.find(s);
      if(result != symbolTable.end())
        op1_symbol = &result->second;
      else
        cout << symbolTable.size() << "NOT FOUND: [" << op1 << "]" << endl;
    }

    switch(command_code)
    {
      case int_: {
        void *data = (void*)new int;
        int val = stoi(op2);
        memcpy(data, (void*)(&val), sizeof(int));
        program[pc] = data;
        //cout << pc << ":" << "int" << ":" << val;
        break;
      }
      case pushi: {
        int loc = -1;       
        void *data = (void*)op1_symbol->Value();
        //cout << "pushi: " <<  *(int *)(data) << endl;
        stack.push_back(data);
        break;
      }
      case addi: {
        int *a = (int *)stack.back();
        stack.pop_back();

        int *b = (int *)stack.back();
        stack.pop_back();

        int *c = new int;
        *c = *a + *b;
        
        stack.push_back(c);

        //cout << "addi: " << *a << " " << *b << " " << *c << endl; 

      }
      case puti: {
        void *data = stack.back();
        int int_value = *((int *)data);
        cout << int_value << endl;
        stack.pop_back();
      }
      case geti: {
        int *int_value = new int;
        cin >> *int_value;
        stack.push_back(int_value);
        //cout << "geti: " << *int_value << endl;        
      }
      case cmp: {
        
      }
      case stp: {
        //cout << "PROGRAM STOP ENCOUNTERED" << endl;
        return;
      }
    }    
  }
 
}

int main(int argc, char **argv)
{
  Vm vm;
  
  vm.Load("test.v");
  vm.LoadProgram("test.v");
  return 0;
}

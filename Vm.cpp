#include "Vm.h"
#include "Command.h"
#include <iostream>
#include <cstring>
#include <map>
#include <tuple>
#include <vector>
using namespace std;

#define GT  0b0100
#define LT  0b0010
#define EQ  0b0001

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
Symbol *Vm::GetSymbol(string name)
{
  string s = name.substr(1, name.length()-1);
  auto result = symbolTable.find(s);
  if(result != symbolTable.end())
    return &result->second;
   
  return NULL;
}
void Vm::LoadProgram(string path)
{
  
  //Each element can be data or instructions
  vector<void *> program(1024);
  vector<void *> stack(1024);
  ifstream f(path);
  string line;

  

  int pc = 0; //Program Counter

  //|GT|LT|EQ 
  
  int cf = 0x0;  

  while(getline(f, line))
  {
    auto cmd = NextCommand(line);
    string command = get<0>(cmd);
    string op1 = get<1>(cmd);
    string op2 = get<2>(cmd);
   
    int command_code = CommandFromName(command);
    cout << command_code << ":" <<  command << ":" << op1 << ":" << op2 << endl;

    
    //replace variable with value
    Symbol *op1_symbol;
    if(op1[0] == '$' || op1[0] == '@')
      op1_symbol = GetSymbol(op1);

    Symbol *op2_symbol;
    if(op2[0] == '$')
      op2_symbol = GetSymbol(op2); 

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
        break;
      }
      case puti: {
        void *data = stack.back();
        int int_value = *((int *)data);
        cout << int_value << endl;
        stack.pop_back();
        break;
      }
      case geti: {
        int *int_value = new int;
        cin >> *int_value;
        stack.push_back(int_value);
        //cout << "geti: " << *int_value << endl;        
        break;
      }
      case cmp: {
        int *a = (int *)op1_symbol->Value();
        int *b = (int *)op2_symbol->Value();
        cf = 0x0;
        if( *a == *b ) cf = cf | EQ;
        if( *a > *b) cf = cf | GT;
        if( *a < *b) cf = cf | LT;
        break;
      }
      case jmp_gt: {
        //int *addr = (int*)op1_symbol->Value();
        
        cout << "jmp_gt: " << op1_symbol->Label() << endl;      
        break;
        
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

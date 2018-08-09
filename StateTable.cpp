#include <iostream>

using namespace std;
const int STATE_TABLE_SIZE = 100;

class StateTable
{
public:
  StateTable()
  {
    clear();
    states[0]['a'] = 1;
    states[1]['a'] = 1;
    states[1][';'] = 2;
  }
  int State(int current, char atom)
  {
    return states[current][(int)atom];
  }
private:
  int states[STATE_TABLE_SIZE][STATE_TABLE_SIZE];
  void clear()
  {
    for(int x = 0; x < STATE_TABLE_SIZE; x++)
      for(int y=0; y < STATE_TABLE_SIZE; y++)
        states[x][y] = -1;
  }
};

int main(int argc, char **argv)
{
  StateTable st;
  
  auto current = st.State(current, 'a');
  cout << current << "a" << endl;
  
  current = st.State(current, 'a');
  cout << current << "a" << endl;
  
  current = st.State(current, ';');
  cout << current << ";" << endl;

  return 0;
}

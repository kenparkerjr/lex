#include <iostream>
#include <tuple>

using namespace std;

int main(int argc, char **argv)
{
  tuple<int, int, int> t;
  get<0>(t) = 101;
  get<1>(t) = 102;
  get<2>(t) = 103;

  cout << get<0>(t) << ":" << get<1>(t) << ":" << get<2>(t) << endl;

}

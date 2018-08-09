#include <string>

using namespace std;

class Token
{
public:
  Token(int aLine, int aColumn, string& aValue) : line(aLine), column(aColumn), value(aValue) {}

  const int Line() const { return line; }
  const int Column() const { return column; }
  const string Value() const { return value; }
private:
  const int line;
  const int column;
  const string value;
};

int main(int argc, char **argv)
{
  return 0;
}


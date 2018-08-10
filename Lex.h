#include <string>
#include "Token.h"

class Lex
{
public:
	Lex(const string& aSource) : source(aSource) {}
	Token *Next();

private:
	const string source;
	int startState = 0;
	int currentState = 0;
	int head = 0;
};

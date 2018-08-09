#include <iostream>
#include "lex.h"

using namespace std;

Token* Lex::Next()
{
	Token *t = NULL;
	string tokenValue = "";
	int position;
	for(position=head; position < source.length(); position++)
	{
		char atom = source[position];
	  tokenValue += atom;
		if(atom == ';')
		{	
			t = new Token(0, position, tokenValue);
			break;
		}
	}
	head = position+1;
	return t; 
}

int main(int argc, char **argv)
{
	Lex lex("aaa;bbb;ccc;ddd;");
	auto token = lex.Next();
	while(token != NULL)
	{
		cout << token->Value() << endl;
		token = lex.Next();
	}
	return 0;
}

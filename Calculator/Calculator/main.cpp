#include <iostream>
#include <sstream>
#include "Tokenize.h"
#include "Parse.h"
using namespace std;

bool Calculate(const string & exp, float & result)
{
	list<Token> tokens;
	if (Tokenize(exp, tokens))
	{
		if(ParseExp(tokens, result) && tokens.empty())
		{
			return true;
		}
		else
		{
			cout << "Parse error.\n";
			return false;
		}
	}
	else
	{
		cout << "Tokenization error.\n";
		return false;
	}
}

int main()
{
	string expression;
	float result;
	cout << "(Input empty string to exit.)\n";
	while (true)
	{
		getline(cin, expression);
		if (expression.empty())
		{
			return 0;
		}
		else if(Calculate(expression, result))
		{
			cout << result << endl;
		}
	}
}
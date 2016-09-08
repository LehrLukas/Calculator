#include "Parse.h"

/*
exp = term exp'
exp' = + term exp' | null
term = factor term'
term' = * factor term' | null
factor = (exp) | num
*/

bool ParseFactor(list<Token> & exp, float & result)
{
	if (exp.empty())
	{
		return false;
	}
	else if (exp.front().tokenType == TokenType::NUM)
	{
		result = exp.front().value.num;
		exp.pop_front();
		return true;
	}
	else if (exp.front().tokenType == TokenType::LPAREN)
	{
		exp.pop_front();
		if (!ParseExp(exp, result))
		{
			return false;
		}
		else
		{
			if (!exp.empty() && exp.front().tokenType == TokenType::RPAREN)
			{
				exp.pop_front();
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
}

bool ParseTerm(list<Token> & exp, float & result)
{
	if (!ParseFactor(exp, result))
	{
		return false;
	}
	while (!exp.empty() && (exp.front().tokenType == TokenType::MUL || exp.front().tokenType == TokenType::DIV))
	{
		TokenType tt = exp.front().tokenType;
		exp.pop_front();
		float other;
		if (!ParseFactor(exp, other))
		{
			return false;
		}
		if (tt == TokenType::MUL)
		{
			result *= other;
		}
		else
		{
			result /= other;
		}
	}
	return true;
}

bool ParseExp(list<Token> & exp, float & result)
{
	if (!ParseTerm(exp, result))
	{
		return false;
	}
	while (!exp.empty() && (exp.front().tokenType == TokenType::ADD || exp.front().tokenType == TokenType::SUB))
	{
		TokenType tt = exp.front().tokenType;
		exp.pop_front();
		float other;
		if (!ParseTerm(exp, other))
		{
			return false;
		}
		if (tt == TokenType::ADD)
		{
			result += other;
		}
		else
		{
			result -= other;
		}
	}
	return true;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// postfix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Постфиксная форма выражения - описание и реализация

#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <string>
#include <map>
#include "stack.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	map<char, int> priority;
	map<string, double> operands;

	int GetPriority(char op) const;
	bool IsOperation(char c) const;
	bool IsOperand(char c) const;
	bool IsFunction(const string& s) const;
	void Parse();

public:
	TPostfix(const string& expr = "");

	string GetInfix() const { return infix; }
	string GetPostfix() const { return postfix; }

	void SetInfix(const string& expr);
	string ToPostfix();

	void SetOperand(const string& name, double value);
	double Calculate();
};

#endif
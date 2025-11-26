// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// postfix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Постфиксная форма выражения - реализация

#include "arithmetic.h"
#include <cctype>
#include <sstream>
#include <cmath>

TPostfix::TPostfix(const string& expr) : infix(expr)
{
    priority['('] = 0;
    priority[')'] = 1;
    priority['+'] = 2;
    priority['-'] = 2;
    priority['*'] = 3;
    priority['/'] = 3;
    priority['^'] = 4;
}

void TPostfix::SetInfix(const string& expr)
{
    infix = expr;
    postfix = "";
    operands.clear();
}

int TPostfix::GetPriority(char op) const
{
    auto it = priority.find(op);
    if (it != priority.end())
        return it->second;
    return -1;
}

bool TPostfix::IsOperation(char c) const
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool TPostfix::IsOperand(char c) const
{
    return isalpha(c) || isdigit(c) || c == '.';
}

bool TPostfix::IsFunction(const string& s) const
{
    return s == "sin" || s == "cos" || s == "exp" ||
        s == "log" || s == "tg" || s == "tan";
}

string TPostfix::ToPostfix()
{
    TStack<string> stack(100);
    postfix = "";

    string token = "";

    for (size_t i = 0; i < infix.length(); i++)
    {
        char c = infix[i];

        // Пропускаем пробелы
        if (c == ' ')
            continue;

        // Если это буква - может быть функция или переменная
        if (isalpha(c))
        {
            token += c;

            // Читаем полное имя
            while (i + 1 < infix.length() && isalpha(infix[i + 1]))
            {
                i++;
                token += infix[i];
            }

            // Проверяем, функция ли это
            if (IsFunction(token))
            {
                stack.Push(token);
            }
            else
            {
                // Это переменная
                postfix += token + " ";
            }
            token = "";
        }
        // Если это цифра
        else if (isdigit(c) || c == '.')
        {
            token += c;

            // Читаем полное число
            while (i + 1 < infix.length() && (isdigit(infix[i + 1]) || infix[i + 1] == '.'))
            {
                i++;
                token += infix[i];
            }

            postfix += token + " ";
            token = "";
        }
        // Открывающая скобка
        else if (c == '(')
        {
            stack.Push(string(1, c));
        }
        // Закрывающая скобка
        else if (c == ')')
        {
            while (!stack.IsEmpty() && stack.GetTop() != "(")
            {
                postfix += stack.Pop() + " ";
            }

            if (stack.IsEmpty())
                throw "Mismatched parentheses";

            stack.Pop(); // Удаляем '('

            // Если перед скобкой была функция, добавляем её
            if (!stack.IsEmpty() && IsFunction(stack.GetTop()))
            {
                postfix += stack.Pop() + " ";
            }
        }
        // Операция
        else if (IsOperation(c))
        {
            while (!stack.IsEmpty() && stack.GetTop() != "(" &&
                GetPriority(stack.GetTop()[0]) >= GetPriority(c))
            {
                postfix += stack.Pop() + " ";
            }
            stack.Push(string(1, c));
        }
        else
        {
            throw "Invalid character in expression";
        }
    }

    // Выталкиваем оставшиеся операции
    while (!stack.IsEmpty())
    {
        string op = stack.Pop();
        if (op == "(")
            throw "Mismatched parentheses";
        postfix += op + " ";
    }

    return postfix;
}

void TPostfix::SetOperand(const string& name, double value)
{
    operands[name] = value;
}

double TPostfix::Calculate()
{
    if (postfix.empty())
        ToPostfix();

    TStack<double> stack(100);
    string token = "";

    for (size_t i = 0; i < postfix.length(); i++)
    {
        char c = postfix[i];

        if (c == ' ')
        {
            if (!token.empty())
            {
                // Проверяем, это функция, операция или операнд
                if (IsFunction(token))
                {
                    // Это функция - берем один аргумент
                    if (stack.IsEmpty())
                        throw "Invalid expression";

                    double arg = stack.Pop();
                    double result;

                    if (token == "sin")
                        result = sin(arg);
                    else if (token == "cos")
                        result = cos(arg);
                    else if (token == "exp")
                        result = exp(arg);
                    else if (token == "log")
                    {
                        if (arg <= 0)
                            throw "Logarithm of non-positive number";
                        result = log(arg);
                    }
                    else if (token == "tg" || token == "tan")
                        result = tan(arg);
                    else
                        throw "Unknown function: " + token;

                    stack.Push(result);
                }
                else if (token.length() == 1 && IsOperation(token[0]))
                {
                    // Это бинарная операция
                    if (stack.GetCount() < 2)
                        throw "Invalid expression";

                    double b = stack.Pop();
                    double a = stack.Pop();
                    double result;

                    switch (token[0])
                    {
                    case '+': result = a + b; break;
                    case '-': result = a - b; break;
                    case '*': result = a * b; break;
                    case '/':
                        if (b == 0)
                            throw "Division by zero";
                        result = a / b;
                        break;
                    case '^': result = pow(a, b); break;
                    default: throw "Unknown operation";
                    }

                    stack.Push(result);
                }
                else
                {
                    // Это число или переменная
                    double value;

                    // Проверяем, является ли токен числом
                    bool isNumber = true;
                    for (char ch : token)
                    {
                        if (!isdigit(ch) && ch != '.' && ch != '-')
                        {
                            isNumber = false;
                            break;
                        }
                    }

                    if (isNumber)
                    {
                        value = stod(token);
                    }
                    else
                    {
                        // Это переменная
                        auto it = operands.find(token);
                        if (it == operands.end())
                            throw "Unknown operand: " + token;
                        value = it->second;
                    }

                    stack.Push(value);
                }

                token = "";
            }
        }
        else
        {
            token += c;
        }
    }

    if (stack.GetCount() != 1)
        throw "Invalid expression";

    return stack.Pop();
}
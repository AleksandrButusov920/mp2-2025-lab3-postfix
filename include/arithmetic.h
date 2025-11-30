#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "stack.h"
#include <string>

class ArithmeticExpression {
private:
    std::string infixExpression;
    std::string postfixExpression;

    bool isOperator(char c) const;
    bool isFunction(const std::string& token) const;
    int getPrecedence(char op) const;
    bool isDigit(char c) const;
    bool isLetter(char c) const;

    std::string extractNumber(const std::string& expr, int& pos) const;
    std::string extractToken(const std::string& expr, int& pos) const;

    double applyOperator(char op, double a, double b) const;
    double applyFunction(const std::string& func, double arg) const;

public:
    ArithmeticExpression();
    ArithmeticExpression(const std::string& expr);

    void setInfixExpression(const std::string& expr);
    std::string getInfixExpression() const;
    std::string getPostfixExpression() const;

    void convertToPostfix();
    double calculate() const;

    bool validate() const;
};

#endif // ARITHMETIC_H
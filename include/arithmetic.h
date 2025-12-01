#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "stack.h"
#include <string>

class ArithmeticExpression {
private:
    std::string infixExpression;
    std::string postfixExpression;
    double variableX;
    double variableY;
    double variableZ;

    bool isOperator(char c) const;
    bool isFunction(const std::string& token) const;
    bool isVariable(char c) const;
    int getPrecedence(char op) const;
    bool isDigit(char c) const;
    bool isLetter(char c) const;

    std::string extractNumber(const std::string& expr, int& pos) const;
    std::string extractToken(const std::string& expr, int& pos) const;

    double applyOperator(char op, double a, double b) const;
    double applyFunction(const std::string& func, double arg) const;
    double getVariableValue(char var) const;

public:
    ArithmeticExpression();
    ArithmeticExpression(const std::string& expr);

    void setInfixExpression(const std::string& expr);
    std::string getInfixExpression() const;
    std::string getPostfixExpression() const;

    void setVariableX(double value);
    void setVariableY(double value);
    void setVariableZ(double value);
    double getVariableX() const;
    double getVariableY() const;
    double getVariableZ() const;

    void convertToPostfix();
    double calculate() const;

    bool validate() const;
};

#endif // ARITHMETIC_H
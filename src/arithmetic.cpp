#include "arithmetic.h"
#include <cmath>
#include <stdexcept>


ArithmeticExpression::ArithmeticExpression() : infixExpression(""), postfixExpression(""), variableX(0), variableY(0), variableZ(0) {}

ArithmeticExpression::ArithmeticExpression(const std::string& expr) : infixExpression(expr), postfixExpression(""), variableX(0), variableY(0), variableZ(0) {
    convertToPostfix();
}

void ArithmeticExpression::setInfixExpression(const std::string& expr) {
    infixExpression = expr;
    postfixExpression = "";
}

std::string ArithmeticExpression::getInfixExpression() const {
    return infixExpression;
}

std::string ArithmeticExpression::getPostfixExpression() const {
    return postfixExpression;
}

void ArithmeticExpression::setVariableX(double value) {
    variableX = value;
}

void ArithmeticExpression::setVariableY(double value) {
    variableY = value;
}

void ArithmeticExpression::setVariableZ(double value) {
    variableZ = value;
}

double ArithmeticExpression::getVariableX() const {
    return variableX;
}

double ArithmeticExpression::getVariableY() const {
    return variableY;
}

double ArithmeticExpression::getVariableZ() const {
    return variableZ;
}

bool ArithmeticExpression::isOperator(char c) const {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool ArithmeticExpression::isFunction(const std::string& token) const {
    return token == "sin" || token == "cos" || token == "tg" ||
        token == "log" || token == "exp";
}

bool ArithmeticExpression::isVariable(char c) const {
    return c == 'x' || c == 'y' || c == 'z';
}

int ArithmeticExpression::getPrecedence(char op) const {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool ArithmeticExpression::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

bool ArithmeticExpression::isLetter(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string ArithmeticExpression::extractNumber(const std::string& expr, int& pos) const {
    std::string number = "";
    bool hasDecimal = false;

    while (pos < expr.length() && (isDigit(expr[pos]) || expr[pos] == '.')) {
        if (expr[pos] == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
        }
        number += expr[pos];
        pos++;
    }
    pos--;
    return number;
}

std::string ArithmeticExpression::extractToken(const std::string& expr, int& pos) const {
    std::string token = "";

    while (pos < expr.length() && isLetter(expr[pos])) {
        token += expr[pos];
        pos++;
    }
    pos--;
    return token;
}

double ArithmeticExpression::getVariableValue(char var) const {
    if (var == 'x') return variableX;
    if (var == 'y') return variableY;
    if (var == 'z') return variableZ;
    throw std::runtime_error("Unknown variable");
}

void ArithmeticExpression::convertToPostfix() {
    Stack<char> operators;
    Stack<std::string> functions;
    postfixExpression = "";

    for (int i = 0; i < infixExpression.length(); i++) {
        char c = infixExpression[i];

        if (c == ' ') continue;

        if (isDigit(c)) {
            postfixExpression += extractNumber(infixExpression, i);
            postfixExpression += ' ';
        }
        else if (isVariable(c)) {
            postfixExpression += c;
            postfixExpression += ' ';
        }
        else if (isLetter(c)) {
            std::string token = extractToken(infixExpression, i);
            if (isFunction(token)) {
                functions.push(token);
            }
            else {
                throw std::runtime_error("Unknown function: " + token);
            }
        }
        else if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                postfixExpression += operators.pop();
                postfixExpression += ' ';
            }
            if (operators.isEmpty()) {
                throw std::runtime_error("Mismatched parentheses");
            }
            operators.pop();

            if (!functions.isEmpty()) {
                postfixExpression += functions.pop();
                postfixExpression += ' ';
            }
        }
        else if (isOperator(c)) {
            while (!operators.isEmpty() && operators.top() != '(' &&
                getPrecedence(operators.top()) >= getPrecedence(c)) {
                postfixExpression += operators.pop();
                postfixExpression += ' ';
            }
            operators.push(c);
        }
    }

    while (!operators.isEmpty()) {
        if (operators.top() == '(') {
            throw std::runtime_error("Mismatched parentheses");
        }
        postfixExpression += operators.pop();
        postfixExpression += ' ';
    }
}

double ArithmeticExpression::applyOperator(char op, double a, double b) const {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    case '^': return pow(a, b);
    default: throw std::runtime_error("Unknown operator");
    }
}

double ArithmeticExpression::applyFunction(const std::string& func, double arg) const {
    if (func == "sin") return sin(arg);
    if (func == "cos") return cos(arg);
    if (func == "tg") return tan(arg);
    if (func == "log") {
        if (arg <= 0) throw std::runtime_error("Logarithm of non-positive number");
        return log(arg);
    }
    if (func == "exp") return exp(arg);
    throw std::runtime_error("Unknown function: " + func);
}

double ArithmeticExpression::calculate() const {
    if (postfixExpression.empty()) {
        throw std::runtime_error("Postfix expression is empty");
    }

    Stack<double> values;
    std::string token = "";

    for (int i = 0; i < postfixExpression.length(); i++) {
        char c = postfixExpression[i];

        if (c == ' ') {
            if (!token.empty()) {
                if (isFunction(token)) {
                    if (values.isEmpty()) {
                        throw std::runtime_error("Not enough operands for function");
                    }
                    double arg = values.pop();
                    values.push(applyFunction(token, arg));
                }
                else if (token.length() == 1 && isVariable(token[0])) {
                    values.push(getVariableValue(token[0]));
                }
                else {
                    double value = 0;
                    bool negative = false;
                    int start = 0;

                    if (token[0] == '-') {
                        negative = true;
                        start = 1;
                    }

                    for (int j = start; j < token.length(); j++) {
                        if (token[j] == '.') continue;
                        value = value * 10 + (token[j] - '0');
                    }

                    int decimalPos = -1;
                    for (int j = 0; j < token.length(); j++) {
                        if (token[j] == '.') {
                            decimalPos = j;
                            break;
                        }
                    }

                    if (decimalPos != -1) {
                        int decimals = token.length() - decimalPos - 1;
                        value /= pow(10, decimals);
                    }

                    if (negative) value = -value;
                    values.push(value);
                }
                token = "";
            }
            continue;
        }

        if (isOperator(c)) {
            if (values.size() < 2) {
                throw std::runtime_error("Not enough operands for operator");
            }
            double b = values.pop();
            double a = values.pop();
            values.push(applyOperator(c, a, b));
        }
        else {
            token += c;
        }
    }

    if (values.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return values.top();
}

bool ArithmeticExpression::validate() const {
    int parentheses = 0;

    for (int i = 0; i < infixExpression.length(); i++) {
        char c = infixExpression[i];
        if (c == '(') parentheses++;
        if (c == ')') parentheses--;
        if (parentheses < 0) return false;
    }

    return parentheses == 0;
}
#include "arithmetic.h"
#include <iostream>
#include <iomanip>

using namespace std;

void displayMenu() {
    cout << "\n========================================\n";
    cout << "  ARITHMETIC EXPRESSION CALCULATOR\n";
    cout << "========================================\n";
    cout << "1. Enter expression\n";
    cout << "2. Set variables (x, y, z)\n";
    cout << "3. Convert to postfix\n";
    cout << "4. Calculate result\n";
    cout << "5. Show current expression and variables\n";
    cout << "6. Help (supported operations)\n";
    cout << "0. Exit\n";
    cout << "========================================\n";
    cout << "Your choice: ";
}

void displayHelp() {
    cout << "\n========================================\n";
    cout << "         SUPPORTED OPERATIONS\n";
    cout << "========================================\n";
    cout << "Basic operators:\n";
    cout << "  + : Addition\n";
    cout << "  - : Subtraction\n";
    cout << "  * : Multiplication\n";
    cout << "  / : Division\n";
    cout << "  ^ : Power\n\n";
    cout << "Functions:\n";
    cout << "  sin(x) : Sine (in radians)\n";
    cout << "  cos(x) : Cosine (in radians)\n";
    cout << "  tg(x)  : Tangent (in radians)\n";
    cout << "  log(x) : Natural logarithm\n";
    cout << "  exp(x) : Exponential (e^x)\n\n";
    cout << "Variables:\n";
    cout << "  x, y, z : Can be used in expressions\n\n";
    cout << "Examples:\n";
    cout << "  2 + 3 * 4\n";
    cout << "  x + y * z\n";
    cout << "  sin(x) + cos(y)\n";
    cout << "  (x + 3) * 2 - log(y)\n";
    cout << "  2 ^ z + cos(0)\n";
    cout << "========================================\n";
}

int main() {
    ArithmeticExpression expr;
    int choice;
    bool hasExpression = false;

    cout << fixed << setprecision(6);

    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        try {
            switch (choice) {
            case 1: {
                cout << "\nEnter arithmetic expression: ";
                string input;
                getline(cin, input);

                expr.setInfixExpression(input);

                if (!expr.validate()) {
                    cout << "ERROR: Invalid expression (check parentheses)\n";
                    hasExpression = false;
                }
                else {
                    cout << "Expression saved successfully!\n";
                    hasExpression = true;
                }
                break;
            }

            case 2: {
                double x, y, z;
                cout << "\nEnter value for variable x: ";
                cin >> x;
                cout << "Enter value for variable y: ";
                cin >> y;
                cout << "Enter value for variable z: ";
                cin >> z;

                expr.setVariableX(x);
                expr.setVariableY(y);
                expr.setVariableZ(z);

                cout << "Variables set successfully!\n";
                cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
                break;
            }

            case 3: {
                if (!hasExpression) {
                    cout << "ERROR: Please enter an expression first (option 1)\n";
                    break;
                }

                expr.convertToPostfix();
                cout << "\nInfix expression:   " << expr.getInfixExpression() << endl;
                cout << "Postfix expression: " << expr.getPostfixExpression() << endl;
                break;
            }

            case 4: {
                if (!hasExpression) {
                    cout << "ERROR: Please enter an expression first (option 1)\n";
                    break;
                }

                expr.convertToPostfix();
                double result = expr.calculate();

                cout << "\nExpression: " << expr.getInfixExpression() << endl;
                cout << "Variables:  x = " << expr.getVariableX()
                    << ", y = " << expr.getVariableY()
                    << ", z = " << expr.getVariableZ() << endl;
                cout << "Postfix:    " << expr.getPostfixExpression() << endl;
                cout << "Result:     " << result << endl;
                break;
            }

            case 5: {
                if (!hasExpression) {
                    cout << "ERROR: No expression entered yet\n";
                    break;
                }

                cout << "\nCurrent infix expression: " << expr.getInfixExpression() << endl;
                cout << "Variables: x = " << expr.getVariableX()
                    << ", y = " << expr.getVariableY()
                    << ", z = " << expr.getVariableZ() << endl;
                if (!expr.getPostfixExpression().empty()) {
                    cout << "Postfix expression: " << expr.getPostfixExpression() << endl;
                }
                break;
            }

            case 6: {
                displayHelp();
                break;
            }

            case 0: {
                cout << "\nThank you for using the calculator!\n";
                return 0;
            }

            default: {
                cout << "ERROR: Invalid choice. Please select 0-6\n";
                break;
            }
            }
        }
        catch (const exception& e) {
            cout << "\nERROR: " << e.what() << endl;
        }
    }

    return 0;
}
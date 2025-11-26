

#include <iostream>
#include <string>
#include <windows.h>
#include "arithmetic.h"

using namespace std;

void PrintMenu()
{
    cout << "\n=== Calculator ===" << endl;
    cout << "1. Enter new expression" << endl;
    cout << "2. Convert to postfix" << endl;
    cout << "3. Set variables and calculate" << endl;
    cout << "4. Calculate (without variables)" << endl;
    cout << "5. Show current expression" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose action: ";
}

int main()
{
    cout << "Arithmetic Expression Calculator" << endl;
    cout << "Supported operations: +, -, *, /, ^ (power)" << endl;
    cout << "Supported functions: sin, cos, exp, log, tg (tan)" << endl;
    cout << "Brackets and variables (single letter) supported" << endl;
    cout << "\nExpression examples:" << endl;
    cout << "  2+3*4" << endl;
    cout << "  (a+b)*c" << endl;
    cout << "  sin(0)+cos(0)" << endl;
    cout << "  2*sin(a)+3*cos(b)" << endl;
    cout << "  exp(1)+log(2.71828)" << endl;

    TPostfix postfix;
    string expression = "";
    int choice;

    do
    {
        PrintMenu();
        cin >> choice;
        cin.ignore();

        try
        {
            switch (choice)
            {
            case 1:
            {
                cout << "\nEnter arithmetic expression: ";
                getline(cin, expression);
                postfix.SetInfix(expression);
                cout << "Expression accepted: " << expression << endl;
                break;
            }

            case 2:
            {
                if (expression.empty())
                {
                    cout << "Enter expression first!" << endl;
                    break;
                }

                string postfixForm = postfix.ToPostfix();
                cout << "\nInfix form:   " << postfix.GetInfix() << endl;
                cout << "Postfix form: " << postfixForm << endl;
                break;
            }

            case 3:
            {
                if (expression.empty())
                {
                    cout << "Enter expression first!" << endl;
                    break;
                }

                cout << "\nEnter variable values:" << endl;

                // Find all unique variables
                string vars = "";
                for (size_t i = 0; i < expression.length(); i++)
                {
                    char c = expression[i];
                    if (isalpha(c) && vars.find(c) == string::npos)
                    {
                        // Check if it's part of a function name
                        bool isFunc = false;
                        if (i + 2 < expression.length())
                        {
                            string check = expression.substr(i, 3);
                            if (check == "sin" || check == "cos" || check == "exp" || check == "log")
                                isFunc = true;
                        }
                        if (i + 1 < expression.length())
                        {
                            string check = expression.substr(i, 2);
                            if (check == "tg")
                                isFunc = true;
                        }

                        if (!isFunc)
                            vars += c;
                    }
                }

                for (char c : vars)
                {
                    double value;
                    cout << c << " = ";
                    cin >> value;

                    string varName(1, c);
                    postfix.SetOperand(varName, value);
                }

                double result = postfix.Calculate();
                cout << "\nResult: " << result << endl;
                break;
            }

            case 4:
            {
                if (expression.empty())
                {
                    cout << "Enter expression first!" << endl;
                    break;
                }

                double result = postfix.Calculate();
                cout << "\nResult: " << result << endl;
                break;
            }

            case 5:
            {
                if (expression.empty())
                {
                    cout << "Expression not set" << endl;
                }
                else
                {
                    cout << "\nCurrent expression: " << expression << endl;
                    if (!postfix.GetPostfix().empty())
                        cout << "Postfix form: " << postfix.GetPostfix() << endl;
                }
                break;
            }

            case 0:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice! Try again." << endl;
            }
        }
        catch (const char* error)
        {
            cout << "\nError: " << error << endl;
        }
        catch (const string& error)
        {
            cout << "\nError: " << error << endl;
        }
        catch (...)
        {
            cout << "\nUnknown error!" << endl;
        }

    } while (choice != 0);

    return 0;
}
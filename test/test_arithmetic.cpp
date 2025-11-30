#include "arithmetic.h"
#include <gtest.h>
#include <cmath>

const double EPSILON = 1e-6;

class ArithmeticExpressionTest : public ::testing::Test {
protected:
    ArithmeticExpression* expr = nullptr;

    void SetUp() override {
        expr = new ArithmeticExpression();
    }

    void TearDown() override {
        delete expr;
        expr = nullptr;
    }

    bool areEqual(double a, double b) {
        return std::fabs(a - b) < EPSILON;
    }
};

// ========== Тесты конструктора ==========

TEST_F(ArithmeticExpressionTest, DefaultConstructor) {
    EXPECT_EQ(expr->getInfixExpression(), "");
    EXPECT_EQ(expr->getPostfixExpression(), "");
}

TEST_F(ArithmeticExpressionTest, ParameterizedConstructor) {
    ArithmeticExpression expr2("2 + 3");
    EXPECT_EQ(expr2.getInfixExpression(), "2 + 3");
    EXPECT_FALSE(expr2.getPostfixExpression().empty());
}

// ========== Тесты установщика и получателя ==========

TEST_F(ArithmeticExpressionTest, SetAndGetInfixExpression) {
    expr->setInfixExpression("1 + 2");
    EXPECT_EQ(expr->getInfixExpression(), "1 + 2");
}

TEST_F(ArithmeticExpressionTest, SetInfixClearsPostfix) {
    expr->setInfixExpression("1 + 2");
    expr->convertToPostfix();
    EXPECT_FALSE(expr->getPostfixExpression().empty());

    expr->setInfixExpression("3 + 4");
    EXPECT_EQ(expr->getPostfixExpression(), "");
}

// ========== Базовые операции ==========

TEST_F(ArithmeticExpressionTest, BasicAddition) {
    expr->setInfixExpression("2 + 3");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

TEST_F(ArithmeticExpressionTest, BasicSubtraction) {
    expr->setInfixExpression("10 - 4");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 6.0));
}

TEST_F(ArithmeticExpressionTest, BasicMultiplication) {
    expr->setInfixExpression("3 * 4");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 12.0));
}

TEST_F(ArithmeticExpressionTest, BasicDivision) {
    expr->setInfixExpression("15 / 3");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

TEST_F(ArithmeticExpressionTest, PowerOperation) {
    expr->setInfixExpression("2 ^ 3");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 8.0));
}

TEST_F(ArithmeticExpressionTest, PowerOfZero) {
    expr->setInfixExpression("5 ^ 0");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

// ========== Тесты приоритетов ==========

TEST_F(ArithmeticExpressionTest, MultiplicationBeforeAddition) {
    expr->setInfixExpression("2 + 3 * 4");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 14.0));
}

TEST_F(ArithmeticExpressionTest, DivisionBeforeSubtraction) {
    expr->setInfixExpression("20 - 10 / 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 15.0));
}

TEST_F(ArithmeticExpressionTest, PowerHighestPrecedence) {
    expr->setInfixExpression("2 + 3 ^ 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 11.0));
}

// ========== Наличие скобок ==========

TEST_F(ArithmeticExpressionTest, SimpleParentheses) {
    expr->setInfixExpression("(2 + 3) * 4");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 20.0));
}

TEST_F(ArithmeticExpressionTest, NestedParentheses) {
    expr->setInfixExpression("((2 + 3) * (4 + 1))");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 25.0));
}

TEST_F(ArithmeticExpressionTest, MultipleParentheses) {
    expr->setInfixExpression("(5 + 3) * 2 - (4 / 2)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 14.0));
}

// ========== Тесты на десятичные числа ==========

TEST_F(ArithmeticExpressionTest, DecimalAddition) {
    expr->setInfixExpression("3.5 + 2.5");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 6.0));
}

TEST_F(ArithmeticExpressionTest, DecimalMultiplication) {
    expr->setInfixExpression("2.5 * 4.0");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 10.0));
}

// ========== Function Tests: sin ==========

TEST_F(ArithmeticExpressionTest, SineZero) {
    expr->setInfixExpression("sin(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.0));
}

TEST_F(ArithmeticExpressionTest, SinePiOverTwo) {
    expr->setInfixExpression("sin(1.5707963267948966)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

TEST_F(ArithmeticExpressionTest, SineWithExpression) {
    expr->setInfixExpression("sin(3.14159265 / 2)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

// ========== Function Tests: cos ==========

TEST_F(ArithmeticExpressionTest, CosineZero) {
    expr->setInfixExpression("cos(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

TEST_F(ArithmeticExpressionTest, CosinePi) {
    expr->setInfixExpression("cos(3.14159265)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, -1.0));
}

// ========== Function Tests: tg ==========

TEST_F(ArithmeticExpressionTest, TangentZero) {
    expr->setInfixExpression("tg(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.0));
}

TEST_F(ArithmeticExpressionTest, TangentPiOverFour) {
    expr->setInfixExpression("tg(0.7853981633974483)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

// ========== Function Tests: log ==========

TEST_F(ArithmeticExpressionTest, LogarithmE) {
    expr->setInfixExpression("log(2.718281828)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

TEST_F(ArithmeticExpressionTest, LogarithmOne) {
    expr->setInfixExpression("log(1)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.0));
}

// ========== Function Tests: exp ==========

TEST_F(ArithmeticExpressionTest, ExponentialZero) {
    expr->setInfixExpression("exp(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

TEST_F(ArithmeticExpressionTest, ExponentialOne) {
    expr->setInfixExpression("exp(1)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::exp(1.0)));
}

// ========== Тесты на смешанные случаи ==========

TEST_F(ArithmeticExpressionTest, SinePlusCosine) {
    expr->setInfixExpression("sin(0) + cos(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.0));
}

TEST_F(ArithmeticExpressionTest, ComplexFunctionExpression) {
    expr->setInfixExpression("2 * sin(0) + 3 * cos(0)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 3.0));
}

TEST_F(ArithmeticExpressionTest, FunctionWithPower) {
    expr->setInfixExpression("exp(1) + 2 ^ 3");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::exp(1) + 8));
}

// ========== Сложные тесты ==========

TEST_F(ArithmeticExpressionTest, LongExpression) {
    expr->setInfixExpression("1 + 2 + 3 + 4 + 5");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 15.0));
}

TEST_F(ArithmeticExpressionTest, VeryComplexExpression) {
    expr->setInfixExpression("((5 + 3) * 2 - 4 / 2) ^ 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 196.0));
}

// ========== Проверочные тесты ==========

TEST_F(ArithmeticExpressionTest, ValidExpressionSimple) {
    expr->setInfixExpression("(2 + 3)");
    EXPECT_TRUE(expr->validate());
}

TEST_F(ArithmeticExpressionTest, ValidExpressionNested) {
    expr->setInfixExpression("((2 + 3) * (4 - 1))");
    EXPECT_TRUE(expr->validate());
}

TEST_F(ArithmeticExpressionTest, InvalidMissingOpenParenthesis) {
    expr->setInfixExpression("2 + 3)");
    EXPECT_FALSE(expr->validate());
}

TEST_F(ArithmeticExpressionTest, InvalidMissingCloseParenthesis) {
    expr->setInfixExpression("(2 + 3");
    EXPECT_FALSE(expr->validate());
}

TEST_F(ArithmeticExpressionTest, ValidNoParentheses) {
    expr->setInfixExpression("2 + 3 * 4");
    EXPECT_TRUE(expr->validate());
}

// ========== Тесты на исключения ==========

TEST_F(ArithmeticExpressionTest, DivisionByZero) {
    expr->setInfixExpression("5 / 0");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, DivisionByZeroComplex) {
    expr->setInfixExpression("10 / (5 - 5)");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, LogarithmNegative) {
    expr->setInfixExpression("log(-1)");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, LogarithmZero) {
    expr->setInfixExpression("log(0)");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, MismatchedParenthesesConversion) {
    expr->setInfixExpression("(2 + 3");
    EXPECT_THROW(expr->convertToPostfix(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, UnknownFunction) {
    expr->setInfixExpression("foo(5)");
    EXPECT_THROW(expr->convertToPostfix(), std::runtime_error);
}

TEST_F(ArithmeticExpressionTest, EmptyPostfixCalculate) {
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

// ========== Postfix Tests ==========

TEST_F(ArithmeticExpressionTest, PostfixConversionSimple) {
    expr->setInfixExpression("2 + 3");
    expr->convertToPostfix();
    std::string postfix = expr->getPostfixExpression();
    EXPECT_FALSE(postfix.empty());
}

TEST_F(ArithmeticExpressionTest, PostfixWithFunction) {
    expr->setInfixExpression("sin(0)");
    expr->convertToPostfix();
    std::string postfix = expr->getPostfixExpression();
    EXPECT_NE(postfix.find("sin"), std::string::npos);
}

// ========== Крайние случаи  ==========

TEST_F(ArithmeticExpressionTest, SingleNumber) {
    expr->setInfixExpression("42");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 42.0));
}

TEST_F(ArithmeticExpressionTest, ExpressionWithSpaces) {
    expr->setInfixExpression("  2   +   3  ");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

TEST_F(ArithmeticExpressionTest, ChainedDivisions) {
    expr->setInfixExpression("100 / 10 / 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

TEST_F(ArithmeticExpressionTest, AllOperatorsInExpression) {
    expr->setInfixExpression("2 + 3 - 4 * 5 / 2 ^ 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.0));
}



// Тест: Недостаточно операндов для оператора
TEST_F(ArithmeticExpressionTest, NotEnoughOperandsForOperator) {
    expr->setInfixExpression("5 +");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

// Тест: Слишком много операндов (неправильное выражение)
TEST_F(ArithmeticExpressionTest, TooManyOperands) {
    expr->setInfixExpression("5 3");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

// Тест: Парсинг десятичного числа с точкой
TEST_F(ArithmeticExpressionTest, DecimalWithDot) {
    expr->setInfixExpression("1.5");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 1.5));
}

// Тест: Сложное десятичное число
TEST_F(ArithmeticExpressionTest, ComplexDecimalParsing) {
    expr->setInfixExpression("0.123 + 0.456");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.579));
}

// Тест: Скобки без функции
TEST_F(ArithmeticExpressionTest, ParenthesesWithoutFunction) {
    expr->setInfixExpression("(5 + 3) + 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 10.0));
}

// Тест: Множественные функции в скобках
TEST_F(ArithmeticExpressionTest, MultipleFunctionsInParentheses) {
    expr->setInfixExpression("sin(0) + (cos(0) + 1)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 2.0));
}

// Тест: Вложенные функции
TEST_F(ArithmeticExpressionTest, NestedFunctions) {
    expr->setInfixExpression("sin(cos(0))");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::sin(1.0)));
}

// Тест: Функция с вычисляемым аргументом
TEST_F(ArithmeticExpressionTest, FunctionWithComputedArgument) {
    expr->setInfixExpression("sin(2 * 3)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::sin(6.0)));
}

// Тест: Парсинг числа в конце выражения
TEST_F(ArithmeticExpressionTest, NumberAtEnd) {
    expr->setInfixExpression("5.5");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.5));
}

// Тест: Несколько операторов подряд с разным приоритетом
TEST_F(ArithmeticExpressionTest, MixedPrecedenceOperators) {
    expr->setInfixExpression("10 - 5 * 2 + 3");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 3.0));
}

// Тест: Степень с отрицательным результатом
TEST_F(ArithmeticExpressionTest, PowerWithNegativeBase) {
    expr->setInfixExpression("2 ^ 2 ^ 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 16.0));
}

// Тест: Валидация - скобки закрываются раньше открытия
TEST_F(ArithmeticExpressionTest, ValidationClosingBeforeOpening) {
    expr->setInfixExpression(")2 + 3(");
    EXPECT_FALSE(expr->validate());
}

// Тест: Пустое выражение
TEST_F(ArithmeticExpressionTest, EmptyExpression) {
    expr->setInfixExpression("");
    EXPECT_TRUE(expr->validate());
}

// Тест: Выражение только из пробелов
TEST_F(ArithmeticExpressionTest, OnlySpaces) {
    expr->setInfixExpression("     ");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

// Тест: Число с несколькими десятичными точками (только первая учитывается)
TEST_F(ArithmeticExpressionTest, MultipleDecimalPoints) {
    expr->setInfixExpression("3.14.15");
    expr->convertToPostfix();
    // Должно обработать только 3.14, остальное - ошибка
}

// Тест: Оператор в начале (после преобразования может вызвать ошибку)
TEST_F(ArithmeticExpressionTest, OperatorAtStart) {
    expr->setInfixExpression("+ 5");
    expr->convertToPostfix();
    EXPECT_THROW(expr->calculate(), std::runtime_error);
}

// Тест: Все функции с ненулевыми аргументами
TEST_F(ArithmeticExpressionTest, AllFunctionsNonZero) {
    expr->setInfixExpression("sin(1) + cos(1) + tg(1) + log(2) + exp(1)");
    expr->convertToPostfix();
    double result = expr->calculate();
    double expected = std::sin(1) + std::cos(1) + std::tan(1) + std::log(2) + std::exp(1);
    EXPECT_TRUE(areEqual(result, expected));
}

// Тест: Длинная последовательность операций одного приоритета
TEST_F(ArithmeticExpressionTest, LongSequenceSamePriority) {
    expr->setInfixExpression("2 + 2 + 2 + 2 + 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 10.0));
}

// Тест: Очень вложенные скобки
TEST_F(ArithmeticExpressionTest, DeeplyNestedParentheses) {
    expr->setInfixExpression("((((1 + 2))))");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 3.0));
}

// Тест: Проверка getPrecedence для неизвестного оператора
TEST_F(ArithmeticExpressionTest, UnknownOperatorInExpression) {
    expr->setInfixExpression("5 $ 3");
    expr->convertToPostfix();
    // $ не является оператором, будет обработан как ошибка или пропущен
}

// Тест: Функция внутри другой функции
TEST_F(ArithmeticExpressionTest, FunctionInsideFunction) {
    expr->setInfixExpression("exp(log(5))");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

// Тест: Скобки вокруг одного числа
TEST_F(ArithmeticExpressionTest, ParenthesesAroundNumber) {
    expr->setInfixExpression("(42)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 42.0));
}

// Тест: Несколько пар скобок подряд
TEST_F(ArithmeticExpressionTest, MultipleBracketPairs) {
    expr->setInfixExpression("(1 + 2) + (3 + 4) + (5 + 6)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 21.0));
}

// Тест: Операция деления с десятичным результатом
TEST_F(ArithmeticExpressionTest, DivisionWithDecimalResult) {
    expr->setInfixExpression("10 / 4");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 2.5));
}

// Тест: Большое число
TEST_F(ArithmeticExpressionTest, LargeNumber) {
    expr->setInfixExpression("123456 + 654321");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 777777.0));
}

// Тест: Ноль в разных операциях
TEST_F(ArithmeticExpressionTest, ZeroInOperations) {
    expr->setInfixExpression("0 + 0 * 0 + 5");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 5.0));
}

// Тест: Минимальное десятичное число
TEST_F(ArithmeticExpressionTest, SmallDecimal) {
    expr->setInfixExpression("0.0001 + 0.0002");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 0.0003));
}

// Тест: Постфикс содержит правильные элементы
TEST_F(ArithmeticExpressionTest, PostfixContainsCorrectElements) {
    expr->setInfixExpression("2 + 3 * 4");
    expr->convertToPostfix();
    std::string postfix = expr->getPostfixExpression();
    EXPECT_NE(postfix.find("2"), std::string::npos);
    EXPECT_NE(postfix.find("3"), std::string::npos);
    EXPECT_NE(postfix.find("4"), std::string::npos);
    EXPECT_NE(postfix.find("*"), std::string::npos);
    EXPECT_NE(postfix.find("+"), std::string::npos);
}

// Тест: Открывающая скобка без закрывающей (ошибка конвертации)
TEST_F(ArithmeticExpressionTest, UnclosedParenthesisInConversion) {
    expr->setInfixExpression("((2 + 3)");
    EXPECT_THROW(expr->convertToPostfix(), std::runtime_error);
}

// Тест: Закрывающая скобка без открывающей (ошибка конвертации)
TEST_F(ArithmeticExpressionTest, UnmatchedClosingParenthesis) {
    expr->setInfixExpression("2 + 3))");
    EXPECT_THROW(expr->convertToPostfix(), std::runtime_error);
}

// Тест: Все операторы с правильным приоритетом
TEST_F(ArithmeticExpressionTest, AllOperatorsPrecedence) {
    expr->setInfixExpression("1 + 2 * 3 ^ 2 - 4 / 2");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, 17.0)); // 1 + 2*9 - 2 = 17
}

// Тест: Функция log с большим числом
TEST_F(ArithmeticExpressionTest, LogLargeNumber) {
    expr->setInfixExpression("log(100)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::log(100)));
}

// Тест: Функция exp с большим числом
TEST_F(ArithmeticExpressionTest, ExpLargeArgument) {
    expr->setInfixExpression("exp(5)");
    expr->convertToPostfix();
    double result = expr->calculate();
    EXPECT_TRUE(areEqual(result, std::exp(5)));
}
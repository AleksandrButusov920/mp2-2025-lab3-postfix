// тесты для вычисления арифметических выражений

#include "arithmetic.h"
#include <gtest.h>

// Тесты конструктора и базовых методов
TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, can_create_postfix_with_expression)
{
	ASSERT_NO_THROW(TPostfix p("a+b"));
}

TEST(TPostfix, can_get_infix)
{
	TPostfix p("a+b");
	EXPECT_EQ("a+b", p.GetInfix());
}

TEST(TPostfix, can_set_infix)
{
	TPostfix p;
	ASSERT_NO_THROW(p.SetInfix("a+b"));
	EXPECT_EQ("a+b", p.GetInfix());
}

// Тесты преобразования в постфиксную форму
TEST(TPostfix, can_convert_simple_addition)
{
	TPostfix p("a+b");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b + ", postfix);
}

TEST(TPostfix, can_convert_simple_subtraction)
{
	TPostfix p("a-b");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b - ", postfix);
}

TEST(TPostfix, can_convert_simple_multiplication)
{
	TPostfix p("a*b");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b * ", postfix);
}

TEST(TPostfix, can_convert_simple_division)
{
	TPostfix p("a/b");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b / ", postfix);
}

TEST(TPostfix, can_convert_expression_with_priority)
{
	TPostfix p("a+b*c");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b c * + ", postfix);
}

TEST(TPostfix, can_convert_expression_with_parentheses)
{
	TPostfix p("(a+b)*c");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b + c * ", postfix);
}

TEST(TPostfix, can_convert_complex_expression)
{
	TPostfix p("(a+b)*(c-d)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b + c d - * ", postfix);
}

TEST(TPostfix, can_convert_expression_with_multiple_operations)
{
	TPostfix p("a+b-c*d/e");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b + c d * e / - ", postfix);
}

TEST(TPostfix, can_convert_nested_parentheses)
{
	TPostfix p("((a+b)*c)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b + c * ", postfix);
}

TEST(TPostfix, can_convert_expression_with_numbers)
{
	TPostfix p("2+3");
	string postfix = p.ToPostfix();
	EXPECT_EQ("2 3 + ", postfix);
}

TEST(TPostfix, can_convert_expression_with_multi_digit_numbers)
{
	TPostfix p("12+34");
	string postfix = p.ToPostfix();
	EXPECT_EQ("12 34 + ", postfix);
}

TEST(TPostfix, throws_on_mismatched_parentheses_left)
{
	TPostfix p("(a+b");
	ASSERT_ANY_THROW(p.ToPostfix());
}

TEST(TPostfix, throws_on_mismatched_parentheses_right)
{
	TPostfix p("a+b)");
	ASSERT_ANY_THROW(p.ToPostfix());
}

// Тесты вычисления
TEST(TPostfix, can_calculate_simple_addition)
{
	TPostfix p("2+3");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(5.0, result);
}

TEST(TPostfix, can_calculate_simple_subtraction)
{
	TPostfix p("10-3");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(7.0, result);
}

TEST(TPostfix, can_calculate_simple_multiplication)
{
	TPostfix p("4*5");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(20.0, result);
}

TEST(TPostfix, can_calculate_simple_division)
{
	TPostfix p("15/3");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(5.0, result);
}

TEST(TPostfix, can_calculate_expression_with_priority)
{
	TPostfix p("2+3*4");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(14.0, result);
}

TEST(TPostfix, can_calculate_expression_with_parentheses)
{
	TPostfix p("(2+3)*4");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(20.0, result);
}

TEST(TPostfix, can_calculate_complex_expression)
{
	TPostfix p("(10+5)*(8-3)");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(75.0, result);
}

TEST(TPostfix, can_calculate_with_variables)
{
	TPostfix p("a+b");
	p.SetOperand("a", 10);
	p.SetOperand("b", 20);
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(30.0, result);
}

TEST(TPostfix, can_calculate_expression_with_multiple_variables)
{
	TPostfix p("a+b*c");
	p.SetOperand("a", 2);
	p.SetOperand("b", 3);
	p.SetOperand("c", 4);
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(14.0, result);
}

TEST(TPostfix, can_calculate_with_mixed_numbers_and_variables)
{
	TPostfix p("a+5");
	p.SetOperand("a", 10);
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(15.0, result);
}

TEST(TPostfix, throws_on_division_by_zero)
{
	TPostfix p("10/0");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_on_unknown_operand)
{
	TPostfix p("a+b");
	p.SetOperand("a", 10);
	ASSERT_ANY_THROW(p.Calculate());
}

// Дополнительные тесты
TEST(TPostfix, can_handle_spaces_in_expression)
{
	TPostfix p("a + b * c");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a b c * + ", postfix);
}

TEST(TPostfix, can_calculate_negative_result)
{
	TPostfix p("5-10");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(-5.0, result);
}

TEST(TPostfix, can_calculate_with_floating_point_numbers)
{
	TPostfix p("3.5+2.5");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(6.0, result);
}

TEST(TPostfix, can_change_operand_values)
{
	TPostfix p("a+b");
	p.SetOperand("a", 10);
	p.SetOperand("b", 20);
	EXPECT_DOUBLE_EQ(30.0, p.Calculate());

	p.SetOperand("a", 5);
	p.SetOperand("b", 15);
	EXPECT_DOUBLE_EQ(20.0, p.Calculate());
}

TEST(TPostfix, can_reuse_postfix_object)
{
	TPostfix p("a+b");
	p.SetOperand("a", 1);
	p.SetOperand("b", 2);
	EXPECT_DOUBLE_EQ(3.0, p.Calculate());

	p.SetInfix("c*d");
	p.SetOperand("c", 3);
	p.SetOperand("d", 4);
	EXPECT_DOUBLE_EQ(12.0, p.Calculate());
}

TEST(TPostfix, can_calculate_long_expression)
{
	TPostfix p("1+2+3+4+5");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(15.0, result);
}

TEST(TPostfix, respects_operation_priority)
{
	TPostfix p("2+3*4-5");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(9.0, result); // 2 + 12 - 5 = 9
}

TEST(TPostfix, can_handle_multiple_parentheses_levels)
{
	TPostfix p("((2+3)*(4+5))");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(45.0, result);
}

TEST(TPostfix, can_calculate_power_operation)
{
	TPostfix p("2^3");
	double result = p.Calculate();
	EXPECT_DOUBLE_EQ(8.0, result);
}

TEST(TPostfix, power_has_higher_priority_than_multiplication)
{
	TPostfix p("2*3^2");
	string postfix = p.ToPostfix();
	EXPECT_EQ("2 3 2 ^ * ", postfix);
}

// Тесты математических функций
TEST(TPostfix, can_convert_sin_function)
{
	TPostfix p("sin(a)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a sin ", postfix);
}

TEST(TPostfix, can_convert_cos_function)
{
	TPostfix p("cos(a)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a cos ", postfix);
}

TEST(TPostfix, can_convert_exp_function)
{
	TPostfix p("exp(a)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a exp ", postfix);
}

TEST(TPostfix, can_convert_log_function)
{
	TPostfix p("log(a)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a log ", postfix);
}

TEST(TPostfix, can_convert_tg_function)
{
	TPostfix p("tg(a)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("a tg ", postfix);
}

TEST(TPostfix, can_calculate_sin)
{
	TPostfix p("sin(0)");
	double result = p.Calculate();
	EXPECT_NEAR(0.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_sin_pi_div_2)
{
	TPostfix p("sin(1.5707963267948966)"); // π/2
	double result = p.Calculate();
	EXPECT_NEAR(1.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_cos)
{
	TPostfix p("cos(0)");
	double result = p.Calculate();
	EXPECT_NEAR(1.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_exp)
{
	TPostfix p("exp(0)");
	double result = p.Calculate();
	EXPECT_NEAR(1.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_exp_1)
{
	TPostfix p("exp(1)");
	double result = p.Calculate();
	EXPECT_NEAR(2.71828182845904523536, result, 1e-10);
}

TEST(TPostfix, can_calculate_log)
{
	TPostfix p("log(2.71828182845904523536)"); // e
	double result = p.Calculate();
	EXPECT_NEAR(1.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_tg)
{
	TPostfix p("tg(0)");
	double result = p.Calculate();
	EXPECT_NEAR(0.0, result, 1e-10);
}

TEST(TPostfix, can_combine_function_with_operation)
{
	TPostfix p("sin(0)+cos(0)");
	double result = p.Calculate();
	EXPECT_NEAR(1.0, result, 1e-10);
}

TEST(TPostfix, can_calculate_function_with_expression_argument)
{
	TPostfix p("sin(1+1)");
	double result = p.Calculate();
	EXPECT_NEAR(sin(2), result, 1e-10);
}

TEST(TPostfix, can_calculate_nested_functions)
{
	TPostfix p("sin(cos(0))");
	double result = p.Calculate();
	EXPECT_NEAR(sin(1), result, 1e-10);
}

TEST(TPostfix, can_calculate_function_with_variable)
{
	TPostfix p("sin(a)");
	p.SetOperand("a", 0);
	double result = p.Calculate();
	EXPECT_NEAR(0.0, result, 1e-10);
}

TEST(TPostfix, can_multiply_function_result)
{
	TPostfix p("2*sin(0)");
	double result = p.Calculate();
	EXPECT_NEAR(0.0, result, 1e-10);
}

TEST(TPostfix, can_add_function_results)
{
	TPostfix p("sin(0)+cos(0)+exp(0)");
	double result = p.Calculate();
	EXPECT_NEAR(2.0, result, 1e-10); // 0 + 1 + 1 = 2
}

TEST(TPostfix, throws_on_log_of_zero)
{
	TPostfix p("log(0)");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, throws_on_log_of_negative)
{
	TPostfix p("log(-1)");
	ASSERT_ANY_THROW(p.Calculate());
}

TEST(TPostfix, can_calculate_complex_expression_with_functions)
{
	TPostfix p("2*sin(0)+3*cos(0)");
	double result = p.Calculate();
	EXPECT_NEAR(3.0, result, 1e-10); // 2*0 + 3*1 = 3
}

TEST(TPostfix, can_use_tan_instead_of_tg)
{
	TPostfix p("tan(0)");
	string postfix = p.ToPostfix();
	EXPECT_EQ("0 tan ", postfix);
}

TEST(TPostfix, function_works_in_complex_expression)
{
	TPostfix p("(sin(0)+1)*2");
	double result = p.Calculate();
	EXPECT_NEAR(2.0, result, 1e-10); // (0+1)*2 = 2
}
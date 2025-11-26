#include "stack.h"
#include <gtest.h>

// Тесты конструкторов
TEST(TStack, can_create_stack_with_positive_size)
{
    ASSERT_NO_THROW(TStack<int> st(10));
}

TEST(TStack, throws_when_create_stack_with_negative_size)
{
    ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, throws_when_create_too_large_stack)
{
    ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}

TEST(TStack, can_create_copied_stack)
{
    TStack<int> st1(10);
    ASSERT_NO_THROW(TStack<int> st2(st1));
}

TEST(TStack, copied_stack_is_equal_to_source_one)
{
    TStack<int> st1(10);
    st1.Push(5);
    st1.Push(10);

    TStack<int> st2(st1);

    EXPECT_EQ(st1, st2);
}

TEST(TStack, copied_stack_has_its_own_memory)
{
    TStack<int> st1(10);
    st1.Push(5);

    TStack<int> st2(st1);
    st2.Push(10);

    EXPECT_NE(st1, st2);
}

// Тесты методов IsEmpty и IsFull
TEST(TStack, new_stack_is_empty)
{
    TStack<int> st(5);
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, stack_with_elements_is_not_empty)
{
    TStack<int> st(5);
    st.Push(1);
    EXPECT_FALSE(st.IsEmpty());
}

TEST(TStack, full_stack_is_full)
{
    TStack<int> st(3);
    st.Push(1);
    st.Push(2);
    st.Push(3);
    EXPECT_TRUE(st.IsFull());
}

TEST(TStack, not_full_stack_is_not_full)
{
    TStack<int> st(5);
    st.Push(1);
    EXPECT_FALSE(st.IsFull());
}

// Тесты Push
TEST(TStack, can_push_element)
{
    TStack<int> st(5);
    ASSERT_NO_THROW(st.Push(10));
}

TEST(TStack, throws_when_push_to_full_stack)
{
    TStack<int> st(2);
    st.Push(1);
    st.Push(2);
    ASSERT_ANY_THROW(st.Push(3));
}

TEST(TStack, can_push_multiple_elements)
{
    TStack<int> st(5);
    ASSERT_NO_THROW(st.Push(1));
    ASSERT_NO_THROW(st.Push(2));
    ASSERT_NO_THROW(st.Push(3));
}

// Тесты Pop
TEST(TStack, can_pop_element)
{
    TStack<int> st(5);
    st.Push(10);
    ASSERT_NO_THROW(st.Pop());
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
    TStack<int> st(5);
    ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack, pop_returns_last_pushed_element)
{
    TStack<int> st(5);
    st.Push(10);
    EXPECT_EQ(10, st.Pop());
}

TEST(TStack, pop_follows_lifo_order)
{
    TStack<int> st(5);
    st.Push(1);
    st.Push(2);
    st.Push(3);

    EXPECT_EQ(3, st.Pop());
    EXPECT_EQ(2, st.Pop());
    EXPECT_EQ(1, st.Pop());
}

// Тесты GetTop
TEST(TStack, can_get_top_element)
{
    TStack<int> st(5);
    st.Push(10);
    ASSERT_NO_THROW(st.GetTop());
}

TEST(TStack, throws_when_get_top_from_empty_stack)
{
    TStack<int> st(5);
    ASSERT_ANY_THROW(st.GetTop());
}

TEST(TStack, top_returns_last_pushed_element)
{
    TStack<int> st(5);
    st.Push(10);
    st.Push(20);
    EXPECT_EQ(20, st.GetTop());
}

TEST(TStack, top_does_not_remove_element)
{
    TStack<int> st(5);
    st.Push(10);
    st.GetTop();
    EXPECT_EQ(10, st.GetTop());
}

// Тесты GetSize и GetCount
TEST(TStack, can_get_size)
{
    TStack<int> st(10);
    EXPECT_EQ(10, st.GetSize());
}

TEST(TStack, can_get_count)
{
    TStack<int> st(10);
    st.Push(1);
    st.Push(2);
    EXPECT_EQ(2, st.GetCount());
}

TEST(TStack, empty_stack_has_count_zero)
{
    TStack<int> st(10);
    EXPECT_EQ(0, st.GetCount());
}

// Тесты Clear
TEST(TStack, can_clear_stack)
{
    TStack<int> st(10);
    st.Push(1);
    st.Push(2);
    st.Clear();
    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, clear_does_not_change_size)
{
    TStack<int> st(10);
    st.Push(1);
    st.Clear();
    EXPECT_EQ(10, st.GetSize());
}

// Тесты оператора присваивания
TEST(TStack, can_assign_stack_to_itself)
{
    TStack<int> st(5);
    st.Push(10);
    ASSERT_NO_THROW(st = st);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
    TStack<int> st1(5), st2(5);
    st1.Push(10);
    st2 = st1;
    EXPECT_EQ(st1, st2);
}

TEST(TStack, can_assign_stacks_of_different_size)
{
    TStack<int> st1(5), st2(10);
    st1.Push(10);
    ASSERT_NO_THROW(st2 = st1);
}

TEST(TStack, assign_operator_changes_stack_size)
{
    TStack<int> st1(5), st2(10);
    st2 = st1;
    EXPECT_EQ(5, st2.GetSize());
}

TEST(TStack, assigned_stack_is_independent)
{
    TStack<int> st1(5), st2(5);
    st1.Push(10);
    st2 = st1;
    st2.Push(20);
    EXPECT_NE(st1, st2);
}

// Тесты операторов сравнения
TEST(TStack, equal_stacks_are_equal)
{
    TStack<int> st1(5), st2(5);
    st1.Push(1);
    st1.Push(2);
    st2.Push(1);
    st2.Push(2);
    EXPECT_TRUE(st1 == st2);
}

TEST(TStack, stack_equals_itself)
{
    TStack<int> st(5);
    st.Push(10);
    EXPECT_TRUE(st == st);
}

TEST(TStack, stacks_with_different_sizes_are_not_equal)
{
    TStack<int> st1(5), st2(10);
    EXPECT_FALSE(st1 == st2);
}

TEST(TStack, stacks_with_different_elements_are_not_equal)
{
    TStack<int> st1(5), st2(5);
    st1.Push(1);
    st2.Push(2);
    EXPECT_FALSE(st1 == st2);
}

TEST(TStack, not_equal_operator_works)
{
    TStack<int> st1(5), st2(5);
    st1.Push(1);
    st2.Push(2);
    EXPECT_TRUE(st1 != st2);
}

// Дополнительные тесты
TEST(TStack, can_push_and_pop_many_times)
{
    TStack<int> st(5);

    for (int i = 0; i < 5; i++)
        st.Push(i);

    for (int i = 4; i >= 0; i--)
        EXPECT_EQ(i, st.Pop());

    EXPECT_TRUE(st.IsEmpty());
}

TEST(TStack, can_work_with_double)
{
    TStack<double> st(5);
    st.Push(3.14);
    EXPECT_DOUBLE_EQ(3.14, st.Pop());
}

TEST(TStack, can_work_with_char)
{
    TStack<char> st(5);
    st.Push('A');
    st.Push('B');
    EXPECT_EQ('B', st.Pop());
    EXPECT_EQ('A', st.Pop());
}

TEST(TStack, multiple_push_and_pop_operations)
{
    TStack<int> st(10);

    st.Push(1);
    st.Push(2);
    EXPECT_EQ(2, st.Pop());
    st.Push(3);
    st.Push(4);
    EXPECT_EQ(4, st.Pop());
    EXPECT_EQ(3, st.Pop());
    EXPECT_EQ(1, st.Pop());
}
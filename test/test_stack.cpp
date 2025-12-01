#include "stack.h"
#include <gtest.h>
#include <string>

// Тест: Создание стека с конструктором по умолчанию
TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.size(), 0);
}

// Тест: Создание стека с заданной начальной ёмкостью
TEST(StackTest, CustomCapacityConstructor) {
    Stack<int> s(5);
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.size(), 0);
}

// Тест: Добавление одного элемента
TEST(StackTest, PushSingleElement) {
    Stack<int> s;
    s.push(10);
    EXPECT_FALSE(s.isEmpty());
    EXPECT_EQ(s.size(), 1);
}

// Тест: Добавление нескольких элементов
TEST(StackTest, PushMultipleElements) {
    Stack<int> s;
    for (int i = 1; i <= 5; i++) {
        s.push(i * 10);
    }
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s.top(), 50);
}

// Тест: Операция извлечения элемента
TEST(StackTest, PopOperation) {
    Stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    EXPECT_EQ(s.pop(), 30);
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.pop(), 20);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.pop(), 10);
    EXPECT_TRUE(s.isEmpty());
}

// Тест: Операция просмотра верхнего элемента без изменения стека
TEST(StackTest, TopOperation) {
    Stack<int> s;
    s.push(100);

    EXPECT_EQ(s.top(), 100);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 100);
}

// Тест: Top для стека с double значениями
TEST(StackTest, TopWithDouble) {
    Stack<double> s;
    s.push(3.14159);
    s.push(2.71828);

    EXPECT_DOUBLE_EQ(s.top(), 2.71828);
    EXPECT_EQ(s.size(), 2);
}

// Тест: Автоматическое увеличение размера при превышении ёмкости
TEST(StackTest, AutomaticResize) {
    Stack<int> s(2);

    for (int i = 1; i <= 25; i++) {
        s.push(i);
    }

    EXPECT_EQ(s.size(), 25);
    EXPECT_EQ(s.top(), 25);

    for (int i = 25; i >= 1; i--) {
        EXPECT_EQ(s.pop(), i);
    }
}

// Тест: Копирующий конструктор
TEST(StackTest, CopyConstructor) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);

    Stack<int> s2(s1);

    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.top(), 3);

    s2.pop();
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s1.top(), 3);
}

// Тест: Оператор присваивания
TEST(StackTest, AssignmentOperator) {
    Stack<int> s1;
    s1.push(10);
    s1.push(20);
    s1.push(30);

    Stack<int> s2;
    s2.push(100);

    s2 = s1;

    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.top(), 30);

    s2.pop();
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s1.size(), 3);
}

// Тест: Самоприсваивание
TEST(StackTest, SelfAssignment) {
    Stack<int> s;
    s.push(1);
    s.push(2);

    s = s;

    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.top(), 2);
}

// Тест: Операция очистки
TEST(StackTest, ClearOperation) {
    Stack<int> s;
    for (int i = 0; i < 15; i++) {
        s.push(i);
    }

    EXPECT_EQ(s.size(), 15);
    s.clear();
    EXPECT_TRUE(s.isEmpty());
    EXPECT_EQ(s.size(), 0);

    s.push(42);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 42);
}

// Тест: Стек со строками
TEST(StackTest, StringOperations) {
    Stack<std::string> s;

    s.push("Hello");
    s.push("World");
    s.push("!");

    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.pop(), "!");
    EXPECT_EQ(s.pop(), "World");
    EXPECT_EQ(s.pop(), "Hello");
    EXPECT_TRUE(s.isEmpty());
}

// Тест: Стек с символами
TEST(StackTest, CharOperations) {
    Stack<char> s;

    s.push('A');
    s.push('B');
    s.push('C');

    EXPECT_EQ(s.top(), 'C');
    EXPECT_EQ(s.pop(), 'C');
    EXPECT_EQ(s.pop(), 'B');
    EXPECT_EQ(s.pop(), 'A');
}

// Тест: Pop из пустого стека выбрасывает исключение
TEST(StackTest, PopEmptyStackException) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), std::runtime_error);
}

// Тест: Top на пустом стеке выбрасывает исключение
TEST(StackTest, TopEmptyStackException) {
    Stack<int> s;
    EXPECT_THROW(s.top(), std::runtime_error);
}

// Тест: Множественные исключения
TEST(StackTest, MultipleExceptions) {
    Stack<int> s;

    EXPECT_THROW(s.pop(), std::runtime_error);
    EXPECT_THROW(s.top(), std::runtime_error);

    s.push(1);
    EXPECT_NO_THROW(s.pop());

    EXPECT_THROW(s.pop(), std::runtime_error);
}

// Тест: Большое количество операций (нагрузочный тест)
TEST(StackTest, StressTest) {
    Stack<int> s;
    const int iterations = 1000;

    for (int i = 0; i < iterations; i++) {
        s.push(i);
    }

    EXPECT_EQ(s.size(), iterations);

    for (int i = iterations - 1; i >= 0; i--) {
        EXPECT_EQ(s.pop(), i);
    }

    EXPECT_TRUE(s.isEmpty());
}

// Тест: Чередующиеся операции push и pop
TEST(StackTest, AlternatingOperations) {
    Stack<int> s;

    s.push(1);
    EXPECT_EQ(s.pop(), 1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.pop(), 3);
    s.push(4);
    EXPECT_EQ(s.size(), 2);
}

// Тест: Консистентность проверки isEmpty
TEST(StackTest, IsEmptyConsistency) {
    Stack<int> s;

    EXPECT_TRUE(s.isEmpty());
    s.push(1);
    EXPECT_FALSE(s.isEmpty());
    s.pop();
    EXPECT_TRUE(s.isEmpty());
}

// Тест: Консистентность размера
TEST(StackTest, SizeConsistency) {
    Stack<int> s;

    EXPECT_EQ(s.size(), 0);
    for (int i = 0; i < 10; i++) {
        s.push(i);
        EXPECT_EQ(s.size(), i + 1);
    }
    for (int i = 9; i >= 0; i--) {
        EXPECT_EQ(s.size(), i + 1);
        s.pop();
    }
    EXPECT_EQ(s.size(), 0);
}


// Тест: Копирующий конструктор с пустым стеком
TEST(StackTest, CopyConstructorEmptyStack) {
    Stack<int> s1;
    Stack<int> s2(s1);

    EXPECT_TRUE(s2.isEmpty());
    EXPECT_EQ(s2.size(), 0);
}

// Тест: Присваивание пустого стека
TEST(StackTest, AssignmentEmptyStack) {
    Stack<int> s1;
    s1.push(1);

    Stack<int> s2;
    s1 = s2;

    EXPECT_TRUE(s1.isEmpty());
}

// Тест: Push после очистки
TEST(StackTest, PushAfterClear) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.clear();
    s.push(3);

    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.top(), 3);
}

// Тест: Множественная очистка
TEST(StackTest, MultipleClear) {
    Stack<int> s;
    s.push(1);
    s.clear();
    s.clear();

    EXPECT_TRUE(s.isEmpty());
}

// Тест: Конструктор с большой начальной ёмкостью
TEST(StackTest, LargeCapacityConstructor) {
    Stack<int> s(1000);
    EXPECT_TRUE(s.isEmpty());
    s.push(42);
    EXPECT_EQ(s.top(), 42);
}

// Тест: Стек с отрицательными числами
TEST(StackTest, NegativeNumbers) {
    Stack<int> s;
    s.push(-10);
    s.push(-20);
    s.push(-30);

    EXPECT_EQ(s.pop(), -30);
    EXPECT_EQ(s.pop(), -20);
    EXPECT_EQ(s.pop(), -10);
}

// Тест: Стек с нулём
TEST(StackTest, WithZero) {
    Stack<int> s;
    s.push(0);

    EXPECT_EQ(s.top(), 0);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.pop(), 0);
}

// НЕТ main() - его предоставит gtest_main при линковке
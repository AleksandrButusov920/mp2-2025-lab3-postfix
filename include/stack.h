// UNN, VMK, Course "Programming Methods-2", C++, OOP
//
// stack.h - Copyright (c) Gergel V.P. 07.05.2001
//   Revised for Microsoft Visual Studio 2008 by Sysoev A.V. (19.04.2015)
//
// Stack based on dynamic array

#ifndef __STACK_H__
#define __STACK_H__

const int MaxStackSize = 100;

template <class T>
class TStack
{
    T* pMem;
    int Size;
    int Top;
public:
    TStack(int s = 10);
    TStack(const TStack& st);
    ~TStack();

    TStack& operator=(const TStack& st);

    bool operator==(const TStack& st) const;
    bool operator!=(const TStack& st) const;

    bool IsEmpty() const { return Top == -1; }
    bool IsFull() const { return Top == Size - 1; }

    void Push(const T& val);
    T Pop();
    T GetTop() const;

    int GetSize() const { return Size; }
    int GetCount() const { return Top + 1; }

    void Clear() { Top = -1; }
};

template <class T>
TStack<T>::TStack(int s)
{
    if (s <= 0 || s > MaxStackSize)
        throw "Invalid stack size";

    Size = s;
    Top = -1;
    pMem = new T[Size];
}

template <class T>
TStack<T>::TStack(const TStack<T>& st)
{
    Size = st.Size;
    Top = st.Top;
    pMem = new T[Size];

    for (int i = 0; i <= Top; i++)
        pMem[i] = st.pMem[i];
}

template <class T>
TStack<T>::~TStack()
{
    delete[] pMem;
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack<T>& st)
{
    if (this == &st)
        return *this;

    if (Size != st.Size)
    {
        delete[] pMem;
        Size = st.Size;
        pMem = new T[Size];
    }

    Top = st.Top;
    for (int i = 0; i <= Top; i++)
        pMem[i] = st.pMem[i];

    return *this;
}

template <class T>
bool TStack<T>::operator==(const TStack<T>& st) const
{
    if (Size != st.Size || Top != st.Top)
        return false;

    for (int i = 0; i <= Top; i++)
        if (pMem[i] != st.pMem[i])
            return false;

    return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack<T>& st) const
{
    return !(*this == st);
}

template <class T>
void TStack<T>::Push(const T& val)
{
    if (IsFull())
        throw "Stack overflow";

    pMem[++Top] = val;
}

template <class T>
T TStack<T>::Pop()
{
    if (IsEmpty())
        throw "Stack underflow";

    return pMem[Top--];
}

template <class T>
T TStack<T>::GetTop() const
{
    if (IsEmpty())
        throw "Stack is empty";

    return pMem[Top];
}

#endif
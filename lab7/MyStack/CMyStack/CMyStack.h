#pragma once
#include <algorithm>

template <typename T>
class CMyStack
{
public:
	CMyStack() noexcept;
	CMyStack(const CMyStack<T>&);
	CMyStack(CMyStack<T>&&) noexcept;
	~CMyStack() noexcept;
	bool Empty() const;
	T& Top() const;
	void Push(const T&);
	int Size()const noexcept;
	void Pop();
	void Clear() noexcept;
	CMyStack<T>& operator=(const CMyStack<T>&);
	CMyStack<T>& operator=(CMyStack<T>&&) noexcept;
private:
	void SwapStack(CMyStack<T>&) noexcept;
private:
	struct StackNode
	{
		T m_data;
		StackNode* m_prev;
		StackNode(const T& _data, StackNode* _prev) 
			:m_data(_data), m_prev(_prev) {}
	};
	StackNode* m_top;
	int m_size;
};

template <typename T>
CMyStack<T>::CMyStack() noexcept
	:m_top(nullptr), m_size(0)
{}

template <typename T>
CMyStack<T>::CMyStack(const CMyStack& from)
{
	if (from.Empty())
	{
		return;
	}
	CMyStack tempStack;
	StackNode* nodeFrom = from.m_top;
	StackNode* prev = nullptr;

	while (nodeFrom != nullptr)
	{
		StackNode* nodeNew = new StackNode(nodeFrom->m_data, nullptr);

		if (prev == nullptr)
		{
			tempStack.m_top = nodeNew;
		}
		else
		{
			prev->m_prev = nodeNew;
		}

		prev = nodeNew;
		nodeFrom = nodeFrom->m_prev;
		++tempStack.m_size;
	}
	
	SwapStack(tempStack);
}

template <typename T>
CMyStack<T>::CMyStack(CMyStack<T>&& stack) noexcept
	: m_size(stack.m_size)
	, m_top(stack.m_top)
{
	stack.m_size = 0;
	stack.m_top = nullptr;
}

template <typename T>
CMyStack<T>::~CMyStack() noexcept
{
	Clear();
}

template <typename T>
bool CMyStack<T>::Empty()const
{
	return m_size == 0;
}

template<typename T>
T& CMyStack<T>::Top()const 
{
	if (Empty())
	{
		throw std::logic_error("Stack is empty");
	}
	return m_top->m_data;
}

template<typename T>
void CMyStack<T>::Push(const T& value) 
{
	m_top = new StackNode(value, m_top);
	++m_size;
}

template<typename T>
int CMyStack<T>::Size()const noexcept
{
	return m_size;
}

template<typename T>
void CMyStack<T>::Pop()
{
	if (Empty())
	{
		throw std::logic_error("Stack is empty");
	}
	StackNode* temp = m_top;
	m_top = m_top->m_prev;
	delete temp;
	--m_size;
}

template<typename T>
void CMyStack<T>::Clear() noexcept
{
	while (!Empty())
	{
		Pop();
	}
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator=(CMyStack<T>&& stack) noexcept
{
	if (&stack != this)
	{
		Clear();
		SwapStack(stack);
	}
	return *this;
}

template <typename T>
CMyStack<T>& CMyStack<T>::operator=(const CMyStack<T>& stack)
{
	if (&stack != this)
	{
		CMyStack tempStack(stack);
		SwapStack(tempStack);
	}
	return *this;
}

template <typename T>
void CMyStack<T>::SwapStack(CMyStack<T>& stack) noexcept
{
	std::swap(m_size, stack.m_size);
	std::swap(m_top, stack.m_top);
}

#pragma once
//#include <cstddef>

template <typename T>
class CMyStack
{
public:
	CMyStack() noexcept;
	~CMyStack() noexcept;
	bool Empty() const;
	T& Top() const;
	void Push(const T& value);
	int Size()const;
	/*
	void Pop();
	void Clear();*/
private:
	template<typename Ty>
	struct Stack_Node {
		Ty m_data;
		Stack_Node* m_next;
		Stack_Node(const Ty& _data, const Stack_Node* _next) :m_data((Ty)_data), m_next((Stack_Node*)_next) {}
	};
	Stack_Node<T>* m_top;
	int m_size;
};

template <typename T>
CMyStack<T>::CMyStack() noexcept
	:m_top(nullptr), m_size(0)
{}

template <typename T>
CMyStack<T>::~CMyStack() noexcept
{
	Stack_Node<T>* temp = m_top;
	while (m_top) {
		m_top = m_top->m_next;
		delete temp;
		temp = m_top;
	}
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
	m_top = new Stack_Node<T>(value, m_top);
	++m_size;
}

template<typename T>
int CMyStack<T>::Size()const
{
	return m_size;
}

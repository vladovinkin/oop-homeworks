#pragma once
//#include <cstddef>

template <typename T>
class CMyStack
{
public:
	CMyStack();
	~CMyStack();
	bool Empty() const;
	/*void Push(const T value);
	void Pop();
	T& Top();
	void Clear();*/
private:
	template<typename Ty>
	struct Stack_Node {
		Ty data;
		Stack_Node* next;
		Stack_Node(const Ty& _data, const Stack_Node* _next) :data((Ty)_data), next((Stack_Node*)_next) {}
	};
	Stack_Node<T>* top;
	int size;
};

template <typename T>
CMyStack<T>::CMyStack()
	:top(nullptr), size(0)
{}

template <typename T>
CMyStack<T>::~CMyStack()
{
	Stack_Node<T>* temp = top;
	while (top) {
		top = top->next;
		delete temp;
		temp = top;
	}
}

template <typename T>
bool CMyStack<T>::Empty()const
{
	return size == 0;
}

#pragma once

template <typename T>
class CMyStack
{
public:
	CMyStack();
	~CMyStack();
	void Push(T elem);
	void Pop();
	T Top();
	bool IsEmpty();
	void Clear();
private:
	T* stackPtr;
	int size;
	T top;
};
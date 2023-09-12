#pragma once
#include <memory>

template<typename type>
class Stack
{
private:
	int m_size = 0;
	int m_capacity;
	type* m_elements;
public:
	Stack(int new_size);
	Stack(const Stack& other);
	~Stack();
	type& top();
	type pop();
	void push(type new_el);
	int GetSize();
	type operator[](const int index) const;
	type& operator[](const int index);
	inline bool IsEmpty() { if (m_size <= 0) return true; else return false; };
};

template<typename type>
inline Stack<type>::Stack(int new_size): m_capacity{new_size}
{
	m_elements = new type[new_size];
}

template<typename type>
inline Stack<type>::Stack(const Stack& other):m_size(other.m_size),m_capacity(other.m_capacity)
{
	m_elements = new type[m_capacity];
	memcpy(m_elements, other.m_elements, other.m_capacity);
}

template<typename type>
inline Stack<type>::~Stack()
{
	delete[] m_elements;
}

template<typename type>
inline type& Stack<type>::top()
{
	return m_elements[m_size-1];
}

template<typename type>
inline type Stack<type>::pop()
{
	type temp = m_elements[m_size-1];
	m_elements[m_size-1] = -1;
	m_size--;
	return temp;

}

template<typename type>
inline void Stack<type>::push(type new_el)
{
	int new_capacity = 1 + m_capacity * 1.5;
	if (m_size >= m_capacity) {

		type* new_elements = new type[new_capacity];

		for (int i = 0; i < m_capacity; i++)
		{
			//std::cout << m_elements[i] << std::endl;
			new_elements[i] = m_elements[i];
			//std::cout << new_elements[i] << std::endl;
		}
		m_capacity = new_capacity;
		delete[] m_elements;
		m_elements = new_elements;
	}
	
	m_elements[m_size] = new_el;
	m_size++;
}

template<typename type>
inline int Stack<type>::GetSize()
{
	return this->m_size;
}

template<typename type>
type Stack<type>::operator[](const int index) const
{
	try {
		if (index >= m_size) throw "Index out of range!";
		return this->m_elements[index % m_size];
	}
	catch (const char* e) {
		std::cerr << e << std::endl;
		return this->m_elements[0];
	}
}

template<typename type>
type& Stack<type>::operator[](const int index)
{
	try {
		if (index >= m_size) throw "Index out of range!";
		return this->m_elements[index % m_size];
	}
	catch (const char* e) {
		std::cerr << e << std::endl;
		return this->m_elements[0];
	}
}
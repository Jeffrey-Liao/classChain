#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <typeinfo>
using namespace std;
template<class TYPE>
class Node
{
protected:
	TYPE m_data;
protected:
	Node()
	{}
	Node(const TYPE Default):m_data(Default)
	{}
	~Node()
	{}
public:
	inline bool data_Empty() const
	{
		if (m_data)
			return 1;
		else
			return 0;
	}
	inline TYPE data_Read()
	{
		return m_data;
	}
	inline void set_Data(TYPE inData)
	{
		m_data = inData;
	}
	std::string get_typeid()
	{
		return typeid(m_data).name();
	}
};
#endif
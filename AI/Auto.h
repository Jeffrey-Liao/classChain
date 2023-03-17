#pragma once
#ifndef AUTO_H
#define AUTO_H
#include <typeinfo>
#include <iostream>
namespace Manipulate
{
#define NAMEINT "int"
#define NAMEFLOAT "float"
#define NAMEDOUBLE "double"
#define NAMELONG "__int64"
#define NAMESTRING "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >"
#define ASINT *(int*)
#define ASFLOAT *(float*)
#define ASDOUBLE *(double*)
#define ASCHAR *(char*)
#define ASSTRING *(string*)
#define ASLONG *(long long*)
	using namespace std;
	enum class AutoTypes
	{
		EMPTY,
		INT,
		FLOAT,
		DOUBLE,
		CHAR,
		STRING,
		LONG,
		STRUCT
	};
	/*template <class TYPE>
		void Assign(TYPE InData);
		void Assign(Auto& Data);
		bool Set(AutoTypes InType, auto InData)
		{
			Type = InType;
			if (InType == AutoTypes::INT)
				Assign<int>(InData);
			else if (InType == AutoTypes::FLOAT)
				Assign<float>(InData);
			else if (InType == AutoTypes::DOUBLE)
				Assign<double>(InData);
			else if (InType == AutoTypes::CHAR)
				Assign<char>(InData);
			else if (InType == AutoTypes::LONG)
				Assign<long long>(InData);
			else if (InType == AutoTypes::STRING)
				Assign<string>(&InData);
			else
				return 0;
			return 1;
					Auto() :Data(0), Type(AutoTypes::EMPTY), Const(0)
		{}
		Auto(const auto InData) :Const(0)
		{
			Set(Case(InData), InData);
		}
		Auto(const auto InData, bool SetConst) :Const(SetConst)
		{
			Set(Case(InData), InData);
		}
		Auto(const Auto& Other)
		{
			if (Data != NULL)
				delete Data;
			Assign(Other);
		}
		bool Clear()
		{

		}
		inline bool Empty()
		{
			if (Data)
				return 0;
			else
				return 1;
		}
		inline bool isConst()
		{
			if (Const)
				return 1;
			else
				return 0;
		}
		Auto& operator=(const auto InData)
		{
			Assign(InData);
		}
		template <class TYPE>
		const TYPE As() const
		{
			return this->*(TYPE*)Data;
		}
		~Auto()
		{
			delete Data;
			Type = AutoTypes::EMPTY;
			Const = 0;
		}
		}*/
	class Auto
	{
	private:
		void* Data;
		AutoTypes Type;
		bool Const;
		//Varviable
	public:
		Auto():Type(AutoTypes::EMPTY),Const(0),Data(nullptr)
		{
		}
	};
}
#endif
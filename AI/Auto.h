#pragma once
#ifndef AUTO_H
#define AUTO_H
#include <typeinfo>
#include <iostream>
namespace Manipulate
{
#define NAMEINT "int"
#define NAMECHAR "char"
#define NAMEFLOAT "float"
#define NAMEDOUBLE "double"
#define NAMELONG "__int64"
#define NAMEUNSIGN "unsigned int"
#define NAMESTRING "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >"
#define ASINT *(int*)
#define ASUNSIGNED *(unsigned int*)
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
		UNSIGNED,
		FLOAT,
		DOUBLE,
		CHAR,
		STRING,
		LONG,
		STRUCT
	};
	class Auto
		{
	private:
		void* Data;
		AutoTypes Type;
		bool Const;
		//Varviable
	private:
		template<class TYPE>
		void Assign(TYPE inData, bool inConst=0)
		{
			if (Data != NULL)
				delete Data;
			Data = new TYPE;
			*(TYPE*)Data = inData;
			string Typeid = typeid(inData).name();
			if (Typeid == NAMEINT)
				Type = AutoTypes::INT;
			else if (Typeid == NAMEUNSIGN)
				Type = AutoTypes::UNSIGNED;
			else if (Typeid == NAMECHAR)
				Type = AutoTypes::CHAR;
			else if (Typeid == NAMEFLOAT)
				Type = AutoTypes::FLOAT;
			else if (Typeid == NAMEDOUBLE)
				Type = AutoTypes::DOUBLE;
			else if (Typeid == NAMESTRING)
				Type = AutoTypes::STRING;
			else if (Typeid == NAMELONG)
				Type = AutoTypes::LONG;
			else
				Type = AutoTypes::STRUCT;
			Const = inConst;
		}
	public:
		Auto() :Type(AutoTypes::EMPTY), Const(0), Data(NULL)
		{}
		 Auto(int inData,bool inConst = 0)
		{
			Assign<int>(inData, inConst);
		}
		Auto(char inData, bool inConst = 0)
		{
			Assign<char>(inData, inConst);
		}
		Auto(double inData, bool inConst = 0)
		{
			Assign<double>(inData, inConst);
		}
		 Auto(float inData, bool inConst = 0)
		{
			Assign<float>(inData, inConst);
		}
		Auto(unsigned int inData, bool inConst = 0)
		{
			Assign<unsigned int>(inData, inConst);
		}
		Auto(long long inData, bool inConst = 0)
		{
			Assign<long long>(inData, inConst);
		}
		Auto(string inData, bool inConst = 0)
		{
			Assign<string>(inData, inConst);
		}
		constexpr Auto& operator = (Auto& inData)
		{
			if(inData.Type == AutoTypes::INT)
				Assign<int>(ASINT inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::CHAR)
				Assign<char>(ASCHAR inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::FLOAT)
				Assign<float>(ASFLOAT inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::DOUBLE)
				Assign<double>(ASDOUBLE inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::STRING)
				Assign<string>(ASSTRING inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::LONG)
				Assign<long long>(ASLONG inData.Data, inData.Const);
			else if (inData.Type == AutoTypes::UNSIGNED)
				Assign<unsigned int>(ASUNSIGNED inData.Data, inData.Const);
			return *this;
		}
		template <class TYPE>
		void operator= (TYPE inData)
		{
			 Assign<TYPE>(inData);
		}
		int operator=(int inData)
		{
			Assign<int>(inData);
			return ASINT(Data);
		}
		char operator=(char inData)
		{
			Assign<char>(inData);
			return ASCHAR(Data);
		}
		float operator= (float inData)
		{
			Assign<float>(inData);
			return ASFLOAT(Data);
		}
		double operator= (double inData)
		{
			Assign<double>(inData);
			return ASDOUBLE(Data);
		}
		string operator= (string inData)
		{
			Assign<string>(inData);
			return ASSTRING(Data);
		}
		long long operator= (long long inData)
		{
			Assign<long long>(inData);
			return ASLONG(Data);
		}
		unsigned int operator= (unsigned int inData)
		{
			Assign<unsigned int>(inData);
			return ASUNSIGNED(Data);
		}
		friend ostream& operator<<(ostream& Out, Auto& Obj)
	{
			if (Obj.Type == AutoTypes::INT)
				Out << ASINT(Obj.Data);
			else if (Obj.Type == AutoTypes::CHAR)
				Out << ASCHAR(Obj.Data);
			else if (Obj.Type == AutoTypes::FLOAT)
				Out << ASFLOAT(Obj.Data);
			else if (Obj.Type == AutoTypes::DOUBLE)
				Out << ASDOUBLE(Obj.Data);
			else if (Obj.Type == AutoTypes::LONG)
				Out << ASLONG(Obj.Data);
			else if (Obj.Type == AutoTypes::UNSIGNED)
				Out << ASUNSIGNED(Obj.Data);
			else if (Obj.Type == AutoTypes::STRING)
				Out << ASSTRING(Obj.Data);
			return Out;
		}
		~Auto()
		{
			delete this->Data;
			this->Type = AutoTypes::EMPTY;
			this->Const = false;
		}
	};
}
#endif
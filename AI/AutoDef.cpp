#include "Auto.h"
void Auto::Assign(Auto& InData)
{
	delete this->Data;
	if (!this->Const)
		this->Type = InData.Type;
	if (InData.Type == AutoTypes::INT)
	{
		this->Data = new int;
		ASINT this->Data = ASINT InData.Data;
	}
	else if (InData.Type == AutoTypes::FLOAT)
	{
		this->Data = new float;
		ASFLOAT this->Data = ASFLOAT InData.Data;
	}
	else if (InData.Type == AutoTypes::DOUBLE)
	{
		this->Data = new double;
		ASDOUBLE this->Data = ASDOUBLE InData.Data;
	}
	else if (InData.Type == AutoTypes::CHAR)
	{
		this->Data = new char;
		ASCHAR this->Data = ASCHAR InData.Data;
	}
	else if (InData.Type == AutoTypes::LONG)
	{
		this->Data = new long long;
		ASLONG this->Data = ASLONG InData.Data;
	}
	else if (InData.Type == AutoTypes::STRING)
	{
		this->Data = new string;
		ASSTRING this->Data = ASSTRING InData.Data;
	}
}
template <class TYPE>
void Auto::Assign(TYPE InData)
{
	Data = new TYPE;
	*(TYPE*)Data = InData;
}
namespace Manipulate
{

}

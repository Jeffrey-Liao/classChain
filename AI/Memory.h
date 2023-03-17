#pragma once
#ifndef MEMO_H
#define MEMO_H
namespace Manipulate
{
#define BACK_(x,y) x=x>>y;
#define BACK(x,y) x>>y;
#define PUSH_(x,y) x=x<<y;
#define PUSH(x,y) x<<y;
#define FULL (unsigned int)~0
#define MEMOSIZE(Data) (_msize(Data)/sizeof(*Data))
	const int EMPTY = 0;
	template<class TYPE>
	class Allocator
	{

		TYPE* Space;
		unsigned int* DataInfor;
		int Focus;
#define ALLOSIZE MEMOSIZE(Space)
	public:
		int size()
		{
			return int(MEMOSIZE(Space));
		}
	private:
		void Extend(TYPE* OldSpace,unsigned int* OldField)
		{
			for (int n = 0;n!=MEMOSIZE(OldSpace);n++)
				this->Space[n] = OldSpace[n];
			for (int n = 0; n != MEMOSIZE(OldField); n++)
				this->DataInfor[n] = OldField[n];
		}
		void Clearify()
		{
			for (int n = 0; n != MEMOSIZE(DataInfor); n++)
				this->DataInfor[n] = 0;
		}
		int Compare(TYPE* Pos)
		{
			int totalSize = this->size();
			if (totalSize % 2 != 0)
				totalSize = totalSize / 2 + 1;
			else
				totalSize = totalSize / 2;
			for (int n =0;n!=totalSize;n++)
			{
				if ((Space + n) == Pos)
					return n;
				if ((Space + (totalSize - (n + 1))) == Pos)
					return (totalSize)-(n + 1);
			}
			return -1;
		}
	public:
		bool Full()
		{
			bool result = true;
			unsigned int signal = PUSH(1,this->size());
			for (int n = 0; n != MEMOSIZE(DataInfor); n++)
				result = result && signal == DataInfor[n];
			return result;
		}
		Allocator():Space(NULL),DataInfor(NULL)
		{}
		TYPE* Allocate(int size)
		{
			TYPE* Pos;
			if (Space == NULL)
			{
				Pos = Space = new TYPE[size];
				DataInfor = new unsigned int;
				Clearify();
			}
			else
			{
				TYPE* temp = Space;
				unsigned int* tempsize = this->DataInfor;
				int totalSize = this->size();
				Space = new TYPE[totalSize + size];
				Pos = Space + totalSize;
				if (size / 32)
					this->DataInfor = new unsigned int[totalSize + size];
				Clearify();
				Extend(temp, tempsize);
			}
			return Pos;
		}
		explicit Allocator(int size)
		{
			Allocate(size);
		}
		void DeAllocate(TYPE* Position)
		{

		}
		void Clear()
		{
			delete this->Space;
			delete this->DataInfor;
		}
		~Allocator()
		{
			this->Clear();
		}
	};
}
#endif
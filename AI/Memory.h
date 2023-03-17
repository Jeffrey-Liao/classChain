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
#define MEMOSIZE(Data) (_msize(Data)/sizeof(Data))
	const int EMPTY = 0;
	template<class TYPE>
	class Allocator
	{
		TYPE* Space;
		unsigned int* DataInfor;
		void Allocate()
		{
			auto UnAllo = &Space;
			if (Space)
			{
				auto Data = Space;
				int GoalSize = (_msize(*Space) / sizeof(TYPE)) * 2;
				*UnAllo = new int[GoalSize];
				for (int n = 0; n != GoalSize; n++)
				{
					if (GoalSize / 2)
						*UnAllo[n] = Data[n];
					else
						*UnAllo[n] = TYPE(0);
				}
				delete[] Data;
			}
			else
				*UnAllo = new int;
		}
	public:
		TYPE* Ask(int size)
		{
			
		}
		TYPE* Delete(TYPE* Address)
		{

		}
	};
}
#endif
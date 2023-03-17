#pragma once
#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
using namespace std;
namespace Manipulate
{
	template<class TYPE>
	class Matrix
	{
		vector<TYPE*> Points;
	public:
		Matrix()
		{
		}
		Matrix(int Line,int Column)
		{
			for(int n = 0;n!= Column;n++)
				Points.push_back(new int[Line]);
		}
		vector<TYPE*>& operator[](int Pos)
		{
			return Points[Pos];
		}
		void Transposition()
		{
			vector<TYPE*>old = Points;
			Points.clear();
			for (int n = 0, *TempVector,size = old.size(); n != _msize(old[0]); n++)
			{
				TempVector = new int[size];
				for (int m = 0;m!=size;m++)
				{
					TempVector[n] = old[n][m];
				}
				Points.push_back(TempVector);
			}
		}
		~Matrix()
		{
			Points.clear();
		}
	};
}
#endif
#pragma once
#include <vector>
#define SQUARE(x)(x*x)
using namespace std;
struct Sample
{
	
};
class ZhongBao
{
	int  Punishment(vector<int> Predict, vector<int> Real)
	{
		int Index = 0;
		for (int n = 0; n != Predict.size(); n++)
			Index +=SQUARE(Predict[n] - Real[n]);
		Index /= Predict.size();
		return Index;
	}
};
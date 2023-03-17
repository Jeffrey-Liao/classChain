#include<array>
#include <list>
#include <iostream>
#include <typeinfo>
#include "./Chain.h"
#define SIZE 

using namespace Manipulate;
using namespace std;
typedef long long S64;
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
class test
{
public:
	int a;
	int b;
};
int main()
{
	Chain<int>Test;
	vector<int> Test2;
	int temp;
	for (int n = 0; n != 100; n++)
	{
		Test.Append(n);
	}
	temp = Test.Locate(30)->data_Read();
	Test.Destroy();
}
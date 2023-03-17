#include<array>
#include <list>
#include <iostream>
#include <typeinfo>
#include <time.h>
#include "./Chain.h"
#define SIZE 
#define WAN 100000
#define TENWAN WAN*10
#define MILLION 100000000
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
	Chain<int> Test;
	for(int n = 0;n!= MILLION;n++)
		Test.Append(n);
	cout << Test;
}
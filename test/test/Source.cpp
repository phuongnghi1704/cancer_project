#include "QInt.h"
#include <string>

void main()
{
	QInt a;
	a.setBit(1, 1);
	a.setBit(1, 4);
	string str;
	str=a.QInt_to_Bin();
	getline(cin, str);
	system("pause");
	
}
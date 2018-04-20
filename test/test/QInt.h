#pragma once
#include <iostream>
#include <string>
using namespace std;
string HexStringToBinString(string hex);
string BinStringToBHexString(string bin);
void StrDiv2(string &Dec);
int ChartoInt(char c);

class QInt
{
	 int arrayBits[4];
	
public:
	QInt();
	QInt(const QInt&);
	~QInt();
	bool getBit(int i)
	{
		int x = arrayBits[i / 32];
		return (x >> (i % 32)) & 1;
	}


	void turnOn(int i)
	{
		arrayBits[i / 32] |= (1 << (i % 32));

	}

	void turnOff(int i)
	{
		arrayBits[i / 32] &= ~(1 << (i % 32));
	}

	void TurnBitOn(int &x, int i)
	{
		x |= (1 << i);
	}

	string QIntToBin();
	bool BinToQInt(string bin);

	string QIntToHex();
	bool HexToQInt(string hex);

	bool DecToQInt(string dec);
	string QIntToDec();

	int findLastNumberOne();
	string Print(int n);
	bool Scan(string str, int n);


	QInt Bu1();
	QInt Bu2();

	QInt& operator=(const QInt&);
	QInt operator+(QInt&);
	QInt operator-(QInt&);
	QInt operator*(QInt&);
	QInt operator/(QInt);
	QInt operator%(QInt);

	QInt operator&(QInt b);
	QInt operator|(QInt b);
	QInt operator^(QInt b);
	QInt operator~();

	QInt operator<<(int j)
	{
		QInt result = *this;
		for (int i = 0; i <= 3; i++)
			result.arrayBits[i] = this->arrayBits[i] << j;

		return result;
	}

	QInt operator>>(int j)
	{
		QInt result = *this;
		for (int i = 0; i <= 3; i++)
			result.arrayBits[i] = this->arrayBits[i] >> j;

		return result;
	}
};


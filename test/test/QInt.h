#pragma once
#include <iostream>
using namespace std;

int ChartoInt(char c);

class QInt
{
	long long arrayBits[2];
	

	
public:
	QInt();
	QInt(const QInt&);
	~QInt();
	bool getBit(int i)
	{
		int x = arrayBits[i / 64];
		return (x >> (i % 64)) & 1;
	}

	void setBit(long long bit, int i)
	{
		if (bit == 1)
			arrayBits[i / 64] |= (1 << 63-(i % 64));
		arrayBits[i / 64] &= ~(1 << (63-i % 64));
	}
	
	void turnOn(int i)
	{
		arrayBits[i / 64] |= (1 << 63 - (i % 64));

	}

	void turnOff(int i)
	{
		arrayBits[i / 64] &= ~(1 << (63 - i % 64));
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


	QInt Bu1();
	QInt Bu2();

	QInt& operator=(const QInt&);
	QInt operator+(QInt&);
	QInt operator-(QInt&);
	QInt operator*(QInt&);
	QInt operator/(QInt&);

	QInt operator&(QInt b);
	QInt operator|(QInt b);
	QInt operator^(QInt b);
	QInt operator~();

	QInt operator<<(int j)
	{
		QInt result = *this;
		for (int i = 0; i <= 1; i++)
			result.arrayBits[i] = this->arrayBits[i] << j;

		return result;
	}

	QInt operator>>(int j)
	{
		QInt result = *this;
		for (int i = 0; i <= 1; i++)
			result.arrayBits[i] = this->arrayBits[i] >> j;

		return result;
	}
};


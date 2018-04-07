#pragma once
#include <iostream>
using namespace std;


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

	string QInt_to_Bin();
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


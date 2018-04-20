#include "QInt.h"

//Reference: https://codescracker.com/cpp/program/cpp-program-convert-hexadecimal-to-binary.htm

int ChartoInt(char c)
{
	return (int)c - 48;
}


string HexStringToBinString(string hex)
{
	string bin = "";
	for (int i = 0; i < hex.length(); i++)
	{
		switch (toupper(hex[i]))
		{
		case '0': bin.append("0000"); break;
		case '1': bin.append("0001"); break;
		case '2': bin.append("0010"); break;
		case '3': bin.append("0011"); break;
		case '4': bin.append("0100"); break;
		case '5': bin.append("0101"); break;
		case '6': bin.append("0110"); break;
		case '7': bin.append("0111"); break;
		case '8': bin.append("1000"); break;
		case '9': bin.append("1001"); break;
		case 'A': bin.append("1010"); break;
		case 'B': bin.append("1011"); break;
		case 'C': bin.append("1100"); break;
		case 'D': bin.append("1101"); break;
		case 'E': bin.append("1110"); break;
		case 'F': bin.append("1111"); break;
		}
	}
	return bin;
}

string BinStringToBHexString(string bin)
{
	string hex = "";
	string tmp = "0000";
	for (int j = 0; j < 128; j += 4)
	{
		tmp = bin.substr(j, 4);
		if (!tmp.compare("0000")) bin += "0";
		else if (!tmp.compare("0001")) hex += "1";
		else if (!tmp.compare("0010")) hex += "2";
		else if (!tmp.compare("0011")) hex += "3";
		else if (!tmp.compare("0100")) hex += "4";
		else if (!tmp.compare("0101")) hex += "5";
		else if (!tmp.compare("0110")) hex += "6";
		else if (!tmp.compare("0111")) hex += "7";
		else if (!tmp.compare("1000")) hex += "8";
		else if (!tmp.compare("1001")) hex += "9";
		else if (!tmp.compare("1010")) hex += "A";
		else if (!tmp.compare("1011")) hex += "B";
		else if (!tmp.compare("1100")) hex += "C";
		else if (!tmp.compare("1101")) hex += "D";
		else if (!tmp.compare("1110")) hex += "E";
		else if (!tmp.compare("1111")) hex += "F";
		else continue;
	}

	return hex;
}


QInt::QInt()
{
	arrayBits[0] = arrayBits[1] = arrayBits[2] = arrayBits[3] = 0;
}

QInt::QInt(const QInt& a)
{
	for (int i = 0; i < 4; i++)
		arrayBits[i] = a.arrayBits[i];
}

QInt::~QInt()
{
}

int QInt::findLastNumberOne()
{
	for (int i = 127; i >= 0; i--)
	{
		if (this->getBit(i) == 1)
			return i;
	}
	return 0;
}


string QInt::QIntToBin()
{
	string Bin = "";
		for (int i = 0; i < 128; i++)
		{
			if (getBit(i) == 0)
				Bin.insert(0, "0");
			else
				Bin.insert(0, "1");
		}
	return Bin;
}

bool QInt::BinToQInt(string bin)
{
	//Nếu ko đủ 128 bit thì add 0 vào đầu chuỗi
	
	if (bin.length() < 128)
	{
		int n = bin.length();
		for (int i = n; i < 128; i++)
		{
			bin.insert(0,"0");
		}
	}
	for (int i = 0; i < 128; i++)
	{
		if (bin.at(abs(i-127))=='0') turnOff(i);
		else turnOn(i);
	}
	return true;
}

string QInt::QIntToHex()
{
	string bin = QIntToBin();
	string hex = BinStringToBHexString(bin);
	return hex;
}

bool QInt::HexToQInt(string hex)
{
	string bin = HexStringToBinString(hex);
	this->BinToQInt(bin);
	return true;

}

string QInt::QIntToDec()
{
	if (arrayBits[0] == 0 && arrayBits[1] == 0 && arrayBits[2] == 0 && arrayBits[3] == 0) return "0";
	int sign = 1; //1 là dương, -1 là âm
	int d;
	string dec="";
	QInt A, temp = *this, ten;

	if (getBit(127) == 1)
	{
		sign = -1;
		temp = temp.Bu1();
	}
	for (int i = 0; i < 128; i++)
	{
		A = temp % ten;
		for (int i = 0; i < 4; i++)
		{
			if (A.getBit(i) == 1)
				TurnBitOn(d, i);		//lưu từng 4 bit của A vào biến d
		}

		temp = temp / ten;
		dec.insert(0, to_string(d)); //chuyển d thành chuỗi rồi add vào dec
		d = 0; 
	}

	if (sign == -1)
	{
		dec.insert(0, "-");
	}
	return dec;
}

bool QInt::DecToQInt(string dec) {
	int sign = 1;
	if (dec[0] == '-')
	{
		dec.erase(0, 1);
		sign = -1;
	}
	for (int i = 0; i < 128; i++)
	{
		if (ChartoInt(dec[dec.length() -1]) % 2 == 1)
		{
			this->turnOn(i);
		}
		StrDiv2(dec);
	}
	if (dec.length() > 1) //When input is more than 128 bit
		return false;

	if (sign == -1)
		*this = this->Bu2(); //When input is neagtive
	return true;

}

void StrDiv2(string &Dec)
{

	if (Dec[0] < '2' && Dec.length() == 1) //when Dec is less than 2
	{
		Dec[0] = '0';
		return;
	}
	string res = "";
	int t = 0;
	for (int i = 0, len = Dec.length(); i < len; ++i) {
		t = t * 10 + (Dec[i] - '0');
		res += (t / 2) + '0';
		t %= 2;
	}
	int l = res.length() - 1;
	for (int i = 0; i < res.length() - 1; ++i)
		if (res[i] != '0')
		{
			l = i;
			break;
		}
	Dec.clear();
	Dec= res.substr(l);
}

QInt QInt::Bu1()
{
	QInt obj;
	for (int i = 0; i < 128; i++)
	{
		if (this->getBit(i) == 1) obj.turnOff(i);
		else obj.turnOn(i);
	}
	return obj;
}

QInt QInt::Bu2()
{
	QInt bu1 = this->Bu1();
	QInt one;
	one.turnOn(0);
	QInt obj = bu1 + one;
	return obj;
}

string QInt::Print(int n)
{
	if (n == 2)
	{
		int len = findLastNumberOne();
		string bin = "";

		for (int i = 0; i <= len; i++)
		{
			if (getBit(i) == 0)
				bin.insert(0, "0");
			else
				bin.insert(0, "1");
		}
		return bin;
	}

	if (n == 10)
	{
		string temp = this->QIntToDec();
		return temp;
	}
	if (n == 16)
	{
		string str = this->QIntToBin();
		return BinStringToBHexString(str);
	}
	return NULL;
}


QInt& QInt::operator = (const QInt &num)
{
	if (this == &num)
		return *this;

	for (int i = 0; i < 4; i++)
		this->arrayBits[i] = num.arrayBits[i];
	return *this;
}

QInt QInt::operator+(QInt &a)
{
	QInt res;
	int carry = 0;

	for (int i = 0; i < 128; i++)
	{
		if (carry == 0)
		{
			if (this->getBit(i) == 0 && a.getBit(i) == 0)
				res.turnOff(i);
			else if (this->getBit(i) == 1 && a.getBit(i) == 1) {
				carry = 1;
				res.turnOff(i);
			}
			else res.turnOn(i);
		}
		else
		{
			if (this->getBit(i) == 0 && a.getBit(i) == 0)
			{
				res.turnOn(i);
				carry = 0;
			}

			else if (this->getBit(i) == 1 && a.getBit(i) == 1) {
				res.turnOn(i);
				carry = 1;
			}

			else
			{
				res.turnOff(i);
				carry = 1;
			}
		}
	}
	return res;

}

QInt QInt::operator - (QInt &a)
{
	QInt bu2 = a.Bu2();
	return *this + bu2;
}

QInt QInt::operator * (QInt &obj)
{
	QInt A;
	int Q1 = 0;
	int count = 128;
	QInt Q = obj;
	do
	{

		if (Q.getBit(0) == 0 && Q1 == 1) A = A + *this;
		if (Q.getBit(0) == 1 && Q1 == 0) A = A - *this;

		Q1 = Q.getBit(0);

		// dịch bit của Q
		for (int j = 1; j < 128; j++)
		{
			if (Q.getBit(j) == 1) Q.turnOn(j - 1);
			else Q.turnOff(j - 1);

		}

		// dịch bit phải nhất của A thành bit trái nhất của Q
		if (A.getBit(0) == 1) Q.turnOn(127);
		else Q.turnOff(127);

		// dịch bit của A
		for (int j = 1; j < 128; j++)
		{
			if (A.getBit(j) == 1) A.turnOn(j - 1);
			else A.turnOff(j - 1);

		}

		count--;

	} 
	while (count > 0);


	return Q;

}

QInt QInt::operator/(QInt obj)
{
	QInt A;
	QInt M = obj;
	QInt Q = *this;
	int count = 128, sign=1;

	if (M.getBit(127) + Q.getBit(127) == 1)
		sign = -1;
	if (M.getBit(127) == 1) M = M.Bu2();

	if (Q.getBit(127) == 1) Q = Q.Bu2();

	do
	{
		//dịch trái A

		for (int i = 126; i >= 0; i--)
		{
			if (A.getBit(i) == 0) A.turnOff(i + 1);
			else A.turnOn(i + 1);
		}

		//dịch bit trái nhất của Q thành bit phải nhất của A

			if (Q.getBit(127) == 1) A.turnOn(0);
			else A.turnOff(0);
		// dịch trái Q

			for (int j = 126; j >= 0; j--)
			{
				if (Q.getBit(j) == 0) Q.turnOff(j + 1);
				else Q.turnOn(j + 1);
			}

				Q.turnOff(0);

			A = A - M;

			if (A.getBit(127) == 1)
			{
				Q.turnOff(0);
				A = A + M;
			}

			else Q.turnOn(0);

			count--;

	} 
	while (count > 0);

	if (sign == -1) Q = Q.Bu2();
	return Q;

}

QInt QInt::operator%(QInt obj)
{
	QInt A;
	QInt M = obj;
	QInt Q = *this;
	int count = 128, sign = 1;

	if (M.getBit(127) + Q.getBit(127) == 1)
		sign = -1;
	if (M.getBit(127) == 1) M = M.Bu2();

	if (Q.getBit(127) == 1) Q = Q.Bu2();

	do
	{
		//dịch trái A

		for (int i = 126; i >= 0; i--)
		{
			if (A.getBit(i) == 0) A.turnOff(i + 1);
			else A.turnOn(i + 1);
		}

		//dịch bit trái nhất của Q thành bit phải nhất của A

		if (Q.getBit(127) == 1) A.turnOn(0);
		else A.turnOff(0);
		// dịch trái Q

		for (int j = 126; j >= 0; j--)
		{
			if (Q.getBit(j) == 0) Q.turnOff(j + 1);
			else Q.turnOn(j + 1);
		}

		Q.turnOff(0);

		A = A - M;

		if (A.getBit(127) == 1)
		{
			Q.turnOff(0);
			A = A + M;
		}

		else Q.turnOn(0);

		count--;

	} while (count > 0);

	if (sign == -1) Q = Q.Bu2();
	return A;
}

QInt QInt::operator&(QInt b)
{
	QInt result, a = *this;
	for (int i = 0; i < 4; i++)
	{
		result.arrayBits[i] = a.arrayBits[i] & b.arrayBits[i];
	}
	return result;
}

QInt QInt::operator|(QInt b)
{
	QInt result, a = *this;
	for (int i = 0; i < 4; i++)
	{
		result.arrayBits[i] = a.arrayBits[i] | b.arrayBits[i];
	}
	return result;
}

QInt QInt::operator^(QInt b)
{
	QInt result, a = *this;
	for (int i = 0; i < 4; i++)
	{
		result.arrayBits[i] = a.arrayBits[i] ^ b.arrayBits[i];
	}
	return result;
}

QInt QInt::operator~()
{
	QInt a = *this, result;
	for (int i = 0; i < 4; i++)
	{
		result.arrayBits[i] = ~a.arrayBits[i];
	}
	return result;
}



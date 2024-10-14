/*
#pragma once
class BigInt
{
public:
	char* Big;

	//think about the private data members
public:
	int BigSize;
	BigInt(int val);
	BigInt(const string& text);
	BigInt(const BigInt& copy); // copy constructor
	// Binary Operators
	// Arithmetic Operators
	BigInt operator+(const BigInt& val) const;
	BigInt operator+(int val) const;
	BigInt operator-(const BigInt& val) const;
	BigInt operator-(int val) const;
	BigInt operator*(const BigInt& val) const;
	// Compound Assignment Operators
	BigInt operator+=(const BigInt& rhs);
	BigInt operator-=(const BigInt& rhs);
	BigInt operator*=(const BigInt& rhs);
	BigInt operator*=(int num);
	// Logical Operators
	bool operator==(const BigInt& val) const;
	bool operator==(const char* val) const;
	bool operator!=(const BigInt& val) const;
	bool operator<(const BigInt& val) const;
	bool operator<=(const BigInt& val) const;
	bool operator>(const BigInt& val) const;
	bool operator>=(const BigInt& val) const;
	// Unary Operators
	BigInt& operator++(); // Pre-increment Operator
	BigInt operator++(int); // Post-increment Operator
	BigInt& operator--(); // Pre-decrement Operator
	BigInt operator--(int); // Post-decrement Operator

	//Conversion Operator
	operator string(); // return value of the BigInt as string
	operator int(); // return the number of digits in big Integer

	friend ostream& operator<<(ostream& output, const BigInt& val); // outputs the BigInt
	friend istream& operator>>(istream& input, BigInt& val); // inputs the BigInt

	~BigInt(); // destructor
};

BigInt::BigInt(int val = 0)
{
	BigSize = 0;
	int temp = val;
	if (val == 0)
	{
		BigSize++;
	}
	while (temp != 0)
	{
		BigSize++;
		temp /= 10;
	}
	Big = new char[BigSize + 1];
	for (int init = 0; init < BigSize; init++)
	{
		Big[init] = '0';
	}
	Big[BigSize] = '\0';
	for (int Zero = BigSize - 1; Zero >= 0; Zero--)
	{
		Big[Zero] = char((val % 10) + 48);
		val /= 10;
	}
}

BigInt::BigInt(const BigInt& copy)
{
	BigSize = copy.BigSize;
	Big = new char[BigSize + 1];
	Big[BigSize] = '\0';
	for (int same = 0; same < BigSize + 1; same++)
	{
		Big[same] = copy.Big[same];
	}
}

BigInt::BigInt(const string& text)
{
	BigSize = 0;
	while (text[BigSize] != '\0')
	{
		BigSize++;
	}
	Big = new char[BigSize + 1];
	Big[BigSize] = '\0';;
	for (int copy = 0; copy < BigSize; copy++)
	{
		Big[copy] = text[copy];
	}
}

BigInt BigInt::operator+(const BigInt& val) const
{
	BigInt Add;
	BigInt Temp;
	if (val.BigSize > BigSize)
	{
		Temp.BigSize = val.BigSize + 1;
	}
	else
	{
		Temp.BigSize = BigSize + 1;
	}
	Temp.Big = new char[Temp.BigSize + 1];
	Temp.Big[Temp.BigSize] = '\0';
	Temp.Big[0] = 0;
	int add1 = BigSize - 1, add2 = val.BigSize - 1;
	int carry = 0;
	for (int i = Temp.BigSize - 1; i >= 0; i--)
	{
		if (i == 0 && (add1 != 0 || add2 != 0))
		{
			carry += 48;
			Temp.Big[0] = char(carry);
			break;
		}
		else if (add1 == 0 && add2 < 0)
		{
			Temp.Big[i] = Big[add1] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 < 0 && add2 == 0)
		{
			Temp.Big[i] = val.Big[add2] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 != 0 && add2 < 0)
		{
			while (add1 >= 0)
			{
				Temp.Big[i] = Big[add1] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add1--;
				i--;
			}
			if (carry != 0 && i == 0)
			{
				Temp.Big[i] = carry + 48;
			}
			break;
		}
		else if (add2 != 0 && add1 < 0)
		{
			while (add2 >= 0)
			{
				Temp.Big[i] = val.Big[add2] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add2--;
				i--;
			}
			if (carry != 0 && i == 0)
			{
				Temp.Big[i] = carry + 48;
			}
			break;
		}
		int a = Big[add1], b = val.Big[add2];
		a -= 48;
		b -= 48;
		a += b;
		a += carry;
		if (a >= 10)
		{
			a -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		a += 48;
		Temp.Big[i] = char(a);
		add1--;
		add2--;
	}
	if (Temp.Big[0] == '0' || Temp.Big[0] == 0)
	{
		Add.BigSize = Temp.BigSize - 1;
	}
	else
	{
		return Temp;
	}
	Add.Big = new char[Add.BigSize + 1];
	Add.Big[Add.BigSize] = '\0';
	int copy = Temp.BigSize - 1;
	for (int i = Add.BigSize - 1; i >= 0; i--)
	{
		Add.Big[i] = Temp.Big[copy];
		copy--;
	}
	return Add;
}

BigInt BigInt::operator+(int val) const
{
	BigInt Add;
	BigInt Temp;
	BigInt rhs(val);
	if (rhs.BigSize > BigSize)
	{
		Temp.BigSize = rhs.BigSize + 1;
	}
	else
	{
		Temp.BigSize = BigSize + 1;
	}
	Temp.Big = new char[Temp.BigSize + 1];
	Temp.Big[Temp.BigSize] = '\0';
	Temp.Big[0] = 0;
	int add1 = BigSize - 1, add2 = rhs.BigSize - 1;
	int carry = 0;
	for (int i = Temp.BigSize - 1; i >= 0; i--)
	{
		if (i == 0 && (add1 != 0 || add2 != 0))
		{
			carry += 48;
			Temp.Big[0] = char(carry);
			break;
		}
		else if (add1 == 0 && add2 < 0)
		{
			Temp.Big[i] = Big[add1] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 < 0 && add2 == 0)
		{
			Temp.Big[i] = rhs.Big[add2] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 != 0 && add2 < 0)
		{
			while (add1 >= 0)
			{
				Temp.Big[i] = Big[add1] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add1--;
				i--;
			}
			break;
		}
		else if (add2 != 0 && add1 < 0)
		{
			while (add2 >= 0)
			{
				Temp.Big[i] = rhs.Big[add2] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add2--;
				i--;
			}
			break;
		}
		int a = Big[add1], b = rhs.Big[add2];
		a -= 48;
		b -= 48;
		a += b;
		a += carry;
		if (a >= 10)
		{
			a -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		a += 48;
		Temp.Big[i] = char(a);
		add1--;
		add2--;
	}
	if (Temp.Big[0] == '0' || Temp.Big[0] == 0)
	{
		Add.BigSize = Temp.BigSize - 1;
	}
	else
	{
		return Temp;
	}
	Add.Big = new char[Add.BigSize + 1];
	Add.Big[Add.BigSize] = '\0';
	int copy = Temp.BigSize - 1;
	for (int i = Add.BigSize - 1; i >= 0; i--)
	{
		Add.Big[i] = Temp.Big[copy];
		copy--;
	}
	return Add;
}

BigInt BigInt::operator-(const BigInt& val) const
{
	BigInt Sub;
	int carry = 0;
	if (BigSize > val.BigSize)
	{
		Sub.BigSize = BigSize;
	}
	else
	{
		Sub.BigSize = val.BigSize;
	}
	Sub.Big = new char[Sub.BigSize + 1];
	Sub.Big[Sub.BigSize] = '\0';
	int size1 = val.BigSize - 1;
	int size2 = BigSize - 1;
	int newsize = Sub.BigSize - 1;
	if (size1 > size2 || ((size1 == size2) && (val.Big[0] > Big[0])))
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (val.Big[size1] >= Big[size2] + carry)
				{
					Sub.Big[newsize] = val.Big[size1] - Big[size2] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - Big[size2] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (val.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = val.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
		BigInt Temp;
		Temp.BigSize = Sub.BigSize + 2;
		Temp.Big = new char[Sub.BigSize + 2];
		Temp.Big[Sub.BigSize + 1] = '\0';
		for (int copy = 1; copy < Sub.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Sub.Big[copy - 1];
		}
		Temp.Big[Sub.BigSize + 1] = Sub.Big[Sub.BigSize];
		Temp.Big[0] = '-';
		delete[] Sub.Big;
		Sub = Temp;
	}
	else
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (Big[size2] >= val.Big[size1] + carry)
				{
					int n = Big[size2] - val.Big[size1] - carry + 48;
					Sub.Big[newsize] = n;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - val.Big[size1] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (val.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = val.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
	}
	return Sub;
}

BigInt BigInt::operator-(int val) const
{
	BigInt Sub;
	BigInt rhs(val);
	int carry = 0;
	if (BigSize > rhs.BigSize)
	{
		Sub.BigSize = BigSize;
	}
	else
	{
		Sub.BigSize = rhs.BigSize;
	}
	(string)Sub = new char[Sub.BigSize + 1];
	Sub.Big[Sub.BigSize] = '\0';
	int size1 = rhs.BigSize - 1;
	int size2 = BigSize - 1;
	int newsize = Sub.BigSize - 1;
	if (size1 > size2 || ((size1 == size2) && (rhs.Big[0] > Big[0])))
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (rhs.Big[size1] >= Big[size2] + carry)
				{
					Sub.Big[newsize] = rhs.Big[size1] - Big[size2] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - Big[size2] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (rhs.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
		BigInt Temp;
		Temp.BigSize = Sub.BigSize + 2;
		Temp.Big = new char[Sub.BigSize + 2];
		Temp.Big[Sub.BigSize + 1] = '\0';
		for (int copy = 1; copy < Sub.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Sub.Big[copy - 1];
		}
		Temp.Big[Sub.BigSize + 1] = Sub.Big[Sub.BigSize];
		Temp.Big[0] = '-';
		delete[] Sub.Big;
		Sub = Temp;
	}
	else
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (Big[size2] >= rhs.Big[size1] + carry)
				{
					Sub.Big[newsize] = Big[size2] - rhs.Big[size1] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - rhs.Big[size1] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (rhs.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
	}
	return Sub;
}

BigInt BigInt::operator*(const BigInt& val) const
{
	BigInt Mult;
	BigInt rhs = val;
	int neg1 = 0, neg2 = 0;
	if (Big[0] == '-' && rhs.Big[0] != '-')
	{
		neg1 = 1;
	}
	if (Big[0] != '-' && rhs.Big[0] == '-')
	{
		neg2 = 1;
	}
	if (Big[0] == '-' && rhs.Big[0] == '-')
	{
		neg1 = 1;
		neg2 = 1;
	}
	Mult.BigSize = BigSize + rhs.BigSize - 1;
	Mult.Big = new char[Mult.BigSize + 1];
	for (int init = 0; init < Mult.BigSize; init++)
	{
		Mult.Big[init] = 0;
	}
	Mult.Big[Mult.BigSize] = '\0';
	int overflow = 0;
	int size1 = BigSize;
	int size2 = rhs.BigSize;
	int carry = 0;
	for (int prod = size1 - 1; prod >= neg1; prod--)
	{
		for (int uct = size2 - 1; uct >= neg2; uct--)
		{
			if (Mult.Big[uct + prod] >= 48 && Mult.Big[uct + prod] <= 57)
			{
				Mult.Big[uct + prod] -= 48;
			}
			if (((rhs.Big[uct] - 48) * (Big[prod] - 48)) + carry + 48 > 127)
			{
				int temp = (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48 - 57;
				int temp2 = temp;
				carry = 0;
				while (temp > 0)
				{
					carry++;
					temp -= 10;
				}
				Mult.Big[uct + prod] += temp2 - (carry * 10) + 57;
			}
			else if (((rhs.Big[uct] - 48) * (Big[prod] - 48)) + carry + 48 + (int)Mult.Big[uct + prod] > 127)
			{
				int temp = (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48 - 57 + (int)Mult.Big[uct + prod];
				int temp2 = temp;
				carry = 0;
				while (temp > 0)
				{
					carry++;
					temp -= 10;
				}
				Mult.Big[uct + prod] = temp2 - (carry * 10) + 57;
			}
			else
			{
				Mult.Big[uct + prod] += (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48;
				carry = 0;
				if (Mult.Big[uct + prod] > 57)
				{
					int temp = Mult.Big[uct + prod] - 57;
					while (temp > 0)
					{
						carry++;
						temp -= 10;
					}
					Mult.Big[uct + prod] -= (carry * 10);
				}
			}
		}
		if (carry != 0 && prod > neg1)
		{
			Mult.Big[neg2 + prod - 1] += carry;
			carry = 0;
		}
	}
	if (carry != 0)
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize + 2;
		Temp.Big = new char[Mult.BigSize + 2];
		Temp.Big[Mult.BigSize + 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Mult.Big[copy - 1];
		}
		Temp.Big[Mult.BigSize + 1] = Mult.Big[Mult.BigSize];
		Temp.Big[neg1 + neg2] = carry + 48;
		delete[] Mult.Big;
		Mult = Temp;
	}
	if ((neg1 == 1 && neg2 == 0) || (neg1 == 0 && neg2 == 1))
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
		Mult.Big[0] = '-';
	}
	else if (neg1 == 1 && neg2 == 1)
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
	}
	while (Mult.Big[0] == '0' && Mult.Big[1] != '\0')
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
	}
	return Mult;
}

BigInt BigInt::operator+=(const BigInt& rhs)
{
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator-=(const BigInt& rhs)
{
	*this = *this - rhs;
	return *this;
}

BigInt BigInt::operator*=(const BigInt& rhs)
{
	*this = *this * rhs;
	return *this;
}

BigInt BigInt::operator*=(int num)
{
	BigInt Mult;
	int remainder = 0;
	if (Big[0] >= '5')
	{
		Mult.BigSize = BigSize + 1;
	}
	else
	{
		Mult.BigSize = BigSize;
	}
	Mult.Big = new char[Mult.BigSize + 1];
	Mult.Big[Mult.BigSize] = '\0';
	int copy2 = BigSize - 1;
	for (int copy = Mult.BigSize - 1; copy >= 0; copy--)
	{
		int digit = Big[copy2];
		digit -= 48;
		digit *= 2;
		digit += remainder;
		if (digit >= 10)
		{
			remainder = 1;
			digit -= 10;
		}
		else
		{
			remainder = 0;
		}
		digit += 48;
		Mult.Big[copy] = char(digit);
		copy2--;
		if (copy2 == -1 && copy != 0)
		{
			Mult.Big[0] = char(remainder + 48);
			break;
		}
	}
	*this = Mult;
	return *this;
}

bool BigInt::operator==(const BigInt& val) const
{
	int counter = 0;
	if (BigSize == val.BigSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val.Big[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return true;
		}
	}
	return false;
}

bool BigInt::operator==(const char* val) const
{
	int counter = 0, valSize = 0;
	while (val[valSize] != '\0')
	{
		valSize++;
	}
	if (BigSize == valSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return true;
		}
	}
	return false;
}

bool BigInt::operator!=(const BigInt& val) const
{
	int counter = 0;
	if (BigSize == val.BigSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val.Big[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return false;
		}
	}
	return true;
}

bool BigInt::operator<(const BigInt& val) const
{
	int compare = 0;
	if (Big == val.Big)
	{
		return false;
	}
	if (BigSize == val.BigSize)
	{
		while (Big[compare] <= val.Big[compare])
		{
			if (Big[compare] < val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return false;
			}
		}
		return false;
	}
	else if (BigSize > val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator<=(const BigInt& val) const
{
	int compare = 0;
	if (BigSize == val.BigSize)
	{
		while (Big[compare] <= val.Big[compare])
		{
			if (Big[compare] < val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return true;
			}
		}
		if (compare == BigSize)
		{
			return true;
		}
		return false;
	}
	else if (BigSize > val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator>(const BigInt& val) const
{
	int compare = 0;
	if (Big == val.Big)
	{
		return false;
	}
	if (BigSize == val.BigSize)
	{
		while (Big[compare] >= val.Big[compare])
		{
			if (Big[compare] > val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return false;
			}
		}
		return false;
	}
	else if (BigSize < val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator>=(const BigInt& val) const
{
	int compare = 0;
	if (BigSize == val.BigSize)
	{
		while (Big[compare] >= val.Big[compare])
		{
			if (Big[compare] > val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return true;
			}
		}
		if (compare == BigSize)
		{
			return true;
		}
		return false;
	}
	else if (BigSize < val.BigSize)
	{
		return false;
	}
	return true;
}

BigInt& BigInt::operator++()
{
	*this = *this + 1;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt temp(*this);
	*this = *this + 1;
	return temp;
}

BigInt& BigInt::operator--()
{
	*this = *this - 1;
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt temp(*this);
	*this = *this - 1;
	return temp;
}

BigInt::operator string()
{
	return Big;
}

BigInt::operator int()
{
	return BigSize;
}

ostream& operator<<(ostream& output, const BigInt& val)
{
	for (int cout = 0; cout < val.BigSize; cout++)
	{
		output << val.Big[cout];
	}
	return output;
}

istream& operator>>(istream& input, BigInt& val)
{
	int size = 0;
	char* temp = new char[1000];
	input >> temp;
	while (temp[size] != '\0')
	{
		size++;
	}
	val.BigSize = size;
	val.Big = new char[val.BigSize + 1];
	for (int cin = 0; cin < (int)val; cin++)
	{
		val.Big[cin] = temp[cin];
	}
	val.Big[val.BigSize] = '\0';
	delete[]temp;
	return input;
}

BigInt::~BigInt()
{
	Big = NULL;
}

*/

#pragma once
class BigInt
{
public:
	char* Big;

	//think about the private data members
public:
	int BigSize;
	BigInt(int val);
	BigInt(const string& text);
	BigInt(const BigInt& copy); // copy constructor
	// Binary Operators
	// Arithmetic Operators
	BigInt operator+(const BigInt& val) const;
	BigInt operator+(int val) const;
	BigInt operator-(const BigInt& val) const;
	BigInt operator-(int val) const;
	BigInt operator*(const BigInt& val) const;
	// Compound Assignment Operators
	BigInt operator+=(const BigInt& rhs);
	BigInt operator-=(const BigInt& rhs);
	BigInt operator*=(const BigInt& rhs);
	BigInt operator*=(int num);
	// Logical Operators
	bool operator==(const BigInt& val) const;
	bool operator==(const char* val) const;
	bool operator!=(const BigInt& val) const;
	bool operator<(const BigInt& val) const;
	bool operator<=(const BigInt& val) const;
	bool operator>(const BigInt& val) const;
	bool operator>=(const BigInt& val) const;
	// Unary Operators
	BigInt& operator++(); // Pre-increment Operator
	BigInt operator++(int); // Post-increment Operator
	BigInt& operator--(); // Pre-decrement Operator
	BigInt operator--(int); // Post-decrement Operator

	//Conversion Operator
	operator string(); // return value of the BigInt as string
	operator int(); // return the number of digits in big Integer

	friend ostream& operator<<(ostream& output, const BigInt& val); // outputs the BigInt
	friend istream& operator>>(istream& input, BigInt& val); // inputs the BigInt

	~BigInt(); // destructor
};

BigInt::BigInt(int val = 0)
{
	BigSize = 0;
	int temp = val;
	if (val == 0)
	{
		BigSize++;
	}
	while (temp != 0)
	{
		BigSize++;
		temp /= 10;
	}
	Big = new char[BigSize + 1];
	for (int init = 0; init < BigSize; init++)
	{
		Big[init] = '0';
	}
	Big[BigSize] = '\0';
	for (int Zero = BigSize - 1; Zero >= 0; Zero--)
	{
		Big[Zero] = char((val % 10) + 48);
		val /= 10;
	}
}

BigInt::BigInt(const BigInt& copy)
{
	BigSize = copy.BigSize;
	Big = new char[BigSize + 1];
	Big[BigSize] = '\0';
	for (int same = 0; same < BigSize + 1; same++)
	{
		Big[same] = copy.Big[same];
	}
}

BigInt::BigInt(const string& text)
{
	BigSize = 0;
	while (text[BigSize] != '\0')
	{
		BigSize++;
	}
	Big = new char[BigSize + 1];
	Big[BigSize] = '\0';;
	for (int copy = 0; copy < BigSize; copy++)
	{
		Big[copy] = text[copy];
	}
}

BigInt BigInt::operator+(const BigInt& val) const
{
	BigInt Add;
	BigInt Temp;
	if (val.BigSize > BigSize)
	{
		Temp.BigSize = val.BigSize + 1;
	}
	else
	{
		Temp.BigSize = BigSize + 1;
	}
	Temp.Big = new char[Temp.BigSize + 1];
	Temp.Big[Temp.BigSize] = '\0';
	Temp.Big[0] = 0;
	int add1 = BigSize - 1, add2 = val.BigSize - 1;
	int carry = 0;
	for (int i = Temp.BigSize - 1; i >= 0; i--)
	{
		if (i == 0 && (add1 != 0 || add2 != 0))
		{
			carry += 48;
			Temp.Big[0] = char(carry);
			break;
		}
		else if (add1 == 0 && add2 < 0)
		{
			Temp.Big[i] = Big[add1] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 < 0 && add2 == 0)
		{
			Temp.Big[i] = val.Big[add2] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 != 0 && add2 < 0)
		{
			while (add1 >= 0)
			{
				Temp.Big[i] = Big[add1] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add1--;
				i--;
			}
			if (carry != 0 && i == 0)
			{
				Temp.Big[i] = carry + 48;
			}
			break;
		}
		else if (add2 != 0 && add1 < 0)
		{
			while (add2 >= 0)
			{
				Temp.Big[i] = val.Big[add2] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add2--;
				i--;
			}
			if (carry != 0 && i == 0)
			{
				Temp.Big[i] = carry + 48;
			}
			break;
		}
		int a = Big[add1], b = val.Big[add2];
		a -= 48;
		b -= 48;
		a += b;
		a += carry;
		if (a >= 10)
		{
			a -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		a += 48;
		Temp.Big[i] = char(a);
		add1--;
		add2--;
	}
	if (Temp.Big[0] == '0' || Temp.Big[0] == 0)
	{
		Add.BigSize = Temp.BigSize - 1;
	}
	else
	{
		return Temp;
	}
	Add.Big = new char[Add.BigSize + 1];
	Add.Big[Add.BigSize] = '\0';
	int copy = Temp.BigSize - 1;
	for (int i = Add.BigSize - 1; i >= 0; i--)
	{
		Add.Big[i] = Temp.Big[copy];
		copy--;
	}
	return Add;
}

BigInt BigInt::operator+(int val) const
{
	BigInt Add;
	BigInt Temp;
	BigInt rhs(val);
	if (rhs.BigSize > BigSize)
	{
		Temp.BigSize = rhs.BigSize + 1;
	}
	else
	{
		Temp.BigSize = BigSize + 1;
	}
	Temp.Big = new char[Temp.BigSize + 1];
	Temp.Big[Temp.BigSize] = '\0';
	Temp.Big[0] = 0;
	int add1 = BigSize - 1, add2 = rhs.BigSize - 1;
	int carry = 0;
	for (int i = Temp.BigSize - 1; i >= 0; i--)
	{
		if (i == 0 && (add1 != 0 || add2 != 0))
		{
			carry += 48;
			Temp.Big[0] = char(carry);
			break;
		}
		else if (add1 == 0 && add2 < 0)
		{
			Temp.Big[i] = Big[add1] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 < 0 && add2 == 0)
		{
			Temp.Big[i] = rhs.Big[add2] + carry;
			if (Temp.Big[i] >= 58)
			{
				Temp.Big[i] -= 10;
				Temp.Big[i - 1] = char(49);
			}
			break;
		}
		else if (add1 != 0 && add2 < 0)
		{
			while (add1 >= 0)
			{
				Temp.Big[i] = Big[add1] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add1--;
				i--;
			}
			break;
		}
		else if (add2 != 0 && add1 < 0)
		{
			while (add2 >= 0)
			{
				Temp.Big[i] = rhs.Big[add2] + carry;
				if (Temp.Big[i] >= 58)
				{
					Temp.Big[i] -= 10;
					carry = 1;
				}
				else
				{
					carry = 0;
				}
				add2--;
				i--;
			}
			break;
		}
		int a = Big[add1], b = rhs.Big[add2];
		a -= 48;
		b -= 48;
		a += b;
		a += carry;
		if (a >= 10)
		{
			a -= 10;
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		a += 48;
		Temp.Big[i] = char(a);
		add1--;
		add2--;
	}
	if (Temp.Big[0] == '0' || Temp.Big[0] == 0)
	{
		Add.BigSize = Temp.BigSize - 1;
	}
	else
	{
		return Temp;
	}
	Add.Big = new char[Add.BigSize + 1];
	Add.Big[Add.BigSize] = '\0';
	int copy = Temp.BigSize - 1;
	for (int i = Add.BigSize - 1; i >= 0; i--)
	{
		Add.Big[i] = Temp.Big[copy];
		copy--;
	}
	return Add;
}

BigInt BigInt::operator-(const BigInt& val) const
{
	BigInt Sub;
	int carry = 0;
	if (BigSize > val.BigSize)
	{
		Sub.BigSize = BigSize;
	}
	else
	{
		Sub.BigSize = val.BigSize;
	}
	Sub.Big = new char[Sub.BigSize + 1];
	Sub.Big[Sub.BigSize] = '\0';
	int size1 = val.BigSize - 1;
	int size2 = BigSize - 1;
	int newsize = Sub.BigSize - 1;
	if (size1 > size2 || ((size1 == size2) && (val.Big[0] > Big[0])))
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (val.Big[size1] >= Big[size2] + carry)
				{
					Sub.Big[newsize] = val.Big[size1] - Big[size2] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - Big[size2] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (val.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = val.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
		BigInt Temp;
		Temp.BigSize = Sub.BigSize + 2;
		Temp.Big = new char[Sub.BigSize + 2];
		Temp.Big[Sub.BigSize + 1] = '\0';
		for (int copy = 1; copy < Sub.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Sub.Big[copy - 1];
		}
		Temp.Big[Sub.BigSize + 1] = Sub.Big[Sub.BigSize];
		Temp.Big[0] = '-';
		delete[] Sub.Big;
		Sub = Temp;
	}
	else
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (Big[size2] >= val.Big[size1] + carry)
				{
					int n = Big[size2] - val.Big[size1] - carry + 48;
					Sub.Big[newsize] = n;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - val.Big[size1] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (val.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = val.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = val.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
	}
	return Sub;
}

BigInt BigInt::operator-(int val) const
{
	BigInt Sub;
	BigInt rhs(val);
	int carry = 0;
	if (BigSize > rhs.BigSize)
	{
		Sub.BigSize = BigSize;
	}
	else
	{
		Sub.BigSize = rhs.BigSize;
	}
	(string)Sub = new char[Sub.BigSize + 1];
	Sub.Big[Sub.BigSize] = '\0';
	int size1 = rhs.BigSize - 1;
	int size2 = BigSize - 1;
	int newsize = Sub.BigSize - 1;
	if (size1 > size2 || ((size1 == size2) && (rhs.Big[0] > Big[0])))
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (rhs.Big[size1] >= Big[size2] + carry)
				{
					Sub.Big[newsize] = rhs.Big[size1] - Big[size2] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - Big[size2] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (rhs.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
		BigInt Temp;
		Temp.BigSize = Sub.BigSize + 2;
		Temp.Big = new char[Sub.BigSize + 2];
		Temp.Big[Sub.BigSize + 1] = '\0';
		for (int copy = 1; copy < Sub.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Sub.Big[copy - 1];
		}
		Temp.Big[Sub.BigSize + 1] = Sub.Big[Sub.BigSize];
		Temp.Big[0] = '-';
		delete[] Sub.Big;
		Sub = Temp;
	}
	else
	{
		while (newsize >= 0)
		{
			if (size1 >= 0 && size2 >= 0)
			{
				if (Big[size2] >= rhs.Big[size1] + carry)
				{
					Sub.Big[newsize] = Big[size2] - rhs.Big[size1] - carry + 48;
					carry = 0;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - rhs.Big[size1] - carry + 10 + 48;
					carry = 1;
				}
			}
			else if (size1 >= 0)
			{
				if (rhs.Big[size1] == '0' && carry == 1)
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = rhs.Big[size1] - carry;
					carry = 0;
				}
			}
			else if (size2 >= 0)
			{
				if (Big[size2] == '0' && carry == 1)
				{
					Sub.Big[newsize] = Big[size2] - carry + 10;
					carry = 1;
				}
				else
				{
					Sub.Big[newsize] = Big[size2] - carry;
					carry = 0;
				}
			}
			newsize--;
			size1--;
			size2--;
		}
		while (Sub.Big[0] == '0' && Sub.Big[1] != '\0')
		{
			BigInt Temp;
			Temp.BigSize = Sub.BigSize - 1;
			Temp.Big = new char[Sub.BigSize];
			Temp.Big[Sub.BigSize - 1] = '\0';
			for (int copy = 1; copy < Sub.BigSize; copy++)
			{
				Temp.Big[copy - 1] = Sub.Big[copy];
			}
			Temp.Big[Sub.BigSize - 1] = Sub.Big[Sub.BigSize];
			delete[] Sub.Big;
			Sub = Temp;
		}
	}
	return Sub;
}

BigInt BigInt::operator*(const BigInt& val) const
{
	BigInt Mult;
	BigInt rhs = val;
	int neg1 = 0, neg2 = 0;
	if (Big[0] == '-' && rhs.Big[0] != '-')
	{
		neg1 = 1;
	}
	if (Big[0] != '-' && rhs.Big[0] == '-')
	{
		neg2 = 1;
	}
	if (Big[0] == '-' && rhs.Big[0] == '-')
	{
		neg1 = 1;
		neg2 = 1;
	}
	Mult.BigSize = BigSize + rhs.BigSize - 1;
	Mult.Big = new char[Mult.BigSize + 1];
	for (int init = 0; init < Mult.BigSize; init++)
	{
		Mult.Big[init] = 0;
	}
	Mult.Big[Mult.BigSize] = '\0';
	int overflow = 0;
	int size1 = BigSize;
	int size2 = rhs.BigSize;
	int carry = 0;
	for (int prod = size1 - 1; prod >= neg1; prod--)
	{
		for (int uct = size2 - 1; uct >= neg2; uct--)
		{
			if (Mult.Big[uct + prod] >= 48 && Mult.Big[uct + prod] <= 57)
			{
				Mult.Big[uct + prod] -= 48;
			}
			if (((rhs.Big[uct] - 48) * (Big[prod] - 48)) + carry + 48 > 127)
			{
				int temp = (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48 - 57;
				int temp2 = temp;
				carry = 0;
				while (temp > 0)
				{
					carry++;
					temp -= 10;
				}
				Mult.Big[uct + prod] += temp2 - (carry * 10) + 57;
			}
			else if (((rhs.Big[uct] - 48) * (Big[prod] - 48)) + carry + 48 + (int)Mult.Big[uct + prod] > 127)
			{
				int temp = (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48 - 57 + (int)Mult.Big[uct + prod];
				int temp2 = temp;
				carry = 0;
				while (temp > 0)
				{
					carry++;
					temp -= 10;
				}
				Mult.Big[uct + prod] = temp2 - (carry * 10) + 57;
			}
			else
			{
				Mult.Big[uct + prod] += (rhs.Big[uct] - 48) * (Big[prod] - 48) + carry + 48;
				carry = 0;
				if (Mult.Big[uct + prod] > 57)
				{
					int temp = Mult.Big[uct + prod] - 57;
					while (temp > 0)
					{
						carry++;
						temp -= 10;
					}
					Mult.Big[uct + prod] -= (carry * 10);
				}
			}
		}
		if (carry != 0 && prod > neg1)
		{
			Mult.Big[neg2 + prod - 1] += carry;
			carry = 0;
		}
	}
	if (carry != 0)
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize + 2;
		Temp.Big = new char[Mult.BigSize + 2];
		Temp.Big[Mult.BigSize + 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize + 1; copy++)
		{
			Temp.Big[copy] = Mult.Big[copy - 1];
		}
		Temp.Big[Mult.BigSize + 1] = Mult.Big[Mult.BigSize];
		Temp.Big[neg1 + neg2] = carry + 48;
		delete[] Mult.Big;
		Mult = Temp;
	}
	if ((neg1 == 1 && neg2 == 0) || (neg1 == 0 && neg2 == 1))
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
		Mult.Big[0] = '-';
	}
	else if (neg1 == 1 && neg2 == 1)
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
	}
	while (Mult.Big[0] == '0' && Mult.Big[1] != '\0')
	{
		BigInt Temp;
		Temp.BigSize = Mult.BigSize - 1;
		Temp.Big = new char[Mult.BigSize];
		Temp.Big[Mult.BigSize - 1] = '\0';
		for (int copy = 1; copy < Mult.BigSize; copy++)
		{
			Temp.Big[copy - 1] = Mult.Big[copy];
		}
		Temp.Big[Mult.BigSize - 1] = Mult.Big[Mult.BigSize];
		delete[] Mult.Big;
		Mult = Temp;
	}
	return Mult;
}

BigInt BigInt::operator+=(const BigInt& rhs)
{
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator-=(const BigInt& rhs)
{
	*this = *this - rhs;
	return *this;
}

BigInt BigInt::operator*=(const BigInt& rhs)
{
	*this = *this * rhs;
	return *this;
}

BigInt BigInt::operator*=(int num)
{
	BigInt Mult;
	int remainder = 0;
	if (Big[0] >= '5')
	{
		Mult.BigSize = BigSize + 1;
	}
	else
	{
		Mult.BigSize = BigSize;
	}
	Mult.Big = new char[Mult.BigSize + 1];
	Mult.Big[Mult.BigSize] = '\0';
	int copy2 = BigSize - 1;
	for (int copy = Mult.BigSize - 1; copy >= 0; copy--)
	{
		int digit = Big[copy2];
		digit -= 48;
		digit *= 2;
		digit += remainder;
		if (digit >= 10)
		{
			remainder = 1;
			digit -= 10;
		}
		else
		{
			remainder = 0;
		}
		digit += 48;
		Mult.Big[copy] = char(digit);
		copy2--;
		if (copy2 == -1 && copy != 0)
		{
			Mult.Big[0] = char(remainder + 48);
			break;
		}
	}
	*this = Mult;
	return *this;
}

bool BigInt::operator==(const BigInt& val) const
{
	int counter = 0;
	if (BigSize == val.BigSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val.Big[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return true;
		}
	}
	return false;
}

bool BigInt::operator==(const char* val) const
{
	int counter = 0, valSize = 0;
	while (val[valSize] != '\0')
	{
		valSize++;
	}
	if (BigSize == valSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return true;
		}
	}
	return false;
}

bool BigInt::operator!=(const BigInt& val) const
{
	int counter = 0;
	if (BigSize == val.BigSize)
	{
		for (int compare = 0; compare < BigSize; compare++)
		{
			if (Big[compare] == val.Big[compare])
			{
				counter++;
			}
		}
		if (counter == BigSize)
		{
			return false;
		}
	}
	return true;
}

bool BigInt::operator<(const BigInt& val) const
{
	int compare = 0;
	if (Big == val.Big)
	{
		return false;
	}
	if (BigSize == val.BigSize)
	{
		while (Big[compare] <= val.Big[compare])
		{
			if (Big[compare] < val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return false;
			}
		}
		return false;
	}
	else if (BigSize > val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator<=(const BigInt& val) const
{
	int compare = 0;
	if (BigSize == val.BigSize)
	{
		while (Big[compare] <= val.Big[compare])
		{
			if (Big[compare] < val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return true;
			}
		}
		if (compare == BigSize)
		{
			return true;
		}
		return false;
	}
	else if (BigSize > val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator>(const BigInt& val) const
{
	int compare = 0;
	if (Big == val.Big)
	{
		return false;
	}
	if (BigSize == val.BigSize)
	{
		while (Big[compare] >= val.Big[compare])
		{
			if (Big[compare] > val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return false;
			}
		}
		return false;
	}
	else if (BigSize < val.BigSize)
	{
		return false;
	}
	return true;
}

bool BigInt::operator>=(const BigInt& val) const
{
	int compare = 0;
	if (BigSize == val.BigSize)
	{
		while (Big[compare] >= val.Big[compare])
		{
			if (Big[compare] > val.Big[compare])
			{
				return true;
			}
			compare++;
			if (compare == BigSize + 1)
			{
				return true;
			}
		}
		if (compare == BigSize)
		{
			return true;
		}
		return false;
	}
	else if (BigSize < val.BigSize)
	{
		return false;
	}
	return true;
}

BigInt& BigInt::operator++()
{
	*this = *this + 1;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt temp(*this);
	*this = *this + 1;
	return temp;
}

BigInt& BigInt::operator--()
{
	*this = *this - 1;
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt temp(*this);
	*this = *this - 1;
	return temp;
}

BigInt::operator string()
{
	return Big;
}

BigInt::operator int()
{
	return BigSize;
}

ostream& operator<<(ostream& output, const BigInt& val)
{
	for (int cout = 0; cout < val.BigSize; cout++)
	{
		output << val.Big[cout];
	}
	return output;
}

istream& operator>>(istream& input, BigInt& val)
{
	int size = 0;
	char* temp = new char[1000];
	input >> temp;
	while (temp[size] != '\0')
	{
		size++;
	}
	val.BigSize = size;
	val.Big = new char[val.BigSize + 1];
	for (int cin = 0; cin < (int)val; cin++)
	{
		val.Big[cin] = temp[cin];
	}
	val.Big[val.BigSize] = '\0';
	delete[]temp;
	return input;
}

BigInt::~BigInt()
{
	Big = NULL;
}


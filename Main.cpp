// Alex Heaton
// CECS 282-05
// Prog 5 ? BigInt
// Due: April 26, 2021
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class BigInt {
private:
	int n;
	vector<char> num;

public:
	BigInt();
	BigInt(string);
	BigInt(int);
	BigInt(const BigInt& x);

	void print();
	bool operator<(const BigInt&) const noexcept;
	bool operator<=(int);
	bool operator==(BigInt);
	BigInt operator+(BigInt);
	BigInt operator-(int);
	BigInt operator++(int);
	friend ostream& operator<<(ostream& os, const BigInt& dt);

};



int goldRabbits(int);
BigInt goldRabbits(BigInt);
void pause(){cout << "Press Enter to continue..."; getchar();}

int main()
{
	{

		cout << goldRabbits(BigInt(3000)) << endl;   // <----- add this line

		// the rest of the program will remain the same

	}
	BigInt B1("123456789123456789123456789123456789");
	BigInt B2(B1);
	BigInt MAX(INT_MAX);
	cout << "B1:" << B1 << "\nB2:" << B2 << "\nMAX:" << MAX << endl;
	pause();
	cout << "\nB1:";
	B1.print();
	cout << endl;
	pause();
	
	for(BigInt i=0; i <= 3000; i++)// uncomment this
	//for(int i=0; i<=3000; i++)// comment this out
	{
		cout << "\ngoldRabbits("<< i <<") = " << goldRabbits(i);
	}
		pause();
		
	cout<< "\nThis is the value of goldRabbits(3000)\n\n";
	BigInt gR3000 =  goldRabbits(BigInt(3000));
	gR3000.print();
	
	pause();

	int n = 500;
		try{
			cout << "The value of goldRabbits(n) is:" << goldRabbits(n) << endl;
		}
		catch(string error){
			cout << error << endl;
			cout << "Transitioning to BigInt\n";
			cout << goldRabbits(BigInt(n));
		}
		
		pause();
}
// Modify this function so that it accepts BigInt as input parameter and returns a BigInt
// and uses a map for speed

int goldRabbits(int n) {
	if (n == 0 || n == 1)// base case
		return 1;

	int x = goldRabbits(n - 1) + goldRabbits(n - 2);
	if (x < 0)
		throw ("Overflow error - goldRabbits overflowed using" + n);
	return x; // general case}
}



BigInt goldRabbits(BigInt n)
{
	static map<BigInt, BigInt> rabbitMap;
	if (n == 0 || n == 1) // base case
	{
		BigInt temp(1);
		return temp;
	}

	else if (rabbitMap.find(n) != rabbitMap.end())
	{
		return rabbitMap[n];
	}
	else
	{
		BigInt val1 = goldRabbits(n - 2);
		BigInt val2 = goldRabbits(n - 1);
		BigInt val = val2 + val1;
		rabbitMap.insert({ n, val });
		return val;
	}
}

//Implementation Below
BigInt::BigInt()
{
	num.push_back(0);
	n = 1;
}

BigInt::BigInt(string str)
{
	n = 0;
	for (int i = 0; i < str.length(); i++)
	{
		num.push_back(str[i]);
		n++;
	}
}

BigInt::BigInt(int x)
{
	string str = to_string(x);
	n = 0;
	for (int i = 0; i < str.length(); i++)
	{
		num.push_back(str[i]);
		n++;
	}
}

BigInt::BigInt(const BigInt& x)
{
	n = x.n;
	num = x.num;
}

void BigInt::print()
{
	string result = "";
	for (int i = 0; i < num.size(); i++)
	{
		result += num[i];
	}
	cout << result << endl;
}

bool BigInt::operator<(const BigInt& rhs) const noexcept
{
	if (n < rhs.n)
		return true;
	else if (n > rhs.n)
		return false;

	for (int i = 0; i < n; i++)
	{
		if (num[i] < rhs.num[i]) { return true; }
		else if (num[i] > rhs.num[i]) { return false; }
	}
	return false;
}

bool BigInt::operator<=(int x)
{
	BigInt temp(x);
	if (n < temp.n) { return true; }
	else if (n > temp.n) { return false; }

	for (int i = 0; i < n; i++)
	{
		if (num[i] < temp.num[i]) { return true; }
		else if (num[i] > temp.num[i]) { return false; }
	}
	return true;
}

bool BigInt::operator==(BigInt o)
{
	if (n != o.n) { return false; }
	for (int i = 0; i < n; i++)
	{
		if (num[i] != o.num[i]) { return false; }
	}
	return true;
}

BigInt BigInt::operator+(BigInt o)
{
	int i = n - 1;
	int j = o.n - 1;

	BigInt result(0);
	int temp = 0;
	bool carry = false;

	while (i >= 0 || j >= 0)
	{
		temp = 0;
		if (i >= 0)
			temp += num[i] - 48;
		if (j >= 0)
			temp += o.num[j] - 48;
		temp += carry;
		if (temp < 10)
		{
			result.num.insert(result.num.begin(), temp + 48);
			carry = false;
		}

		if (temp >= 10)
		{
			result.num.insert(result.num.begin(), temp + 38);
			carry = true;
		}
		result.n++;
		i--;
		j--;
	}
	if (carry)
	{
		result.num.insert(result.num.begin(), '1');
		result.n++;
	}

	result.num.pop_back();
	result.n--;
	return result;
}

BigInt BigInt::operator-(int x)
{
	BigInt o(x);
	BigInt t(*this);
	int i = t.n - 1;
	int j = o.n - 1;
	while (j >= 0)
	{
		char temp = t.num[i] - o.num[j] + 48;
		if (temp < '0')
		{
			t.num[i] = temp + 10;
			int k = i - 1;
			t.num[k]--;
			while (t.num[k] < '0') {
				t.num[k] = '9';
				k--;
				t.num[k]--;
			}
		}
		else
		{
			t.num[i] = temp;
		}
		i--;
		j--;
	}
	while (true)
	{
		if (t.num[0] != '0') { break; }
		if (t.num[0] == '0' && t.n == 1) { break; }
		t.num.erase(t.num.begin());
		t.n--;
	}
	return t;
}

BigInt BigInt::operator++(int)
{
	int i = n - 1;
	while (true)
	{
		if (num[i] < '9')
		{
			num[i]++;
			break;
		}

		num[i] = '0';
		if (i == 0)
		{
			num.insert(num.begin(), '1');
			n++;
			break;
		}
		i--;
	}
	return *this;
}

inline ostream& operator<<(ostream& os, const BigInt& obj)
{
	if (obj.n > 12)
	{
		os << obj.num[0] << '.';
		for (int i = 1; i < 11; i++) { os << obj.num[i]; }
		os << 'e' << obj.n;
	}

	else {
		for (int i = 0; i < obj.n; i++) { os << obj.num[i]; }
	}
	return os;
}
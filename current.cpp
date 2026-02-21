#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include "current.h"

using namespace std;

Base::Base() {}
Base::~Base() {}

Base* Base::create_object()
{
    return new AnyBaseInt();
}
std::string AnyBaseInt::ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
AnyBaseInt::AnyBaseInt() : value("0"), base(10), currentAlphabet("0"), Negative(false), value10(0){}
AnyBaseInt::~AnyBaseInt() {}


void AnyBaseInt::setBase(const int newBase) //помимо записи основания, записывается и алфавит на основания количества символов
{
	base = newBase;
	currentAlphabet = ALPHABET.substr(0, base);
}

int AnyBaseInt::Input_base()
{
    cout << "\nenter base of system: ";
    while (!(cin >> base) || base < 2 || base > 36)
        cout << "\nwrong input, try again\n";
    return base;
}

int AnyBaseInt::Check_Input_Value(string buf, string alphabet)
{
    for (char c : buf)
        if (alphabet.find(c) == string::npos)
            return 0;
    return 1;
}

void AnyBaseInt::Input_value(string &value, string alphabet)
{
    string buf;
    do
    {
        cout << "enter value\n";
        cin >> buf;
    } while (!Check_Input_Value(buf, alphabet));

    value = buf;
}

string AnyBaseInt::Convert_to_Decimal(string &buf, int base, string alphabet, bool Negative)
{
    int result = 0;
    
    cout << "negative value - " << Negative;
    
    if (base == 10) return buf;
    
    if (Negative) buf.erase(0,1);
    
    for (char c : buf)
        result = result * base + alphabet.find(c);

    buf = to_string(Negative ? -result : result);
    return buf;
}

bool AnyBaseInt::Input_Negative()
{
	int buf;
	
	cout << "\nIs value negative? 1. yes 0. no\n";
	while (1)
	{
		cin >> buf;
		if (buf == 0 || buf == 1) break;
	}
	
	Negative = buf;
}

void AnyBaseInt::AddObjectValue()
{
    setBase(Input_base());
    
    Input_Negative();
    Input_value(value, currentAlphabet);
    
    string buf = value;
    
    value10 = stoi(Convert_to_Decimal(buf, base, currentAlphabet, Negative));
}

string AnyBaseInt::Add_One(string &converted, int base, string alphabet)
{
    int carry = 1;

    for (int i = converted.size() - 1; i >= 0 && carry; i--)
    {
        int d = alphabet.find(converted[i]) + carry;
        carry = d / base;
        converted[i] = alphabet[d % base];
    }

    if (carry)
        converted = alphabet[carry] + converted;

    return converted;
}

string AnyBaseInt::Convert_to_Base(int buf, int base, string alphabet)
{
    int number = buf;
	string res = "";

    if (number == 0)
        return string(1, alphabet[0]);

    while (number > 0)
    {
        res = alphabet[number % base] + res;
        number /= base;
    }
    
    return res;
}

string AnyBaseInt::ConvertToString(int number, int base, bool negative, string currentAlphabet)
{
    int value = negative ? -number : number;   // берём модуль если отрицательное
    string converted = Convert_to_Base(value, base, currentAlphabet);

    if (!negative)
    {
        return converted;
    }
    else
    {
    	if (base == 10)
        {
            return "-" + converted;
        }
        
        char signDigit = currentAlphabet[base - 1];

        return string(1, signDigit) + converted;
    }
}

int AnyBaseInt::ConvertToInt(string s, int base, bool negative, string alphabet)
{
    if (negative)
    {
        int borrow = 1;
        for (int i = s.size() - 1; i >= 0 && borrow; i--)
        {
            int d = alphabet.find(s[i]) - borrow;
            if (d < 0) d += base;
            else borrow = 0;
            s[i] = alphabet[d];
        }

        for (char &c : s)
            c = alphabet[base - 1 - alphabet.find(c)];
    }

    int res = 0;
    for (char c : s)
        res = res * base + alphabet.find(c);

    return negative ? -res : res;
}

void AnyBaseInt::Print()
{
    cout << "value - " << value
         << "\n\t\t\t\t\t\t\t\tbase - " << base
         << "\n\t\t\t\t\t\t\t\talphabet - " << currentAlphabet 
		 << "\n\t\t\t\t\t\t\t\tnegative - " << Negative
		 << "\n\t\t\t\t\t\t\t\tvalue 10 - " << value10 << "\n";
}

bool AnyBaseInt::operator<(AnyBaseInt &b) const
{
	return this->value10 < b.value10;
}

bool AnyBaseInt::operator>(AnyBaseInt &b) const
{
	return this->value10 > b.value10;
}

bool AnyBaseInt::operator == (AnyBaseInt &b) const
{
	return this->value10 == b.value10;
}

string AnyBaseInt::GetValue() const 
{ 
	return value; 
}

void AnyBaseInt::SetValue(const string& v) 
{ 
	value = v; 
}

void AnyBaseInt::Convertation()
{
    int base_changed;
    cout << "\nbase of a system converting to: ";
    cin >> base_changed;

    string alphabet_changed = ALPHABET.substr(0, base_changed);

    string original_value = value;
    cout << "\nORIGINAL VALUE IS " << original_value;
	
    string buf = ConvertToString(value10, base_changed, Negative, alphabet_changed);
    
    cout << "\nRESULT is ";
    if (base == 10) cout << value10;
    	else cout << buf;

    value = buf;              
    base = base_changed;
    currentAlphabet = alphabet_changed;
}


int AnyBaseInt::Compare_objects(AnyBaseInt p1, AnyBaseInt p2)
{
	if (p1 > p2) return 1;
		else if (p1 < p2) return 2;
			else return 3;	
}


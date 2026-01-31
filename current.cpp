#include <iostream>
#include <string>
#include <cmath>
#include "current.h"

using namespace std;

Base::Base() {}
Base::~Base() {}

Base* Base::create_object()
{
    return new AnyBaseInt();
}

AnyBaseInt::AnyBaseInt() : value("0"), base(10), alphabet("0"), Negative(false) {}
AnyBaseInt::~AnyBaseInt() {}

int AnyBaseInt::Input_base(int &base)
{
    cout << "\nenter base of system: ";
    while (true)
    {
        cin >> base;
        if (!cin || base < 2 || base > 36)
        {
            cout << "wrong input, try again\n";
            cin.clear();
            continue;
        }
        break;
    }
    return base;
}

void AnyBaseInt::Convert_to_Uppercase(string &alphabet)
{
    for (char &c : alphabet)
        c = toupper(c);
}

int AnyBaseInt::Check_symbols(char c)
{
    string allowed = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    return allowed.find(c) != string::npos;
}

void AnyBaseInt::Input_alphabet(int base, string &alphabet)
{
    alphabet.clear();
    char c;

    cout << "Enter alphabet (" << base << " symbols):\n";
    for (int i = 0; i < base; i++)
    {
        do
        {
            cin >> c;
            if (!Check_symbols(c))
                cout << "wrong input, try again\n";
        } while (!Check_symbols(c));

        alphabet.push_back(c);
    }
}

int AnyBaseInt::Unique_alphabet(string alphabet, int base)
{
	Convert_to_Uppercase(alphabet);

    for (int i = 0; i < base; i++)
        for (int j = i + 1; j < base; j++)
            if (alphabet[i] == alphabet[j])
                return 0;

    return 1;
}

void AnyBaseInt::Fill_Alphabet(string &alphabet, int base)
{
    do
    {
        Input_alphabet(base, alphabet);
    } while (!Unique_alphabet(alphabet, base));
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
        if (!Check_Input_Value(buf, alphabet))
        {
            cout << "wrong input, try again (value)\n";
            cin.clear();
        }
    } while (!Check_Input_Value(buf, alphabet));

    value = buf;
}

bool AnyBaseInt::Input_negative(bool &Negative)
{
    int buf;
    do
    {
        cout << "is value negative?\n1. yes\n2. no\n";
        cin >> buf;
        if (!cin || (buf != 1 && buf != 2))
        {
            cout << "wrong input, try again\n";
            cin.clear();
            buf = 0;
        }
    } while (buf != 1 && buf != 2);

    Negative = (buf == 1);
    return Negative;
}


void AnyBaseInt::AddObjectValue()
{
    Input_base(base);
    Fill_Alphabet(alphabet, base);
    Input_value(value, alphabet);
    Input_negative(Negative);
}

string AnyBaseInt::Convert_to_Decimal(string &buf, int base, string alphabet, bool Negative) //�������������� � ���������� �����, ���� ��� ����������, �� ������ ������������ ����������� ������ 
{
	if (Negative)
	{
		if (base == 10) return buf;
		else
		{
			
		}
	}
	else
	{
		if (base == 10) return buf;
		else
		{
			int i, j, temp_value = 0;
			j = buf.size()-1;
		
			for (i = 0; i < buf.size(); i++)
			{
				temp_value += alphabet.find(buf[i]) * pow(base, j);
				j--;
			}
		
			buf = to_string(temp_value);
		
			return buf;
		}		
	}	
}

string AnyBaseInt::Convert_to_Base(string &buf, int base, string alphabet) 
{
	int i, cur_remain, cur_number;
	
	cur_number = stoi(buf);
	buf = "";
	
	while (cur_number/base >= base)
	{
		cur_remain = cur_number % base;
		
		buf = alphabet[cur_remain-1] + buf;
		
		cur_number = cur_number / base;
	}
	
	cout << "number after convertation - \n" << buf;
	return buf;
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

string AnyBaseInt::ConvertToString(int number, int base, bool negative, string alphabet)
{
    string converted = to_string(abs(number));
    converted = AnyBaseInt().Convert_to_Base(converted, base, alphabet);

    if (!negative)
        return converted;

    while (converted.size() % 4 != 0)
        converted = alphabet[0] + converted;

    for (char &c : converted)
        c = alphabet[base - 1 - alphabet.find(c)];

    Add_One(converted, base, alphabet);
    return converted;
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

Base* AnyBaseInt::Convertation()
{
    string buf, alphabet_changed;
    int base_changed;

    Base *p = Base::create_object();
    p->AddObjectValue(); 

    cout << "base of a system converting to: ";
    Input_base(base_changed);
    cout << "alphabet of new system:\n";
    Fill_Alphabet(alphabet_changed, base_changed);

    buf = Convert_to_Decimal(this->value, this->base, this->alphabet, this->Negative);

    buf = Convert_to_Base(buf, base_changed, alphabet_changed);
    
    cout << "Converted value: " << buf << "\n";

    AnyBaseInt* new_obj = dynamic_cast<AnyBaseInt*>(p);
    if (new_obj)
    {
        new_obj->value = buf;
        new_obj->base = base_changed;
        new_obj->alphabet = alphabet_changed;
        new_obj->Negative = false; 
    }

    return p;
}


int AnyBaseInt::Compare_objects(AnyBaseInt p1, AnyBaseInt p2)
{
	int num1, num2;
	
	if (p1.Negative)
	{
		num1 = ConvertToInt(p1.value, p1.base, p1.Negative, p1.alphabet);
	}
	else 
	{
		num1 = stoi(Convert_to_Decimal(p1.value, p1.base, p1.alphabet, p1.Negative));
	}
	
	if (p2.Negative)
	{
		num2 = ConvertToInt(p2.value, p2.base, p2.Negative, p2.alphabet);
	}
	else
	{
		num2 = stoi(Convert_to_Decimal(p2.value, p2.base, p2.alphabet, p2.Negative));
	}
	
	if (num1 > num2) return 1;
		else if (num1 < num2) return 2;
			else return 3;
}

void AnyBaseInt::Print()
{
    cout << "value - " << value
         << "\nbase - " << base
         << "\nalphabet - " << alphabet << "\n";
}

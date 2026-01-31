#ifndef SUBJ_H
#define SUBJ_H

#include <string>
#include "list.h"
using namespace std;

class Base : public Item
{
public:
    Base();
    virtual ~Base();

    static Base* create_object();

    virtual void AddObjectValue() = 0;
    virtual void Print() = 0;
};

class AnyBaseInt : public Base
{
private:
	string value;
    int base;
    string alphabet;
    bool Negative;
    
public:
    AnyBaseInt();
    ~AnyBaseInt();

    int Input_base(int &base);
    int CaseSensetivity();
    void Convert_to_Uppercase(string &alphabet);
    int Check_symbols(char c);
    void Input_alphabet(int base, string &alphabet);
    int Unique_alphabet(string alphabet, int base);
    void Fill_Alphabet(string &alphabet, int base);
    int Check_Input_Value(string buf, string alphabet);
    void Input_value(string &value, string alphabet);
    bool Input_negative(bool &Negative);
    void AddObjectValue();

    string Convert_to_Decimal(string &buf, int base, string alphabet, bool Negative = false);
    string Convert_to_Base(string &buf, int base, string alphabet);

    void Print();
    
    string ConvertToString(int number, int base, bool negative, string alphabet);
	int ConvertToInt(string s, int base, bool negative, string alphabet);
	string Add_One(string &converted, int base, string alphabet);
	
	Base* Convertation();
	int Compare_objects(AnyBaseInt p1, AnyBaseInt p2);
};

#endif

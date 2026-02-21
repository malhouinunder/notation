#ifndef SUBJ_H
#define SUBJ_H

#include <string>
#include "list.h"
using namespace std;

class Base : public Item
{
	
friend class AnyBaseInt;

public:
    Base();
    virtual ~Base();

    static Base* create_object();

    virtual void AddObjectValue() = 0;
    virtual void Print() = 0;
};

class AnyBaseInt : public Base
{
friend class Base;

private:
	string value;
    int base;
    string currentAlphabet;
    bool Negative;
    int value10; //здесь хранятся числа в 10сс
    static std::string ALPHABET;
    
public:
    AnyBaseInt();
    ~AnyBaseInt();
    
    void setBase(const int base); //сеттер Base, внутри установка алфавита

	int Input_base();

    int Check_Input_Value(string buf, string alphabet);
    void Input_value(string &value, string alphabet);
    bool Input_negative(bool &Negative);
    void AddObjectValue();

    string Convert_to_Decimal(string &buf, int base, string alphabet, bool Negative = false);
	string Convert_to_Base(int buf, int base, string alphabet);

    void Print();
    
    string ConvertToString(int number, int base, bool negative, string alphabet);
	int ConvertToInt(string s, int base, bool negative, string alphabet);
	string Add_One(string &converted, int base, string alphabet);
	
	void Convertation();
	int Compare_objects(AnyBaseInt p1, AnyBaseInt p2);
	
    bool operator<(AnyBaseInt &b) const;
	bool operator>(AnyBaseInt &b) const;
	bool operator == (AnyBaseInt &b) const;
	
	bool Input_Negative();
	
	string GetValue() const;
	void SetValue(const std::string& v);
	
};

#endif

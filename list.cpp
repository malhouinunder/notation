#include <iostream>
#include <stdexcept>
#include "list.h"
using namespace std;

Item::Item() //�����������
	: next(NULL), prev(NULL)
{
}

Item::~Item() //����������
{
	if (owner){
		int pos = owner->GetIndex(this);
		if (pos!=-1){
			owner->Remove(pos);
		}
	}
}

List::List()
	: head(NULL), tail(NULL)
{
}

List::~List()
{
	Clear();
}


void List::Add(Item *item){
	cout << "adding elem\n";
	if (!item) return;
			
	item->next = NULL;
	item->prev = tail;
			
	if (tail)
		tail->next = item; 
	else 
		head = item;
	
	tail = item;
	
			
}

Item* List::GetItem(int pos)
{
    if (pos < 0 || pos >= CountElem()){
    	cout << "no such elem\n";
    	return NULL;
	} 

    Item *tmp = head;
    int i = 0;

    while (tmp && i < pos) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}

Base& List::operator[](int i)
{
    if (i < 0 || i > CountElem())
    {
		throw std::out_of_range("Index out of range");  	
	}
    
    Item* item = GetItem(i);
    if (!item)
        throw std::out_of_range("Item is nullptr at this index");
        
    return *(Base*)item;
}


int List::GetIndex(Item *elem)
{
	int n=0;
	Item *tmp = head;
			
	while (tmp){
		if (tmp==elem) return n;
		n++;
		tmp=tmp->next;
	}
			
	return -1;
}


void List::Insert(int pos, Item* insert)
{
    if (!insert) return;

    Item* elem = GetItem(pos);

    if (!elem) {
        Add(insert);
        return;
    }

    insert->prev = elem->prev;
    insert->next = elem;

    if (elem->prev)
        elem->prev->next = insert;
    else
        head = insert;

    elem->prev = insert;
}

Item* List::Remove(int pos)
{
    Item *removal = GetItem(pos);
    if (!removal){
    	cout << "no such elem\n";
    	return NULL;
	} 

    if (removal->prev)
        removal->prev->next = removal->next;
    else
        head = removal->next;

    if (removal->next)
        removal->next->prev = removal->prev;
    else
        tail = removal->prev;

    return removal;
}

void List::Delete(int pos)
{
	if (head == NULL && tail == NULL)	return;
	
    Item *item = Remove(pos);
    delete item;
    
    cout << "elem deleted\n";
}

int List::CountElem()
{
    int n = 0;
    Item* tmp = head;
    
    while (tmp) {
        n++;
        tmp = tmp->next;
    }
    
    return n;
}

void List::Clear()
{
    Item* tmp = head;
    
    while (tmp) {
        Item* next = tmp->next;
        delete tmp;
        tmp = next;
    }

    head = NULL;
    tail = NULL;
}


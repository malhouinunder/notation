#ifndef LIST_H
#define LIST_H
#include <iostream>

class List;
class Base;

class Item {
	friend class List;
	friend class SubjList;
	friend class DebugList;
	
private:
	Item *next;
	Item *prev;
			
	List *owner;
			
public:
	Item();
	virtual ~Item();
		
	Item* Next(){return next;}
	Item* Prev(){return prev;}	
};

class List {
	friend class Item;
	friend class DebugList;
	
	private:
		Item* head;
		Item* tail;
		
	public:
		List();
		~List(); 
	
		void Add(Item *item);
	
		Item* GetItem(int number);
		
		Item* Remove (int pos);
	
		void Delete(int pos);
		
		void Insert (int pos, Item *insert);
		
		int GetIndex (Item *elem);
	
		int CountElem ();
		
		void Clear();
		
		Item* Head(){return head;}
		Item* Tail(){return tail;}
		
		Base& operator[](int i);
};

#endif

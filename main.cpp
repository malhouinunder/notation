#include <iostream>
#include "list.h"
#include "current.h"

using namespace std;

class DebugList : public List
{
public:
    void printList();
    int menuCase();
    int elemNum();
    void Print();
};

void DebugList::Print()
{
    for (Item* it = Head(); it; it = it->Next())
    {
        Base* p = dynamic_cast<Base*>(it);
        if (p)
            p->Print();
    }
}

void DebugList::printList()
{
    int i;
    Item* p;

    cout << "\t#\tp\tp->Prev()\tp->Next()\tValues\n";
    for (p = Head(), i = 0; p; p = p->Next(), i++)
    {
        cout << "\t" << i << "\t" << p << "\t" << p->Prev()
             << "\t" << p->Next() << "\t";

        Base* b = dynamic_cast<Base*>(p);
        if (b)
            b->Print();
        else
            cout << "[Not a Base object]";

        cout << endl;
    }
}

int DebugList::menuCase()
{
    int a;
    cout <<
        "\nEnter menu option\n"
        "1. Add value to List\n"
        "2. Convert value\n"
        "3. Print List\n"
        "4. Compare objects\n"
        "5. Delete one value\n"
        "6. Clear\n"
        "7. Exit\n";

    cin >> a;
    return a;
}

int DebugList::elemNum()
{
    int pos;
    cout << "enter element number: ";
    cin >> pos;
    return pos;
}

int main()
{
    DebugList L;
    int a;

    do
    {
        a = L.menuCase();

        switch (a)
        {
        case 1:
        {
            Base* p = Base::create_object();
            p->AddObjectValue();
            L.Add(static_cast<Item*>(p));
            break;
        }

        case 2:
        {
            AnyBaseInt temp;

            temp.Convertation();

            int k;
            cout << "\ndo you want to save this value? 1. yes 2. no\n";
            cin >> k;

            if (k == 1)
            {
                Base* p = new AnyBaseInt(temp);
                L.Add(p);
            }
            break;
        }

        case 3:
        {
            if (L.Head())
                L.printList();
            else
                cout << "no elements yet\n";
            break;
        }

        case 4:
        {
            int n1, n2;
            cout << "enter two element numbers: ";
            cin >> n1 >> n2;

            Item* i1 = L.GetItem(n1);
            Item* i2 = L.GetItem(n2);

            if (!i1 || !i2)
            {
                cout << "wrong indexes\n";
                break;
            }

            AnyBaseInt* p1 = dynamic_cast<AnyBaseInt*>(i1);
            AnyBaseInt* p2 = dynamic_cast<AnyBaseInt*>(i2);

            if (!p1 || !p2)
            {
                cout << "wrong object type\n";
                break;
            }

            int res = p1->Compare_objects(*p1, *p2);

            if (res == 1)
                cout << "first > second\n";
            else if (res == 2)
                cout << "second > first\n";
            else
                cout << "equal\n";

            break;
        }

        case 5:
        {
            L.Delete(L.elemNum());
            break;
        }

        case 6:
        {
            L.Clear();
            break;
        }

        case 7:
            break;

        default:
            cout << "wrong menu option\n";
        }

    } while (a != 7);

    return 0;
}


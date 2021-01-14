#include<iostream>
#include<climits>
using namespace std;

class LinkedList
{
private:

    struct node
    {
        int value;
        node* next;
        node(int value):value(value),next(nullptr)
        {
        }
    };

    node *head, *tail;
    int size;

    static node* getPlaceholderNode()
    {
        return new node(INT_MAX);
    }

    bool isPlaceholderNode(node* n)
    {
        return n->value == INT_MAX;
    }

public:

    LinkedList()
    {
        head = getPlaceholderNode();
        tail = head;
        size = 0;
    }

    int getSize()
    {
        return this->size;
    }

    void add_first(int value)
    {
        node* n = new node(value);
        if(isPlaceholderNode(head))
        {
            tail = n;
        }
        n->next = head;
        head = n;
        size++;
    }

    void remove_first()
    {
        if(getSize()>0)
        {
            node* current = head;
            head = head->next;
            delete current;
            if(getSize()==1)
                tail = head;
            size--;
        }
    }

    void add_last(int value)
    {
        node* n = new node(value);
        if(isPlaceholderNode(head) && isPlaceholderNode(tail))
        {
            head = n;
            n->next = tail;
            tail = n;
        }
        else
        {
            node* pn = tail->next;
            tail->next = n;
            n->next = pn;
            tail = n;
        }
        size++;
    }

    // removes a node from the back of the list
    void remove_last()
    {
        if(getSize()>0)
        {
            if(getSize()==1)
            {
                node* current = head;
                head = current->next;
                tail = current->next;
                delete current;
                size--;
            }
            else
            {
                node* prev = head;
                for(int i=0; i<getSize()-2; ++i)
                {
                    prev = prev->next;
                }
                node* current = prev->next;
                prev->next = current->next;
                tail = prev;
                delete current;
                size--;
            }
        }
        else
            cout << "Error: List is empty" << endl;
    }

    void insert_at(int idx, int value)
    {
        if(idx==0 || getSize() == 0)
        {
            add_first(value);
        }
        else if(idx > 0 && idx < getSize())
        {
            node* n = new node(value);
            node* current = head;
            for(int i = 0; i<idx-1; ++i)
                current = current->next;
            node* temp = current->next;
            current->next = n;
            n->next = (temp);
            size++;
        }
        else
        {
            cout << "invalid index" << endl;
        }
    }

    void remove_at(int idx)
    {
        if(idx >= 0 && idx < getSize())
        {
            if(idx == 0)
                remove_first();
            else if(idx == getSize()-1)
                remove_last();
            else
            {
                node* prev = head;
                for(int i = 0; i<idx-1; ++i)
                    prev = prev->next;
                node* current = prev->next;
                prev->next = current->next;
                delete current;
                size--;
            }
        }
        else
            cout << "Invalid index" << endl;
    }

    //declaration
    friend ostream & operator<<(ostream & os, LinkedList & L)
    {
        node* head = L.head;
        while(!L.isPlaceholderNode(head))
        {
            os << (head->value) << " ";
            head = head->next;
        }
        return os;
    }

};

int main()
{
    LinkedList m;
    m.add_first(4);    // 4
    m.add_first(9);    // 9 -> 4
    m.add_last(12);    // 9 -> 4 -> 12

    cout << m << endl;

    m.insert_at(1, 99); // 9 -> 99 -> 4 -> 12
    m.insert_at(0, 1); // 1 -> 9 -> 99 -> 4 -> 12

    cout << m << endl;

    return 0;
}

#include <iostream>
#include <math.h>
using namespace std;

// Multiplication method + Open addressing

#define TABLE_SIZE 193

struct Node
{
public:
    unsigned int data;
    Node *next;

    Node();

    Node(unsigned int d)
    {
        this->data = d;
        next = NULL;
    }
};

class List
{
private:
    Node *node;

public:
    bool Insert(unsigned int x);
    bool Delete(unsigned int x);
    bool Search(unsigned int x);
    void Print();

    List()
    {
        node = NULL;
    }

    Node * getNode() {return this -> node;}
};

bool List::Insert(unsigned int x)
{
    if (node != NULL)
        return false;

    Node *temp = new Node(x);
    this->node = temp;
    return true;
}

bool List::Delete(unsigned int x)
{
    if (node == NULL)
        return false;

    if (node->data == x)
    {
        Node *temp = this->node;
        this->node = NULL;
        delete temp;
        return true;
    }
    return false;
}

bool List::Search(unsigned int x)
{
    if (node == NULL)
        return false;
    return node->data == x;
}

void List::Print()
{
    if (this->node == NULL)
        return;
    cout << node->data << " ";
}
// ----------------------------------------------------------------------------------------

class Hash
{
private:
    int BUCKET;
    List *table;
    int m_count;

public:
    Hash(int v);
    void Insert(unsigned int x);
    bool Delete(unsigned int x);
    bool Search(unsigned int x);
    int hashKey(unsigned int x) { return BUCKET * fmod((0.618034 * x) , 1.0); }
    void displayHash();

    void Rehashing(); // expand the size
};

Hash::Hash(int v)
{
    this->BUCKET = v;
    table = new List[BUCKET];
    m_count = 0;
}

void Hash::Insert(unsigned int x)
{
    int index = hashKey(x);
    int cnt = 0;
    
    while (cnt <= BUCKET)
    {
        if (table[index].Search(x))
            return;
        else if (table[index].Insert(x))
        {
            m_count++;
            break;
        }
        else
            index = (index + 1) % BUCKET;
        cnt++;
    }

    if ((float)m_count / BUCKET >= (float)3 / 4) // load factor >= 0.75
        Rehashing(); // add buckets
}

bool Hash::Delete(unsigned int x)
{
    int index = hashKey(x);
    int cnt = 0;

    while (cnt <= BUCKET)
    {
        if (table[index].Search(x))
        {
            m_count--;
            return table[index].Delete(x);
        }

        index = (index + 1) % BUCKET;
        cnt++;
    }
    return false;
}

bool Hash::Search(unsigned int x)
{
    int index = hashKey(x);
    int cnt = 0;

    while (cnt <= BUCKET)
    {
        if (table[index].Search(x))
            return true;

        index = (index + 1) % BUCKET;
        cnt++;
    }
    return false;
}

void Hash::displayHash()
{
    for (int i = 0; i < 20; i++)
    {
        cout << i << ": ";
        table[i].Print();
        cout << endl;
    }
}

void Hash::Rehashing()
{
    int newSize = BUCKET * 2; // BUCKET * 2

    List *newList = new List[newSize];
    List *temp = table;
    this->table = newList; // swap
    int oldBUCKET = this->BUCKET;

    this->BUCKET = newSize;
    this->m_count = 0;

    for (int i = 0; i < oldBUCKET; i++) {
        if (temp[i].getNode() != NULL) {
            this -> Insert(temp[i].getNode() -> data);
        }
    }

    delete temp; // delete the old one
}

int main()
{
    //clock_t tStart = clock();
    //freopen("caseIn-10000.txt", "r", stdin);

    int size = TABLE_SIZE;

    Hash h(size);
    string s;
    unsigned int val;

    while (cin >> s >> val)
    {
        if (s == "insert") {
            h.Insert(val);
        }
        else if (s == "delete")
        {
            if (h.Delete(val))
                printf("%u was deleted successfully\n", val);
            else
                printf("%u does not exist\n", val);
        }
        else if (s == "search")
        {
            if (h.Search(val))
                printf("%u was found\n", val);
            else
                printf("%u does not exist\n", val);
        }

        else if (s == "print")
        {
            h.displayHash();
        }
    }

    //printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    return 0;
}
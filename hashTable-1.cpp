#include <iostream>
using namespace std;

// Division method + Separate chaining

#define TABLE_SIZE 193

struct Node
{
public:
    unsigned int data;
    Node *next;

    Node(unsigned int d)
    {
        this->data = d;
        next = NULL;
    }
};

class LinkedList
{
private:
    Node *head;
    int m_count;

public:
    void Insert(unsigned int x);
    bool Delete(unsigned int x);
    bool Search(unsigned int x);
    void Print();

    LinkedList()
    {
        head = NULL;
        m_count = 0;
    }
};

void LinkedList::Insert(unsigned int x)
{
    Node *node = new Node(x);

    if (head == NULL)
    {
        head = node;
        m_count++;
        return;
    }

    Node *cur = head;

    while (cur->next != NULL)
    {
        if (cur->data == x)
            break;
        cur = cur->next;
    }

    if (cur->data != x)
    {
        cur->next = node;
        m_count++;
    }
}

bool LinkedList::Delete(unsigned int x)
{
    if (head == NULL)
        return false;

    Node *cur = head,
         *prev = head;
    int cnt = 0;

    while (cur != NULL)
    {
        if (cur->data == x)
            break;

        cnt++;
        prev = cur;
        cur = cur->next;
    }

    if (cur != NULL && cur->data == x)
    {
        Node *temp;
        if (cnt == 0)
        {
            temp = head;
            head = head->next;
        }
        else if (cnt == m_count)
        {
            temp = cur;
            prev->next = NULL;
        }
        else
        {
            temp = cur;
            prev->next = cur->next;
        }
        delete temp;
        return true;
    }
    return false;
}

bool LinkedList ::Search(unsigned int x)
{
    if (head == NULL)
        return false;

    Node *cur = head;

    while (cur != NULL)
    {
        if (cur->data == x)
            return true;
        cur = cur->next;
    }

    return false;
}

void LinkedList ::Print()
{
    if (head == NULL)
        return;

    Node *cur = head;
    while (cur != NULL)
    {
        cout << cur->data << " ";
        cur = cur->next;
    }
}

// ----------------------------------------------------------------------------------------

class Hash
{
private:
    int BUCKET;
    LinkedList *table;

public:
    Hash(int v);
    void Insert(unsigned int x);
    bool Delete(unsigned int x);
    bool Search(unsigned int x);
    int hashKey(unsigned int x) { return x % BUCKET; }
    void displayHash();
};

Hash::Hash(int v)
{
    this->BUCKET = v;
    table = new LinkedList[BUCKET];
}

void Hash::Insert(unsigned int x)
{
    if (Search(x))
        return;
    int index = hashKey(x);
    table[index].Insert(x);
}

bool Hash::Delete(unsigned int x)
{
    int index = hashKey(x);
    return table[index].Delete(x);
}

bool Hash::Search(unsigned int x)
{
    int index = hashKey(x);
    return table[index].Search(x);
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

int main()
{
    //clock_t tStart = clock();
    freopen("caseIn-10000.txt", "r", stdin);

    int size = TABLE_SIZE;

    Hash h(size);
    string s;
    unsigned int val;

    while (cin >> s >> val)
    {
        if (s == "insert")
            h.Insert(val);
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
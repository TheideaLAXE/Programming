#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct List {
    Node* start;
    List() {
        start = new Node();   // dummy node
        start->next = nullptr;
    }
};

void Insert(List &l, int x);
void BubbleSort(List &l);
void InsertionSort(List &l);
void Print(List &l);

void Insert(List &l, int x) {
    Node *p = l.start;
    while (p->next)
        p = p->next;
    p->next = new Node();
    p->next->val = x;
    p->next->next = nullptr;
}

void BubbleSort(List &l) {
    if (!l.start) return;
    Node *p, *q = l.start->next;  // skip dummy node
    while (true) {
        bool Y = true;
        p = q;
        while (p->next) {
            if (p->val > p->next->val) {
                int temp = p->val;
                p->val = p->next->val;
                p->next->val = temp;
                Y = false;
            }
            p = p->next;
        }
        if (Y) break;
    }
}


void InsertionSort(List &l) {
    if (!l.start || !l.start->next) return;
    Node *p = l.start;
    while (p->next) {
        int x = p->next->val;
        Node *q = l.start;
        while (q->next!=p->next && q->next->val<x)
            q=q->next;
        if (q->next==p->next) {
            p=p->next;
            continue;
        }
        Node* p1=p->next;
        p->next = p1->next;
        Node *t = new Node();
        t->val = x;
        t->next = q->next;
        q->next = t;
        delete p1;
    }
}

void Print(List &l) {
    Node *p=l.start;
    while (p->next) {
        std::cout << p->next->val << " ";
        p=p->next;
    }
}

int main() {
    List l;
    int n;
    while (std::cin>>n)
        Insert(l, n);
    InsertionSort(l);
    Print(l);
}

//1 2 5 8 6 7 a
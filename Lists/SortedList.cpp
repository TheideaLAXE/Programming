#include <iostream>

struct Node {
    int val;
    Node* next;
};

struct List {
    Node* head;
    List() {
        head = new Node();   // dummy node
        head->next = nullptr;
    }
};

void Insert(List &l, int x) {
    Node* p = l.head;
    while (p->next && p->next->val < x)
        p = p->next;

    if (p->next && p->next->val == x)
        return;

    Node* q = new Node();
    q->val = x;
    q->next = p->next;
    p->next = q;
}

void Print(List &l) {
    Node *p=l.head;
    while (p->next) {
        std::cout << p->next->val << " ";
        p=p->next;
    }
}


int main() {
    int n;
    List l;
    while (std::cin>>n)
        Insert(l, n);

    Print(l);
}

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
void SortInsert(List &l, int x);
void Print(List &l);
void BubbleSort(List &l);
void Merge(List &l1, List &l2);
void DelDup(List &l);

void Insert(List &l, int x) {
    Node *p = l.start;
    while (p->next)
        p=p->next;
    p->next = new Node();
    p->next->val = x;
    p->next->next = nullptr;
}

void SortInsert(List &l, int x) {
    Node* p = l.start;
    while (p->next && p->next->val < x)
        p = p->next;

    if (p->next && p->next->val == x)
        return;

    Node* q = new Node();
    q->val = x;
    q->next = p->next;
    p->next = q;
}

void BubbleSort(List &l) {
    if (!l.start->next) return;
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

void Merge(List &l1, List &l2) {
    if (!l1.start || !l2.start) return;
    Node *p = l2.start->next;  // skip dummy node
    while (p) {
        SortInsert(l1, p->val);
        p = p->next;
    }
}

void DelDup(List &l) {
    if (!l.start->next) return;
    if (!l.start->next->next) return;
    Node *p = l.start->next;
    while (p->next) {
        if (p->val == p->next->val) {
            Node * q=p->next->next;
            delete p->next;
            p->next = q;
        }
        else
            p=p->next;
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
    List l1, l2;
    int n;
    while (std::cin>>n) {
        Insert(l1, n);
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    while (std::cin>>n) {
        Insert(l2, n);
    }
    BubbleSort(l1);
    DelDup(l1);
    Merge(l1, l2);
    Print(l1);
}
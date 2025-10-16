#include <iostream>

struct Node {
    int val;
    Node *next, *prev;
};

struct DubList {
    Node* start;
    DubList() {
        start = new Node();
        start->val = -1; //no grabo
        start->next = nullptr;
        start->prev = nullptr;
    }
};


void DubListAdd(DubList &l, int val, Node *whereafter);
void DubListRemove(DubList &l, Node *remnode);
void DubListPrint(const DubList &l);
Node * DubListFind(const DubList &l, int val);

void DubListAdd(DubList &l, int x, Node *whereafter=nullptr) {
    if (whereafter==nullptr) {
        Node *p = l.start;
        while (p->next)
            p = p->next;
        Node *q = new Node();
        q->val = x;
        q->next = nullptr;
        q->prev = p;
        p->next = q;
    }
    else {
        Node *p = whereafter;
        Node *q = new Node();
        q->val = x;
        if (p->next) {
            q->next = p->next;
            p->next->prev = q;
            q->prev = p;
            p->next = q;
        }
        else {
            q->next = nullptr;
            q->prev = p;
            p->next = q;
        }
    }
}

void DubListRemove(DubList &l, Node *remnode) {
    Node *t=l.start;
    bool B=false;
    while (t->next) { //O(n) to check if the node belongs in the list
        if (t->next==remnode) {
            B=true;
            break;
        }
        t=t->next;
    }
    if (!B)
        return;


    if (remnode==nullptr) return;
    Node *p = remnode;
    if (p==l.start) return;
    p=p->prev;
    if (remnode->next) {
        Node *q = remnode->next;
        p->next = q;
        q->prev = p;
        delete remnode;
    }
    else {
        p->next = nullptr;
        delete remnode;
    }
}

Node * DubListFind(const DubList &l, int val) {
    Node *p = l.start;
    while (p->next) {
        if (p->next->val==val)
            return p->next;
        p=p->next;
    }
    return nullptr;
}

void DubListPrint(const DubList &l) {
    Node *p = l.start;
    while (p->next) {
        std::cout << p->next->val << " ";
        p = p->next;
    }
}

int main() {
    DubList l;

    return 0;
}
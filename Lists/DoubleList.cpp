#include <iostream>

struct Node {
    int val;
    Node *next, *prev;
};

struct DubList {
    Node* start;
    DubList() {
        start = new Node();
        start->val = -1;
        start->next = nullptr;
        start->prev = nullptr;
    }
};


void DubListAdd(DubList &l, int val, Node *whereafter);
void DubListRemove(DubList &l, Node *remnode);
void DubListPrint(const DubList &l);
Node * DubListFind(const DubList &l, int val);

void DubListAdd(DubList &l, int x, Node *after=nullptr) {
    if (after==nullptr) {
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
        Node *p = l.start;
        bool InList = false;
        while (p->next) {   //O(n) to check if the node belongs in the list
            if (p->next==after) {
                InList = true;
                break;
            }
            p = p->next;
        }
        if (!InList)
            return;
        Node *q = new Node();
        q->val = x;
        if (after->next) {
            q->next = after->next;
            after->next->prev = q;
            q->prev = after;
            after->next = q;
        }
        else {
            q->next = nullptr;
            q->prev = after;
            after->next = q;
        }
    }
}

void DubListRemove(DubList &l, Node *remnode) {
    Node *p=l.start;
    bool InList=false;
    while (p->next) {   //O(n) to check if the node belongs in the list
        if (p->next==remnode) {
            InList=true;
            break;
        }
        p=p->next;
    }
    if (!InList)
        return;

    if (remnode==nullptr) return;
    p = remnode->prev;
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
    int n;
    DubList l;
    while (std::cin>>n)
        DubListAdd(l, n);
    Node *p = DubListFind(l, 3);
    std::cout << p << "\n";
    DubListPrint(l);

    return 0;
}

//1 2 3 4 5 6 7 8 9 0 9 8 7 6 5 4 3 2 1 a
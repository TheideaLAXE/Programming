#include <iostream>
#include <climits>
#include <stack>

using namespace std;

struct BT {
    int val;
    BT *left=nullptr;
    BT *right=nullptr;
    BT(const int _v=INT_MIN) {
        val=_v;
        left=nullptr;
        right=nullptr;
    }
};

void insertBT(BT *r, const string &s, const int x) {
    if (r->val == INT_MIN) {
        r->val = x;
        return;
    }
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'L') {
            if (r->left) r = r->left;
            else {
                r->left = new BT(x);
                return;
            }
        }
        else if (s[i] == 'R') {
            if (r->right) r = r->right;
            else {
                r->right = new BT(x);
                return;
            }
        }
    }
    r->val = x;
}

void insertBST(BT *r, const int val) {
    if (r->val==INT_MIN) {
        r->val=val;
        return;
    }
    if (val<r->val) {
        if (r->left) insertBST(r->left, val);
        else {
            r->left = new BT(val);
        }
    }
    else if (val>r->val) {
        if (r->right) insertBST(r->right, val);
        else {
            r->right = new BT(val);
        }
    }
}

bool findBST(const BT *r, const int val) {
    if (r->val==INT_MIN) return false;
    if (r->val==val) {
        return true;
    }
    if (r->val>val) {
        if (r->left) return findBST(r->left, val);
        return false;
    }
    if (r->right) return findBST(r->right, val);
    return false;
}

bool findBT(const BT *r, const int val) {
    if (r->val==INT_MIN) return false;
    if (r->val==val) return true;
    if (r->left) {
        if (findBT(r->left, val)) return true;
    }
    if (r->right) return findBT(r->right, val);
    return false;
}

void preorder(const BT *r) {
    cout << r->val << " ";
    if (r->left) preorder(r->left);
    if (r->right) preorder(r->right);
}

void inorder(const BT *r) {
    if (r->left) inorder(r->left);
    cout << r->val << " ";
    if (r->right) inorder(r->right);
}

void postorder(const BT *r) {
    if (r->left) postorder(r->left);
    if (r->right) postorder(r->right);
    cout << r->val << " ";
}

void preorder2() {
    //TODO
}
void inorder2() {
    //TODO
}
void postorder2() {
    //TODO
}



int sum(const BT *r) {
    int s = r->val;
    if (r->left) s+=sum(r->left);
    if (r->right) s+=sum(r->right);
    return s;
}


void delTree(BT *r) {
    if (!r) return;
    if (r->left) delTree(r->left);
    if (r->right) delTree(r->right);
    delete r;
}

int main() {
    int n;
    cin >> n;
    if (n<1) return 0;
    int x;
    string s; //L-left, R-right
    cin >> x;
    BT *r = new BT(x); //root

    for (int i=0; i<n-1; i++) {
        cin >> s;
        cin >> x;
        //x=i+1;
        insertBT(r, s, x);
    }
    cout << sum(r) << "\n";
    preorder(r);
    cout << "\n";
    inorder(r);
    cout << "\n";
    postorder(r);
    cout << "\n";
    for (int i=0; i<10; i++) {
        cout << findBST(r, i) << " ";
    }

    delTree(r);

    return 0;
}

/*
7
0
L 1
R 2
LL 3
LR 4
RL 5
RR 6
*/
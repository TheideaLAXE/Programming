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

void preorder2(const BT *r) {
    if (r->val==INT_MIN) return;
    stack<const BT*> st;
    st.push(r);

    while (!st.empty()) {
        const BT *curr = st.top();
        st.pop();
        cout << curr->val << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left) st.push(curr->left);
    }
}

void inorder2(const BT *r) {
    if (!r || r->val==INT_MIN) return;
    const BT* s[1000];
    int top = -1;
    const BT* curr = r;

    while (top >= 0 || curr) {
        while (curr) {
            top++;
            s[top] = curr;
            curr = curr->left;
        }
        curr = s[top];
        top--;
        cout << curr->val << " ";
        curr = curr->right;
    }
}

void postorder2(const BT *r) {
    if (!r || r->val==INT_MIN) return;
    const BT* s1[1000];
    const BT* s2[1000];
    int top1 = 0, top2 = -1;
    s1[top1] = r;

    while (top1 >= 0) {
        const BT* curr = s1[top1];
        top1--;

        top2++;
        s2[top2] = curr;

        if (curr->left) {
            top1++;
            s1[top1] = curr->left;
        }
        if (curr->right) {
            top1++;
            s1[top1] = curr->right;
        }
    }
    while (top2 >= 0) {
        cout << s2[top2]->val << " ";
        top2--;
    }
}

int sum(const BT *r) {
    int s = r->val;
    if (r->left) s+=sum(r->left);
    if (r->right) s+=sum(r->right);
    return s;
}



void bfs(const BT *r) {
    if (!r || r->val == INT_MIN) return;
    const BT* q[1000];
    int front = 0, back = 0;
    q[back] = r;
    back++;

    while (front < back) {
        const BT* curr = q[front++];
        cout << curr->val << " ";
        if (curr->left) {
            q[back] = curr->left;
            back++;
        }
        if (curr->right) {
            q[back] = curr->right;
            back++;
        }
    }
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
    string s;
    cin >> x;
    BT *r = new BT(x);

    for (int i=0; i<n-1; i++) {
        cin >> s;
        cin >> x;
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
        cout << findBT(r, i) << " ";
    }
    cout << "\n";
    bfs(r);
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

21
0 1 3 4 2 5 6
3 1 4 0 5 2 6
3 4 1 5 6 2 0
1 1 1 1 1 1 1 0 0 0
0 1 2 3 4 5 6
*/

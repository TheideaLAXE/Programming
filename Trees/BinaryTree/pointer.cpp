#include <iostream>
#include <climits>
#include <stack>
#include <queue>
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
    if (!r || r->val == INT_MIN) return;
    stack<const BT*> st;
    st.push(r);

    while (!st.empty()) {
        const BT *curr = st.top();
        st.pop();
        cout << curr->val << " ";
        if (curr->right) st.push(curr->right);
        if (curr->left)  st.push(curr->left);
    }
}

void inorder2(const BT *r) {
    if (!r || r->val == INT_MIN) return;
    stack<const BT*> s;
    const BT* curr = r;
    while (curr || !s.empty()) {
        while (curr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        cout << curr->val << " ";
        curr = curr->right;
    }
}

void postorder2(const BT *r) {
    if (!r || r->val == INT_MIN) return;
    stack<const BT*> s1, s2;
    s1.push(r);
    while (!s1.empty()) {
        const BT* curr = s1.top();
        s1.pop();
        s2.push(curr);
        if (curr->left)  s1.push(curr->left);
        if (curr->right) s1.push(curr->right);
    }
    while (!s2.empty()) {
        cout << s2.top()->val << " ";
        s2.pop();
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
    queue<const BT*> q;
    q.push(r);

    while (!q.empty()) {
        const BT* curr = q.front(); q.pop();
        cout << curr->val << " ";
        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
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

#include <iostream>
#include <climits>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

void insertBT(vector<int> &v, const int val) {
    for (int i=0; i<v.size(); i++) {
        if (v[i]==INT_MIN) {
            v[i]=val;
            return;
        }
    }
    v.push_back(val);
}

void insertBST(vector<int> &v, const int val) {
    int i=0;
    while (i<v.size() && v[i]!=INT_MIN) {
        if (v[i]>val) i=i*2+1;
        else if (v[i]<val) i=i*2+2;
        else return;
    }
    if (i>=v.size()) v.resize(i+1, INT_MIN);
    v[i]=val;
}

bool findBT(const vector<int> &v, const int val) { ///ig?
    for (int i=0; i<v.size(); i++) {
        if (v[i]==val) return true;
    }
    return false;
}

bool findBST(const vector<int> &v, const int val) {
    int i = 0;
    while (i<v.size() && v[i]!=INT_MIN) {
        if (v[i]==val) return true;
        if (val<v[i]) i=2*i+1;
        else i=2*i+2;
    }
    return false;
}

int sum(const vector<int> &v, const int t=0) {
    if (t >=v.size() || v[t]==INT_MIN) return 0;
    int s=v[t];
    s+=sum(v, 2*t+1);
    s+=sum(v, 2*t+2);
    return s;
}


void preorder(const vector<int> &v, const int p=0) {
    if (p<v.size() && v[p]!=INT_MIN) {
        cout << v[p] << " ";
        preorder(v, p*2+1);
        preorder(v, p*2+2);
    }
}

void inorder(const vector<int> &v, const int p=0) {
    if (p<v.size() && v[p]!=INT_MIN) {
        inorder(v, p*2+1);
        cout << v[p] << " ";
        inorder(v, p*2+2);
    }
}

void postorder(const vector<int> &v, const int p=0) {
    if (p<v.size() && v[p]!=INT_MIN) {
        postorder(v, p*2+1);
        postorder(v, p*2+2);
        cout << v[p] << " ";
    }
}

void preorder2(const vector<int> &v) {
    if (v.empty() || v[0]==INT_MIN) return;
    stack<int> s;
    s.push(0);
    while (!s.empty()) {
        const int i = s.top();
        s.pop();
        if (i >= v.size() || v[i]==INT_MIN) continue;
        cout << v[i] << " ";
        const  int r = 2*i+2;
        const int l = 2*i+1;
        if (r < v.size() && v[r]!=INT_MIN) s.push(r);
        if (l < v.size() && v[l]!=INT_MIN) s.push(l);
    }
}

void inorder2(const vector<int> &v) {
    if (v.empty() || v[0]==INT_MIN) return;
    stack<int> s;
    int curr = 0;
    while (!s.empty() || (curr < v.size() && v[curr]!=INT_MIN)) {
        while (curr < v.size() && v[curr]!=INT_MIN) {
            s.push(curr);
            curr = 2*curr+1;
        }
        if (s.empty()) break;
        curr = s.top();
        s.pop();
        cout << v[curr] << " ";
        curr = 2*curr+2;
    }
}

void postorder2(const vector<int> &v) {
    if (v.empty() || v[0]==INT_MIN) return;
    stack<int> s1, s2;
    s1.push(0);
    while (!s1.empty()) {
        const int i = s1.top();
        s1.pop();
        if (i >= v.size() || v[i]==INT_MIN) continue;
        s2.push(i);
        const int l = 2*i+1;
        const int r = 2*i+2;
        if (l < v.size() && v[l]!=INT_MIN) s1.push(l);
        if (r < v.size() && v[r]!=INT_MIN) s1.push(r);
    }
    while (!s2.empty()) {
        cout << v[s2.top()] << " ";
        s2.pop();
    }
}

void bfs(const vector<int> &v) {
    if (v.empty() || v[0]==INT_MIN) return;
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        const int i = q.front();
        q.pop();
        if (i >= v.size() || v[i]==INT_MIN) continue;
        cout << v[i] << " ";
        const int l = 2*i+1;
        const int r = 2*i+2;
        if (l < v.size() && v[l]!=INT_MIN) q.push(l);
        if (r < v.size() && v[r]!=INT_MIN) q.push(r);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n, INT_MIN);
    int x;
    for (int i=0; i<n; i++) {
        cin >> x;
        insertBT(v, x);
    }
    cout << sum(v) << "\n";
    preorder(v);
    cout << "\n";
    inorder(v);
    cout << "\n";
    postorder(v);
    cout << "\n";
    for (int i=0; i<10; i++) {
        cout << findBT(v, i) << " ";
    }
    cout << "\n\n\n";
    bfs(v);
    return 0;
}

/*
7
1 2 3 4 5 6 7

28
1 2 4 5 3 6 7
4 2 5 1 6 3 7
4 5 2 6 7 3 1
0 1 1 1 1 1 1 1 0 0
 */
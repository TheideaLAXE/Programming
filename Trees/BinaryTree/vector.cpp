#include <iostream>
#include <climits>
#include <vector>

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
    //TODO
}
void inorder2(const vector<int> &v) {
    //TODO
}
void postorder2(const vector<int> &v) {
    //TODO
}


int main() {
    int n;
    cin >> n;
    vector<int> v(n, INT_MIN);
    int x;
    for (int i=0; i<n; i++) {
        cin >> x;
        insertBST(v, x);
    }
    preorder(v);
    cout << "\n";

    inorder(v);
    cout << "\n";

    postorder(v);
    cout << "\n";


    return 0;
}
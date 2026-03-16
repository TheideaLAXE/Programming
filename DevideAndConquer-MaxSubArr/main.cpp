#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define mm max
#define MM INT_MIN

using namespace std;

int funk(vector<int> &v, const int l, const int r) {
    if (l==r) return v[l];
    const int mid=l+(r-l)/2;
    const int L = funk(v, l, mid);
    const int R = funk(v, mid+1, r);

    int sum=0, c1=MM, c2=MM;
    for (int i=mid; i>=l; i--) {
        sum+=v[i];
        c1=mm(c1, sum);
    }
    sum=0;
    for (int i=mid+1; i<=r; i++) {
        sum+=v[i];
        c2=mm(c2, sum);
    }

    return mm({L, R, c1+c2});
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++) cin >> v[i];

    int res = funk(v, 0, v.size()-1);

    cout << res << " ";
    return 0;
}
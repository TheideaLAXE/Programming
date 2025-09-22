#include <bits/stdc++.h>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i=1; i<n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j>=0 && arr[j]>key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int N=1e5;
vector<int> arr(N);

int main()
{
    for (int z=0; z<N; z++) arr[z] = rand();
    insertionSort(arr);
    return 0;
}
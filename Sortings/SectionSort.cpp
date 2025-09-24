#include <bits/stdc++.h>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i=0; i<n-1; i++) {
        int min = i;
        for (int j = i+1; j<n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        swap(arr[i], arr[min]);
    }
}

int N=1e5;
vector<int> arr(N);

int main()
{
    for (int z=0; z<N; z++) arr[z] = rand();
    selectionSort(arr);
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
int main() {
    int t;
    while (t--) {
        int n;
        cin >> n;
        int a[n];
        for (int i = 0;i < n;i++)
            cin >> a[i];
        for (auto x : a)
            cout << x << " ";
        cout << "\n";
    }
    return 0;
}

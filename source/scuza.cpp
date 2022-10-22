#include <bits/stdc++.h>
using namespace std;

void solve()
{
    vector <long long> h;
    vector <long> b;
    int n, q;
    long a;

    h.push_back(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        h.push_back(h.back() + a);
        if (i == 0)
        {
            b.push_back(a);
        }
        else 
        {
            b.push_back(max(b.back(), a));
        }
    }

    for (int i = 0; i < q; i++)
    {
        long k;
        cin >> k;
        int index = upper_bound(b.begin(), b.end(), k) - b.begin();
        cout << h[index] << " ";
    }
    cout << endl;
}


int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}
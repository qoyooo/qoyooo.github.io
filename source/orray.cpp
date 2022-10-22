#include <bits/stdc++.h>
using namespace std;

bool find(const vector<long> a, const long t, const int l, int &index)
{
    long max = t;
    bool found = false;
    for (int i = l; i < a.size(); i++)
    {
        if ((t | a[i]) > max)
        {
            max = (t | a[i]);
            index = i;
            found = true;
        }
    }
    return found;
}

void solve()
{
    int n, x;
    vector<long> a;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        a.push_back(x);
    }

    int i = 0;
    long t = 0;
    int index = 0;

    while (find(a, t, i, index) && (i < n))
    {

        long temp = a[index];
        a.erase(a.begin()+index);
        a.insert(a.begin()+i, temp);
        t += temp;
        i++;
    }

    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
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
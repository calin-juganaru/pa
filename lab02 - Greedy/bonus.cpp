#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using T = pair<int, int>;

int main()
{
    int n, k;
    cin >> n >> k;

    auto v = vector<T>(n);

    for (auto&& it: v)
        cin >> it.first;
    for (auto&& it: v)
        cin >> it.second;

    sort(begin(v), end(v), [&](const T& x, const T& y)
    {
        return (x.first - x.second) < (y.first - y.second);
    });

    auto sol = 0;
    for (auto&& [now, after]: v)
    {
        if (k)
        {
            --k;
            sol += now;
        }
        else sol += min(now, after);
    }

    cout << sol << endl;
}
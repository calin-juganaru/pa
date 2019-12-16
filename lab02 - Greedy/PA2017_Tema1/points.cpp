#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
using T = pair<int, int>;

int main()
{
    ifstream fin("./public_tests/points/input/3-points.in");
    int N, M;
    fin >> N >> M;
    auto P = vector<pair<int, int>>(N);
    auto I = vector<T>(M);
    
    for (auto&& it: P)
    {
        fin >> it.first;
        it.second = 0;
    }
    
    for (auto&& [st, dr]: I)
        fin >> st >> dr;

    sort(begin(I), end(I), [&](const T& x, const T& y)
    {
        //if (x.second == y.second)
        //    return x.first < y.first;
        return x.second < y.second;
    });

    auto sol = 0;
    for (auto&& [st, dr]: I)
    {
        //cout << st << ' ' << dr << endl;
        auto ales = false;
        auto count = 0;
        for (auto&& [pct, ok]: P)
            if (st <= pct && pct <= dr)
            {
                if (ok)
                {
                    ales = true;
                }
                else
                {
                    ++ok;
                }
            }
        if (!ales)
                        ++sol;
    }

    cout << sol << endl;
}
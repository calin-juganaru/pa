#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;
 
int main()
{
    freopen("rucsac.in", "r", stdin);
    freopen("rucsac.out", "w", stdout);

    int N, G; cin >> N >> G;
    auto v = vector<pair<int, int>>(N);
    auto sol = vector<int>(G + 1);
    for (auto&& [gr, val]: v)
        cin >> gr >> val;

    for (auto&& [gr, val]: v)
        for(auto j = G; j >= gr; --j)
            if(gr <= j) 
                sol[j] = max(val + sol[j - gr], sol[j]);
    cout << sol[G] << endl;
}
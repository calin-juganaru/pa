#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

using namespace std;
using vector_t = vector<int>;
using pair_t = pair<int, int>;
using pvect_t = vector<pair_t>;

void drum(const int& x, const int& y, vector<pvect_t>& pred)
{
    if (pred[x][y] != pair(-1, -1))
    {
        auto [i, j] = pred[x][y];
        drum(i, j, pred);
        cout << "(" << i + 1 << ", " << j + 1 << ") --> ";
    }
    return;
}

int main()
{
    auto input = ifstream("bonus.in");
    int N, x, y; input >> N;
    input >> x >> y; --x; --y;

    auto harta = vector<vector_t>(N, vector_t(N));
    for (auto&& linie: harta)
        for (auto&& elem: linie)
            input >> elem;

    auto dist = vector<vector_t>(N, vector_t(N, -1));
    auto pred = vector<pvect_t>(N, pvect_t(N, {-1, -1}));
    auto q = queue<pair_t>();

    dist[x][y] = 0;
    q.push({x, y});

    while (!q.empty())
    {
        auto&& [i, j] = q.front(); q.pop();
        for (auto&& [di, dj]: {pair{i - 1, j}, {i + 1, j}, {i, j - 1}, {i, j + 1}})
            if (di >= 0 && di < N && dj >=0 && dj < N)
                if (dist[di][dj] == -1)
                    if (harta[di][dj] != 1)
                    {
                        q.push({di, dj});
                        dist[di][dj] = dist[i][j] + 1;
                        pred[di][dj] = {i, j};
                    }
    }

    auto min_dist = 0x3f3f3f3f;
    for (auto i = 0; i < N; ++i)
        for (auto j = 0; j < N; ++j)
            if (harta[i][j] == 2 && min_dist > dist[i][j])
            {
                min_dist = dist[i][j];
                x = i; y = j;
            }

    cout << min_dist << endl;
    drum(x, y, pred);
    cout << "(" << x + 1 << ", " << y + 1 << ")\n";
}
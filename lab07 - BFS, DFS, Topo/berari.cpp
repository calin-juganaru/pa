#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
using vector_t = vector<int>;

int main()
{
    auto input  = ifstream("berarii2.in");
    auto output = ofstream("berarii2.out");

    int N, M, P, x, y; input >> N >> M >> P;
    auto vecini = vector<vector_t>(N + 1);
    auto berarii = vector_t(P);

    while (M--)
    {
        input >> x >> y; --x; --y;
        vecini[y].push_back(x);
    }

    for (auto&& it: berarii)
    {
        input >> it; --it;
        vecini[N].push_back(it);
    }

    auto viz = vector<bool>(N + 1);
    auto q = queue<int>();
    q.push(N); viz[N] = true;

    while (!q.empty())
    {
        auto node = q.front();
        q.pop();

        for (auto&& next: vecini[node])
        {
            if (!viz[next])
            {
                q.push(node);
                viz[next] = true;
            }
        }
    }

    auto result = 0;
    for (auto&& it: viz)
        if (!it) ++result;

    output << result << endl;
    for (auto i = 0; i < viz.size(); ++i)
        if (viz[i]) output << i + 1 << ' ';
}
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr auto inf = 0x3f3f3f3f;
int N, M, T, min_cal, max_cal, start, finish;

bool floyd(const int& nod, const vector<vector<int>>& adj,
		   vector<pair<int, int>>& calorii)
{
	//auto s = vector<vector<int>>(N + 1, vector<int>(N + 1, inf));
	auto s = adj;
	/*
	for (auto i = 1; i <= N; ++i)
		for (auto j = 1; j <= N; ++j)
			if (adj[i][j]) s[i][j] = adj[i][j];
	*/

    for (auto k = nod; k <= N; ++k)
    {
        for (auto i = nod; i <= N; ++i)
        	//if (s[i][k] < inf)
            	for (auto j = nod; j <= N; ++j)
					if (s[i][j] > s[i][k] + s[k][j] || !s[i][j])
						s[i][j] = s[i][k] + s[k][j];

        for (auto i = nod; i <= k; ++i)
        	for (auto j = nod; j <= k; ++j)
             	if (s[i][j] == T)
             	{
                	cout << "aici\n";
					start = i; finish = j;
					min_cal = calorii[nod].first;
					max_cal = calorii[k].first;
                 	return true;
             	}
    }
    return false;
}

int main()
{
	auto input  = ifstream("coach.in");
	auto output = ofstream("coach.out");

	input >> N >> M >> T;
	auto calorii = vector<pair<int, int>>(N + 1);
	calorii.push_back({0, 0});
	for (auto i = 1, c = 0; i <= N; ++i)
	{
		input >> c;
		calorii.push_back({c, i});
	}

	sort(begin(calorii), end(calorii));

	auto poz = vector<int>(N + 1);
	for (auto i = 1; i <= N; ++i)
		poz[calorii[i].second] = i;

	auto adj = vector<vector<int>>(N + 1, vector<int>(N + 1));
	for (auto i = 1, x = 0, y = 0, c = 0; i <= M; ++i)
	{
		input >> x >> y >> c;
		adj[poz[x]][poz[y]] = adj[poz[y]][poz[x]] = c;
	}

	for (auto i = 1; i <= N && !floyd(i, adj, calorii); ++i);

	output << calorii[start].second << ' '
           << calorii[finish].second << ' '
		   << min_cal << ' ' << max_cal << '\n';
}
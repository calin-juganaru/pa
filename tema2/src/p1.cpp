#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);

	auto input = ifstream("p1.in");
	auto output = ofstream("p1.out");

	int N; input >> N;
	auto min_dist = vector<pair<int, int>>(N + 1);
	auto nodes = vector<int>(N + 1, -1);
	auto edges = vector<pair<int, int>>();

	for (auto i = 1, aux = 0; i <= N; ++i)
	{
		input >> aux;

		// dacă un nod != 1 are distanța 0,
		//	atunci nu există soluție
		if (!aux && i > 1)
		{
			output << -1 << endl;
			return 0;
		}

		min_dist[i] = {aux, i};

		if (nodes[aux] == -1)
		{
			nodes[aux] = i;
		}
	}

	// sortez crescător vectorul
	//	întâi după distanțe, apoi după indici
	sort(begin(min_dist), end(min_dist));

	// dacă există discontinuități în vector,
	//	atunci nu există soluție
	for (auto i = 0; i < min_dist.size() - 1; ++i)
		if (min_dist[i + 1].first - min_dist[i].first > 1)
		{
			output << -1 << endl;
			return 0;
		}

	// pentru fiecare nod, diferit de primul
	for (auto i = 2; i <= N; ++i)
	{
		// obțin distanța și indicele
		auto [x, y] = min_dist[i];
		// obțin indicele primului nod
		//	cu distanța anterioară
		x = nodes[x - 1];
		// adaug o nouă muchie
		edges.push_back({x, y});
	}

	output << edges.size() << endl;
	for (auto&& edge: edges)
		output << edge.first << ' '
			   << edge.second << '\n';
}
#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

using long_t = long long;
using vector_t = vector<bool>;
using matrix_t = vector<vector_t>;
using graph_t = vector<vector<tuple<int, long_t, int>>>;

constexpr auto inf = 0x3f3f3f3f3f3f3f3fll;

int dijkstra(const graph_t& graph, const vector<long_t>& penalty)
{
	auto dist = vector<long_t>(graph.size(), inf);
	auto visited = vector_t(graph.size());
	auto used = matrix_t(graph.size(), vector_t(penalty.size()));

	auto comp = [&](const int& x, const int& y)
	{
		return dist[x] > dist[y];
	};

	auto heap = priority_queue<int, vector<int>,
							   decltype(comp)>(comp);
	dist[1] = 0; heap.push(1);

	while (!heap.empty())
	{
		auto node = heap.top();	heap.pop();
		if (visited[node]) continue;

		visited[node] = true;
		for (auto&& [next, cost, type]: graph[node])
		{
			// dacă penalizarea pentru acest tip
			//	a mai fost aplicată
			if (used[node][type])
			{
				// aplic o relaxare de Dijkstra
				if (dist[next] > dist[node] + cost)
				{
					dist[next] = dist[node] + cost;
					used[next] = used[node];
					heap.push(next);
				}
			}
			else
			{
				// altfel, actualizez distanța minimă
				//	luând în calcul și penalizarea
				if (dist[next] > dist[node] + cost + penalty[type])
				{
					dist[next] = dist[node] + cost + penalty[type];
					heap.push(next);

					used[next] = used[node];
					used[next][type] = true;
				}
			}
		}
	}

	return dist.back() == inf ? -1 : dist.back();
}

int main()
{
	ios_base::sync_with_stdio(false);

	auto input = ifstream("p4.in");
	auto output = ofstream("p4.out");

	int N, M, T; input >> N >> M >> T;
	auto graph = graph_t(N + 1);
	auto penalty = vector<long_t>(T + 1);

	int x, y, t;
	long_t c;
	while (M--)
	{
		input >> x >> y >> c >> t;
		graph[x].emplace_back(y, c, t);
		graph[y].emplace_back(x, c, t);
	}

	for (auto type = 1; type <= T; ++type)
		input >> penalty[type];

	output << dijkstra(graph, penalty) << endl;
}
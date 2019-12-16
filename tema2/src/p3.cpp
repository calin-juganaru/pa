#include <fstream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

using long_t = long long;
using vector_t = vector<long_t>;
using matrix_t = vector<vector_t>;
using graph_t = vector<vector<tuple<int, long_t, int>>>;

constexpr auto inf = 0x3f3f3f3f3f3f3f3fll;

int dijkstra(const graph_t& graph, const matrix_t& penalty)
{
	auto dist = vector<long_t>(graph.size(), inf);
	auto visited = vector<bool>(graph.size());
	auto last_type = vector_t(graph.size());

	auto comp = [&](const int& x, const int& y)
	{
		return dist[x] > dist[y];
	};

	auto heap = priority_queue<int, vector_t,
							   decltype(comp)>(comp);
	dist[1] = 0; heap.push(1);

	while (!heap.empty())
	{
		auto node = heap.top();	heap.pop();
		if (visited[node]) continue;

		visited[node] = true;
		for (auto&& [next, cost, type]: graph[node])
		{
			// actualizez distanța minimă luând în calcul și penalizarea
			if (dist[next] > dist[node] + cost + penalty[last_type[node]][type])
			{
				dist[next] = dist[node] + cost + penalty[last_type[node]][type];
				last_type[next] = type;
				heap.push(next);
			}
		}
	}

	return dist.back() == inf ? -1 : dist.back();
}

int main()
{
	ios_base::sync_with_stdio(false);

	auto input = ifstream("p3.in");
	auto output = ofstream("p3.out");

	int N, M, T; input >> N >> M >> T;
	auto graph = graph_t(N + 1);
	auto penalty = matrix_t(T + 1, vector_t(T + 1));

	int x, y, t;
	long_t c;

	while (M--)
	{
		input >> x >> y >> c >> t;
		graph[x].emplace_back(y, c, t);
		graph[y].emplace_back(x, c, t);
	}

	for (auto i = 1; i <= T; ++i)
		for (auto j = 1; j <= T; ++j)
			input >> penalty[i][j];

	output << dijkstra(graph, penalty) << endl;
}
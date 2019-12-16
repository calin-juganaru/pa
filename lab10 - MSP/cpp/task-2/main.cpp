#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <tuple>

using namespace std;
using pair_t = pair<int, int>;
using vector_t = vector<pair_t>;

constexpr static auto inf = 0x3f3f3f3f;

class Task
{
 public:
	void solve()
	{
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<vector_t> adj;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;
		adj.resize(n + 1);

		for (int i = 1, x, y, w; i <= m; i++)
		{
			fin >> x >> y >> w;
			adj[x].push_back({y, w});
			adj[y].push_back({x, w});
		}

		fin.close();
	}

	int get_result()
	{
		auto total_cost = 0;
		auto visited = vector<bool>(n + 1);
		auto min_dist = vector<int>(n + 1, inf);
		auto heap = priority_queue<pair_t, vector_t, greater<pair_t>>();

		min_dist[1] = 0;
	    heap.push({0, 1});

		while (!heap.empty())
		{
			auto [dist, node] = heap.top(); heap.pop();

			if (!visited[node])
			{
				visited[node] = true;
				total_cost += dist;

				for (auto&& [son, cost]: adj[node])
					if (cost < min_dist[son])
					{
						heap.push({cost, son});
						min_dist[son] = cost;
					}
			}
		}

		return total_cost;
	}

	void print_output(int result)
	{
		ofstream fout("out");
		fout << result << "\n";
		fout.close();
	}
};

int main()
{
	Task *task = new Task();
	task->solve();
	delete task;
}

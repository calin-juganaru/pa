#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Task
{
 public:
	void solve()
	{
		read_input();
		print_output(get_result());
	}

 private:
	int n, m, source;
	vector<vector<pair<int, int>>> adj;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m >> source;
		adj.resize(n + 1);
		for (int i = 1, x, y, w; i <= m; ++i)
		{
			fin >> x >> y >> w;
			adj[x].push_back({y, w});
		}
		fin.close();
	}

	vector<int> get_result()
	{
		auto dist = vector<int>(n + 1, -1);
		auto visited = vector<bool>(n + 1);

		auto comp = [&](const int& x, const int& y)
		{
			return dist[x] > dist[y];
		};

		priority_queue<int, vector<int>,
						decltype(comp)> heap(comp);
		dist[source] = 0;
		heap.push(source);

		while (!heap.empty())
		{
			auto node = heap.top();	heap.pop();
			if (visited[node])
				continue;

			visited[node] = true;
			for (auto&& [next, cost]: adj[node])
				if (dist[next] == -1 || dist[next] > dist[node] + cost)
				{
					dist[next] = dist[node] + cost;
					heap.push(next);
				}
		}

		return dist;
	}

	void print_output(vector<int> result)
	{
		ofstream fout("out");
		for (int i = 1; i <= n; i++)
		{
			fout << result[i] << " ";
		}
		fout << "\n";
		fout.close();
	}
};

int main()
{
	Task *task = new Task();
	task->solve();
	delete task;
}

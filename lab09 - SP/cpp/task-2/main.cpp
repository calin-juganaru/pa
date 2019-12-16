#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

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
		for (int i = 1, x, y, w; i <= m; i++)
		{
			fin >> x >> y >> w;
			adj[x].push_back({y, w});
		}
		fin.close();
	}

	vector<int> get_result()
	{
		auto dist = vector<int>(n + 1, -1);
		auto visited = vector<int>(n + 1);
		auto q = queue<int>();

		dist[source] = 0;
		q.push(source);

		while (!q.empty())
		{
			auto node = q.front(); q.pop();
			visited[node]++;

			if (visited[node] == n)
				return vector<int>();

			for (auto&& [next, cost]: adj[node])
				if (dist[next] == -1 || dist[next] > dist[node] + cost)
				{
					dist[next] = dist[node] + cost;
					q.push(next);
				}
		}

		return dist;
	}

	void print_output(vector<int> result)
	{
		ofstream fout("out");
		if (result.size() == 0)
		{
			fout << "Ciclu negativ!\n";
		}
		else
		{
			for (int i = 1; i <= n; i++)
				fout << result[i] << ' ';
			fout << '\n';
		}
		fout.close();
	}
};

int main()
{
	Task *task = new Task();
	task->solve();
	delete task;
}

#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;
using matrix_t = vector<vector<int>>;

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
	matrix_t adj, cap;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;

		adj.resize(n + 1);
		cap = matrix_t(n + 1, vector<int>(n + 1));

		for (int i = 1, x, y, z; i <= m; ++i)
		{
			fin >> x >> y >> z;
			adj[x].push_back(y);
			adj[y].push_back(x);
			cap[x][y] += z;
		}

		fin.close();
	}

	bool bfs(vector<bool>& visited, matrix_t& flow, vector<int>& parent)
	{
		visited = vector<bool>(n + 1);
		auto q = queue<int>();
		q.push(1); visited[1] = true;

		while (!q.empty())
		{
			auto node = q.front(); q.pop();

			if (node != n)
				for (auto&& next: adj[node])
					if (!visited[next] && flow[node][next] != cap[node][next])
					{
						q.push(next);
						visited[next] = true;
						parent[next] = node;
					}
		}

		return visited.back();
	}

	int get_result()
	{
		auto max_flow = 0;
		auto visited = vector<bool>();
		auto parent = vector<int>(n + 1);
		auto flow = matrix_t(n + 1, vector<int>(n + 1));

		while (bfs(visited, flow, parent))
			for (auto&& next: adj[n])
			{
				if (flow[next][n] == cap[next][n]
					|| !visited[next]) continue;
				parent[n] = next;

				auto incr = 0x3f3f3f3f;
				for (auto node = n; node != 1; node = parent[node])
				{
					incr = min(incr, ( cap[ parent[node] ][node] -
									  flow[ parent[node] ][node] ) );
				}

				for (auto node = n; node != 1 && incr; node = parent[node])
				{
					flow[ parent[node] ][node] += incr;
					flow[node][ parent[node] ] -= incr;
				}

				max_flow += incr;
			}

		return max_flow;
	}

	void print_output(int result)
	{
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main()
{
	Task *task = new Task();
	task->solve();
	delete task;
}

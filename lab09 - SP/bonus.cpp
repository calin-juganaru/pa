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
		ifstream fin("bonus.in");
		fin >> n >> m >> source;
		adj.resize(n + 1);
		for (int i = 1, x, y, w; i <= m; ++i)
		{
			fin >> x >> y >> w;
			adj[x].push_back({y, w});
		}
		fin.close();
	}

	pair<vector<int>, vector<int>> get_result()
	{
		auto dist = vector<int>(n + 1, -1);
		auto prev = vector<int>(n + 1, 0);

		auto comp = [&](const int& x, const int& y)
		{
			return dist[x] > dist[y];
		};

		priority_queue<int, vector<int>,
						decltype(comp)> heap(comp);
		dist[source] = 0;
		heap.push(source);

		while(!heap.empty())
		{
			auto node = heap.top();
			heap.pop();

			for (auto&& [next, cost]: adj[node])
				if (dist[next] == -1 || dist[next] > dist[node] + cost)
				{
					dist[next] = dist[node] + cost;
					prev[next] = node;
					heap.push(next);
				}
		}

		return {dist, prev};
	}

	void print_aux(const int& node, vector<int>& prev, ostream& fout)
	{
		if (auto next = prev[node]; next)
		{
			fout << next << ' ';
			print_aux(next, prev, fout);
		}
	}

	void print_output(pair<vector<int>, vector<int>> result)
	{
		ofstream fout("bonus.out");
		for (int i = 1; i <= n; i++)
		{
			fout << i << ' ' << result.first[i] << " --- ";
			print_aux(i, result.second, fout);
			fout << endl;
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

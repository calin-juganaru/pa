#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

namespace std
{
	template <> struct hash<pair<int, int>>
	{
    	inline size_t operator()(const pair<int, int> &p) const
		{
        	return hash<int>()(p.first) + hash<int>()(p.second);
    	}
	};
}

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
	vector<vector<int>> adj;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;
		adj.resize(n + 1);
		for (int i = 1, x, y; i <= m; i++)
		{
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	void dfs(const int& node, const int& parent,
			 vector<int>& depth, vector<int>& low_point,
			 unordered_set<pair<int, int>>& cut_edges)
	{
		static auto TIME = 0;
		depth[node] = low_point[node] = ++TIME;

		for (auto&& son: adj[node])
			if (son != parent)
			{
				if (!depth[son])
				{
					dfs(son, node, depth, low_point, cut_edges);
					low_point[node] = min(low_point[node], low_point[son]);

					if (low_point[son] > depth[node])
					{
						cut_edges.insert({node, son});
					}
				}
				else
				{
					low_point[node] = min(low_point[node], depth[son]);
				}
			}
	}

	vector<pair<int, int>> get_result()
	{
		auto cut_edges = unordered_set<pair<int, int>>();
		auto depth = vector<int>(n + 1), low_point = depth;
		dfs(1, 0, depth, low_point, cut_edges);
		return vector(begin(cut_edges), end(cut_edges));
	}

	void print_output(vector<pair<int, int>> result)
	{
		ofstream fout("out");
		fout << result.size() << '\n';
		for (auto&& [i, j]: result)
			fout << i << ' ' << j << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}

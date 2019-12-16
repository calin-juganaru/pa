#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_set>

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
			 unordered_set<int>& cut_vertices)
	{
		static auto TIME = 0;

		depth[node] = ++TIME;
		low_point[node] = depth[node];

		auto children = 0;

		for(auto&& son: adj[node])
		{
			if(!depth[son])
			{
				++children;
				dfs(son, node, depth, low_point, cut_vertices);
				low_point[node] = min(low_point[node], low_point[son]);

				if(parent && low_point[son] >= depth[node])
				{
					cut_vertices.insert(node);
				}

				if (!parent && children > 1)
                {
					cut_vertices.insert(node);
				}
			}
			else
			{
				low_point[node] = min(low_point[node], depth[son]);
			}
		}
	}

	vector<int> get_result()
	{
		auto cut_vertices = unordered_set<int>();
		auto depth = vector<int>(n + 1), low_point = depth;
		dfs(1, 0, depth, low_point, cut_vertices);
		return vector(begin(cut_vertices), end(cut_vertices));
	}

	void print_output(vector<int> result)
	{
		ofstream fout("out");
		for (auto&& it: result)
			fout << it << ' ';
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}

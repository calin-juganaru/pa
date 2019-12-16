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
	int n, m;
	vector<vector<int>> adj, adjt;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;

        adj.resize(n + 1);
        adjt.resize(n + 1);

		for (int i = 1, x, y; i <= m; i++)
		{
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		fin.close();
	}

	void dfs(const int& node, vector<bool>& visited, deque<int>& topo)
	{
		visited[node] = true;
		for(auto&& other: adj[node])
			if(!visited[other])
                dfs(other, visited, topo);
		topo.push_front(node);
	}

	void dfst(const int& node, vector<bool>& not_visited,
			  vector<vector<int>>& ctc)
	{
		not_visited[node] = false;
		ctc.back().push_back(node);
		for(auto&& other: adjt[node])
			if(not_visited[other])
                dfst(other, not_visited, ctc);
	}

	vector<vector<int>> get_result()
	{
		auto ctc = vector<vector<int>>();
        auto visited = vector<bool>(n + 1);
        auto topo = deque<int>();

		for(auto node = 1; node <= n; ++node)
			if(!visited[node])
                dfs(node, visited, topo);

		for(auto&& node: topo)
			if(visited[node])
			{
				ctc.push_back(vector<int>());
                dfst(node, visited, ctc);
			}

		return ctc;
	}

	void print_output(vector<vector<int>> result)
	{
		ofstream fout("out");
		fout << result.size() << '\n';
		for (auto&& ctc: result)
		{
			for (auto&& node: ctc)
				fout << node << ' ';
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
	return 0;
}

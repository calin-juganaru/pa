#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#include <numeric>
#include <tuple>

using namespace std;
using edge_t = tuple<int, int, int>;

class disjoint_set
{
private:
	vector<int> group;

public:
	disjoint_set(int n)
	{
		group.resize(n + 1);
		iota(begin(group), end(group), 0);
	}

	int find(int node)
	{
        //return node == group[node] ? node : group[node] = find(group[node]);

		if (group[node] != node)
			group[node] = find(group[node]);
		return group[node];
	}

	void merge(int x, int y)
	{
		group[find(y)] = find(x);
	}
};

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
	priority_queue<edge_t, vector<edge_t>, greater<edge_t>> heap;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;

		for (int i = 1, x, y, w; i <= m; i++)
		{
			fin >> x >> y >> w;
			heap.emplace(w, x, y);
		}

		fin.close();
	}

	int get_result()
	{
		auto cost = 0, edges = 0;
		auto dsu = disjoint_set(n);

		while (!heap.empty() && edges < n)
		{
			auto [c, x, y] = heap.top(); heap.pop();

			if (dsu.find(x) != dsu.find(y))
			{
				dsu.merge(x, y);
				cost += c;
				++edges;
			}
		}

		return cost;
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

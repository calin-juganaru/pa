#include <fstream>
#include <vector>

using namespace std;

class Task
{
 public:
	void solve()
	{
		read_input();
		compute();
		print_output();
	}

 private:
	int n;
	vector<vector<int>> edge, dist;

	void read_input()
	{
		ifstream fin("in");
		fin >> n;
		edge.assign(n + 1, vector<int>(n + 1));
		dist.assign(n + 1, vector<int>(n + 1));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
			{
				fin >> edge[i][j];
				dist[i][j] = edge[i][j];
			}
		fin.close();
	}

	void compute()
	{
		for (auto k = 1; k <= n; ++k)
			for (auto i = 1; i <= n; ++i)
				for (auto j = 1; j <= n; ++j)
					if (i != j && dist[i][k] && dist[k][j])
						if (dist[i][j] > dist[i][k] + dist[k][j] || !dist[i][j])
							dist[i][j] = dist[i][k] + dist[k][j];
	}

	void print_output()
	{
		ofstream fout("out");
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
				fout << dist[i][j] << ' ';
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

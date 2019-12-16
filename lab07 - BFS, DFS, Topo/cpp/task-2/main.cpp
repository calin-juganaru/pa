#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}

    void dfs(const int& node, vector<bool>& visited, deque<int>& topo)
    {
        visited[node] = true;
        for (auto&& next: adj[node])
            if (!visited[next])
                dfs(next, visited, topo);
        topo.emplace_front(node);
    }

	vector<int> get_result()
    {
		auto visited = vector<bool>(n + 1);
        auto topo = deque<int>();

        for (auto node = 1; node <= n; ++node)
            if (!visited[node])
                dfs(node, visited, topo);

        return vector(begin(topo), end(topo));
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
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

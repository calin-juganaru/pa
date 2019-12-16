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
	int source;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result()
    {
		auto dist = vector<int>(n + 1, -1);
        auto q = queue<int>();
        dist[source] = 0;
        q.push(source);

        while (!q.empty())
        {
            auto node = q.front(); q.pop();

            for (auto&& other: adj[node])
            {
                if (dist[other] < 0)
                {
                    q.push(other);
                    dist[other] = dist[node] + 1;
                }
            }
        }

		return dist;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}

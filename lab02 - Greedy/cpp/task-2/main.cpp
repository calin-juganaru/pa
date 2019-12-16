#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> dist;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> m;
		dist.push_back(0);
		for (int i = 0, d; i < n; i++) {
			fin >> d;
			dist.push_back(d);
		}
		
		fin.close();
	}

	int get_result()
	{
		auto rez = m, sol = 0;
		auto stop = n + 1;
		for (auto i = 0; i < stop; ++i)
		{
			auto d = dist[i + 1] - dist[i];
			if (d > rez)
			{
				++sol;
				rez = m;
			}
			rez -= d;
		}

		return sol;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	void submultimi(const int& N, const int& K,
					 vector<vector<int>>& solutie, vector<int>& aux)
	{
		if (K <= N)
			for (auto i = 1 + (aux.empty() ? 0 : aux.back()); i <= N; ++i)
			{
				aux.push_back(i);
				
				solutie.push_back(aux);

				submultimi(N, K + 1, solutie, aux);
				aux.pop_back();
			}
		else return;
	}

	vector<vector<int>> get_result()
	{
		auto sol = vector<vector<int>>();
		auto aux = vector<int>();
		
		sol.push_back(vector<int>());
		submultimi(n, 1, sol, aux);

		return sol;
	}

	void print_output(vector<vector<int> > result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < (int)result.size(); i++) {
			for (int j = 0; j < (int)result[i].size(); j++) {
				fout << result[i][j] <<
					(j + 1 != result[i].size() ? ' ' : '\n');
			}
		}
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}

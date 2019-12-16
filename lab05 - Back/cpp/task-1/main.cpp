#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using vect = vector<int>;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, k;

	void read_input() {
		ifstream fin("in");
		fin >> n >> k;
		fin.close();
	}

	void aranjamente(const int& N, const int& K, const int& elem,
					 vector<vector<int>>& solutie, 
					 vector<int>& aux, vector<bool>& folosit)
	{
		if (elem == K) 
			solutie.push_back(aux);
		else
			for (auto i = 1; i <= N; ++i)
				if (!folosit[i])
				{
					aux[elem] = i;
					folosit[i] = true;
					aranjamente(N, K, elem + 1,
								solutie, aux, folosit);
					folosit[i] = false;
				}
	}

	vector<vector<int>> get_result()
	{
		auto sol = vector<vect>();
		auto aux = vector<int>(k);
		auto fol = vector<bool>(n + 1);

		aranjamente(n, k, 0, sol, aux, fol);

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

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using vect = vector<int>;
using matr = vector<vect>;

struct Result
{
	int len;
	vector<int> subsequence;
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> v;
	vector<int> w;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;

		v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}

		w.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= m; i++) {
			fin >> e;
			w.push_back(e);
		}

		fin.close();
	}
		
	void back(const int& i, const int& j, const matr& sol, vect& r)
	{
    	if(i && j)
    	{
        	if (v[i] == w[j])
        	{
            	back(i - 1, j - 1, sol, r);
            	r.push_back(v[i]);
        	}
        	else
        	{
            	if (sol[i - 1][j] > sol[i][j - 1])
                	 back(i - 1, j, sol, r);
            	else back(i, j - 1, sol, r);
        	}
    	}
	}

	Result get_result()
	{
		auto result = Result();

		auto sol = matr(n + 1, vect(m + 1, 0));
		for (auto i = 1; i <= n; ++i)		
			for (auto j = 1; j <= m; ++j)
			{
				if (v[i] == w[j])
					 sol[i][j] = sol[i - 1][j - 1] + 1;
				else sol[i][j] = max(sol[i][j - 1], sol[i - 1][j]);
			}
		
		result.len = sol[n][m];
		back(n, m, sol, result.subsequence);

		return result;
	}

	void print_output(Result result)
	{
		ofstream fout("out");
		fout << result.len << '\n';
		for (int x : result.subsequence)
			fout << x << ' ';
		fout << '\n';
		fout.close();
	}
};

int main()
{
	Task task;
	task.solve();
	return 0;
}

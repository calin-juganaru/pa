#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, S;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n >> S;
		for (int i = 1, e; i <= n; i++)
		{
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result()
	{
		auto max = S + 1;  
        auto sol = vector<int>(max, max);  
        sol[0] = 0;   
        
		for (auto i = 1; i <= S; ++i)
            for (auto&& it: v)
                if (it <= i)
                    sol[i] = min(sol[i], sol[i - it] + 1);

        return sol[S] > S ? -1 : sol[S];
	}

	void print_output(int result)
	{
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

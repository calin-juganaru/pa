#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int mod = 1e9 + 7;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		//v.push_back(-1); // adaugare element fictiv - indexare de la 1
		for (int i = 1, e; i <= n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin.close();
	}

	int get_result()
	{
		auto par = 1, impar = 0;

		for (auto&& it: v)
		{
			if (it % 2)
			{
				par = impar = par + impar;
			}
			else
			{
				par *= 2;
				impar *= 2;
			}

			par %= mod;
			impar %= mod;
		}

		return par - 1;
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

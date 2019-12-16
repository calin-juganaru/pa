#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

constexpr int mod = 1e9 + 7;
using vect = vector<decltype(0ull)>;

class Task
{
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	string expr;

	void read_input() {
		ifstream fin("in");
		fin >> n >> expr;
		fin.close();
	}

	int get_result()
	{
		auto T = vector<vect>(n, vect(n)), F = T;

		for (auto i = 0; i < n; i += 2)
			if (expr[i] == 'T')
				 T[i][i] = 1;
			else F[i][i] = 1;

		for (auto k = 1; k <= n / 2; ++k)
		{
			for (auto i = 0; i < n; i += 2)
			{
				auto j = i + 2 * k;
				if (j > n) break;

				for (auto l = i + 1; l < j; l += 2)
				{
					switch (expr[l])
					{
						case '&':
							T[i][j] += (T[i][l - 1] * T[l + 1][j]) % mod;
							F[i][j] += (F[i][l - 1] * T[l + 1][j]) % mod
									 + (T[i][l - 1] * F[l + 1][j]) % mod
									 + (F[i][l - 1] * F[l + 1][j]) % mod;
							break;
						case '|':
							T[i][j] += (T[i][l - 1] * T[l + 1][j]) % mod
									 + (T[i][l - 1] * F[l + 1][j]) % mod
									 + (F[i][l - 1] * T[l + 1][j]) % mod;
							F[i][j] += (F[i][l - 1] * F[l + 1][j]) % mod;
							break;
						case '^':
							T[i][j] += (T[i][l - 1] * F[l + 1][j]) % mod
									 + (F[i][l - 1] * T[l + 1][j]) % mod;
							F[i][j] += (T[i][l - 1] * T[l + 1][j]) % mod
									 + (F[i][l - 1] * F[l + 1][j]) % mod;
							break;
						default:
							break;
					}
					T[i][j] %= mod;
					F[i][j] %= mod;
				}
			}
		}

		return T.front().back();
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result << '\n';
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}

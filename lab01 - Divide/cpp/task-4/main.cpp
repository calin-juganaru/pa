#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(fast_pow(base, exponent, mod));
	}

private:
	int base, exponent, mod;

	void read_input() {
		ifstream fin("in");
		fin >> base >> exponent >> mod;
		fin.close();
	}

	int fast_pow(int base, int exp, int mod) {
		if (!exp)
			return 1;

		auto aux = 1ll * fast_pow(base, exp >> 1, mod);
		aux = (aux * aux) % mod;

		if (exp & 1)
		{
			 aux *= base;
			 return aux % mod;
		}
		else return aux;
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

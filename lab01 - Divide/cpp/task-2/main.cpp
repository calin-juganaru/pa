#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(compute_sqrt());
	}

private:
	double n;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		fin.close();
	}

	double compute_sqrt()
	{
		auto subunit = false;
		if (n < 1.0)
		{
			n = 1 / n;
			subunit = true;
		}

		auto rad = 0.0;
		auto st = rad;
		auto dr = n;
		auto eps = 0.0001;
		
		while (fabs(dr - st) > eps)
		{
			auto mij = (st + dr) / 2;
			rad = mij;
			if (mij * mij + eps > n)
				 dr = mij;
			else st = mij;
		}

		if (subunit)
		{
			n = 1 / n;
			rad = 1 / rad;
		}

		return rad;
	}

	void print_output(double result) {
		ofstream fout("out");
		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}

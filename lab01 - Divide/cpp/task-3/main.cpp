#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve()
	{
		read_input();
		print_output(get_result(1 << n, x, y));
	}

private:
	int n, x, y;

	void read_input() {
		ifstream fin("in");
		fin >> n >> x >> y;
		fin.close();
	}

	int get_result(int n, int x, int y)
	{
		if (n == 1)
			return 1;
		
		auto rez = 0;
		n >>= 1;

		if (x > n)
		{
			x -= n;
			rez += n * n * 2;
		}

		if (y > n)
		{
			y -= n;
			rez += n * n;
		}

		return rez + get_result(n, x, y);
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

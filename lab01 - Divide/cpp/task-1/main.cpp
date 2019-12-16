#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result());
	}

private:
	int n, x;
	vector<int> v;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, e; i < n; i++) {
			fin >> e;
			v.push_back(e);
		}
		fin >> x;
		fin.close();
	}

	int find_first()
	{
		auto poz = 0;
		for (auto&& it: v)
		{
			if (it == x)
				return poz; 
			++poz;
		}
		return -1;
	}

	int find_last()
	{
		for (auto poz = v.size(); poz > 0; --poz)
		{
			if (v[poz - 1] == x)
				return poz - 1;
		}
		return -1;
	}

	int get_result()
	{
		auto aux = 0;
		for (auto&& it: v)
			if (it == x)
				++aux;
		return aux;
	}

	void print_output(int result)
	{
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main()
{
	Task task;
	task.solve();
	return 0;
}

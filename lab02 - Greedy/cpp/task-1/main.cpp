#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Object
{
	double weight;
	double price;

	Object(double _weight, double _price):
		weight(_weight), price(_price) {}

	bool operator>(const Object& o) const
	{
		return (this->price / this->weight) > (o.price / o.weight);
	}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, w;
	vector<Object> objs;

	void read_input()
	{
		ifstream fin("in");
		fin >> n >> w;
		double weight, price;
		for (int i = 0; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result()
	{
		auto rez = 0.0;
		auto w = this->w;
		sort(begin(objs), end(objs), greater<Object>());
		for (auto&& it: objs)
		{
			if (w < it.weight)
			{
				rez += it.price * w / it.weight;
				break;
			}
			rez += it.price;
			w -= it.weight;
		}

		return rez;
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
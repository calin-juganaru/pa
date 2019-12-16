#include <fstream>
#include <deque>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score):
		deadline(_deadline), score(_score) {}

	bool operator<(const Homework& o) const
	{
		if (this->deadline == o.deadline)
		{
			return this->score > o.score;
		}
		return this->deadline > o.deadline;
	}
};

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	deque<Homework> hws;

	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.push_back(Homework(deadline, score));
		}
		fin.close();
	}

	int get_result()
	{
		sort(begin(hws), end(hws));
		auto aux = 0, scor = 0;
		
		/*
		for (auto&& it: hws)
		{
			cout << it.deadline << ' ' << it.score << endl;
			if (it.deadline >= aux)
			{
				++aux;
				scor += it.score;
			}
		}
		*/

		auto comp = [&](const Homework& x, const Homework& y)
		{
			return x.score < y.score;
		};

		auto heap = priority_queue<Homework, deque<Homework>, decltype(comp)>(comp);

		for (auto sapt = hws.front().deadline; sapt > 0; --sapt)
		{
			while (!hws.empty() && hws.front().deadline == sapt)
			{
				heap.push(hws.front());
				hws.pop_front();
			}
			cout << heap.top().score << ' ' <<  heap.top().deadline << endl;
			scor += heap.top().score;
			heap.pop();
		}

		return scor;
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
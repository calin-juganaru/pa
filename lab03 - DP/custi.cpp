#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
	
using namespace std;
using bits = vector<bool>;
using vect = vector<int>;

template <typename T>
auto min(T&& x, T&& y, T&& z)
{
    return min(forward<T>(x),
           min(forward<T>(y), forward<T>(z)));
}

template <typename T>
auto max(T&& x, T&& y, T&& z)
{
    return max(forward<T>(x),
           max(forward<T>(y), forward<T>(z)));
}

int main()
{
	ifstream fin("custi.in");
    ofstream fout("custi.out");

    int n; fin >> n; ++n;
	auto m = vector<bits>(n, bits(n, 0));
    auto sol = vector<vect>(n, vect(n, 0));
    auto nr = deque<int>(n, 0);

    for (auto i = 1; i < n; ++i)
        for (auto j = 1; j < n; ++j)
        {
            bool aux;
            fin >> aux;
            m[i][j] = aux;
	
            if (m[i][j])
            {
                sol[i][j] = 1 + min(sol[i][j - 1],
                                    sol[i - 1][j],
                                    sol[i - 1][j - 1]);

                for (auto k = sol[i][j]; k; --k)
                    ++nr[k];
            }
        }
	
	nr.pop_front();
    for (auto&& it: nr)
        fout << it << endl;	
}
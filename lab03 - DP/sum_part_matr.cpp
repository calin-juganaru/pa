#include <fstream>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

using vect = vector<int>;
using matr = vector<vect>;

auto precalc = [&](auto&& matrice)
{
    auto n = matrice.size();
    auto m = matrice.front().size();
    auto sum = matr(n + 1, vect(m + 1));

    for(auto i = 0; i < n; ++i)
        partial_sum(begin(matrice[i]),
                      end(matrice[i]),
                    begin(sum[i + 1]) + 1);

    for(auto i = 1; i <= n; ++i)
        for(auto j = 0; j <= m; ++j)
            sum[i][j] += sum[i - 1][j];

    return sum;
};

auto suma = [&](matr& matrice, int i1, int j1, int i2, int j2)
{
    static auto sum = precalc(matrice);

    return sum[i2 + 1][j2 + 1] + sum[i1][j1]
         - sum[i2 + 1][j1] - sum[i1][j2 + 1];
};

int main()
{
    ifstream fin("sume.in");
    ofstream fout("sume.out");

    int n, m; fin >> n >> m;
    auto matrice = matr(n, vect(m));
    for (auto&& linie: matrice)
        for (auto&& elem: linie)
            fin >> elem;
    
    fout << suma(matrice, 1, 2, 3, 4) << endl;
}
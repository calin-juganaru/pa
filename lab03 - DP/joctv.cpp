#include <fstream>
#include <vector>

using namespace std;
using vect = vector<int>;
using matr = vector<vect>;

auto subsir_suma_max = [](auto&& sir)
{
    auto suma = 0, sol = 0;

    for (auto& it: sir)
    {
        suma += it;
        
        if(suma > sol)
            sol = suma;
        
        if(suma < 0)
            suma = 0;
    }

    return sol;
};

auto suma_max_2D = [&](auto&& matrice)
{
    auto sol = 0, n = matrice.size();

    for (auto i = 0; i < n; ++i)
    {
        auto aux = vect(n);
        for (auto j = i; j < n; ++j)
        {
            for (auto k = 0; k < n; ++k)
                aux[k] += matrice[j][k];
            auto ssm = subsir_suma_max(aux);

            if(ssm > sol)
                sol = ssm;
        }
    }

    return sol;
};

int main()
{
    ifstream fin("joctv.in");
    ofstream fout("joctv.out");

    int n; fin >> n;
    auto matrice = matr(n, vect(n));

    for (auto&& linie: matrice)
        for (auto&& elem: linie)
            fin >> elem;
    
    fout << suma_max_2D(matrice) << endl;
}
#include <fstream>
#include <vector>
#include <numeric>

using namespace std;

using vector_t = vector<long long>;

int main()
{
    auto input  = ifstream("p3.in");
    auto output = ofstream("p3.out");

    int N; input >> N;

    auto v = vector_t(N);
    for (auto&& it: v)
    {
        input >> it;
    }

    // suma tuturor numerelor din șirul citit
    auto total_sum = accumulate(begin(v), end(v), 0);
    // matricea folosită la recurență
    auto max_sum = vector<vector_t>(4, vector_t(N));

    // iterăm întâi după dimensiunea intervalului,
    //  adică întâi pe bucăți mici, pe care le vom
    //  folosi apoi la calculul pe bucăți mai mari
    for (auto length = 1; length <= N; ++length)
    {
		// deplasăm la fiecare pas intervalul
        //  cu câte o poziție la dreapta
        for (auto i = 0, j = length - 1; j < N; ++i, ++j)
        {
		    // și aplicăm recurența explicată în README (liniile 64 -- 75)
            max_sum[i % 3][j] = max(v[i] + min(max_sum[(i + 2) % 3][j], max_sum[(i + 1) % 3][j - 1]),
                                    v[j] + min(max_sum[(i + 1) % 3][j - 1], max_sum[i % 3][j - 2]));
		}
	}

    // deducem soluția din suma totală și suma maximă obținută de Tuzgu
    output << 2 * max_sum.front().back() - total_sum << endl;

    input.close();
    output.close();
}

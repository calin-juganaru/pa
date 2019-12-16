#include <fstream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;
using vector_t = vector<int>;

int main()
{
    auto input  = ifstream("p2.in");
    auto output = ofstream("p2.out");

    int N, K;
    input >> N >> K;

    if (N > K)
    {
        auto v = vector_t(N);
        for (auto&& it: v)
        {
            input >> it;
        }

        // sortăm întâi șirul citit descrescător
        sort(begin(v), end(v), greater<int>());
        // și creăm o matrice pentru dinamică
        auto score = vector<vector_t>(2, vector_t(N));

        for (auto i = 0; i < N; ++i)
        {
            // primul caz nu este necesar de calculat,
            //  dar al doilea da (README, linia 24)
            score[1][i] = v.front() - v[i];
        }

        // pentru restul cazurilor aplicăm recurența
        for (auto i = 2; i < N - K; ++i)
        {
            for (auto j = 0; j < i; ++j)
            {
                score[i % 2][j] = 0;
            }

            for (auto j = i; j < N; ++j)
            {
                // variabilă auxiliară care înmulțește
                //  elementul curent cu + sau -1,
                //  în funcție de paritatea indicelui,
                //  pentru simplificarea codului
                auto aux = v[j] * ((i % 2) ? -1 : 1);
                score[i % 2][j] = max(score[i % 2][j - 1],
                                      score[(i - 1) % 2][j - 1] + aux);
            }
        }

        // soluția se va afla pe ultima coloană,
        //  de pe ultima linie calculată
        output << score[(N - K + 1) % 2].back() << endl;
    }
    else
    {
        // când N <= K, nu există soluție
        output << "0\n";
    }

    input.close();
    output.close();
}

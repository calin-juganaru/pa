#include <fstream>
#include <array>
#include <numeric>

using namespace std;
using long_t  = long long;
using clref_t = const long_t&;

// numărul cu care facem toate operațiile %
constexpr static auto mod = 1'000'000'007ll;

// funcție de înmulțire % mod
auto mul = [&](auto&& x, auto&& y)
{
    return (x * y) % mod;
};

// funcție de ridicare la putere,
//  în timp logaritmic, % mod
auto power(clref_t base, long_t exp)
{
    auto result = 1ll;
    for (auto aux = base; exp; exp >>= 1)
    {
        if (exp % 2)
        {
            result = mul(result, aux);
        }
        aux = mul(aux, aux);
    }
    return result;
}

// funcție de calculare a factorialului % mod
auto factorial(long_t N)
{
    auto result = 1ll;
    while (N > 0)
    {
        for (auto i = 2ll; i <= N; ++i)
        {
            result = mul(result, i);
        }
        N /= mod;
    }
    return result;
}

// funcție folosită pentru
//  lizibilitatea codului
auto euler = [&](auto&& N)
{
    return power(N, mod - 2);
};

// funcție pentru calcularea combinărilor % mod,
//  cu ajutorul teoremei inversului modular (Euler)
auto combs = [&](auto&& N, auto&& K)
{
    if (N < K || K < 0)
    {
        return 0ll;
    }
    return mul(factorial(N), mul(euler(factorial(K)),
                                 euler(factorial(N - K))));
};

int main()
{
    auto input  = ifstream("p4.in");
    auto output = ofstream("p4.out");

    long_t N, K, V;
    input >> N >> K >> V;

    // cele 4 cazuri de așezare
    //  a spațiilor și intervalelor
    auto cases = array<long_t, 4>();

    if (N % 2 == 0) // cazul cu N par
    {
        // numărul de intervale
        auto M = N / 2;
        // numărul de spații
        auto L = V - K - 1;

        // numărul de posibilități de
        //  aranjare a intervalelor
        auto ranges = combs(K - 1, M - 1);
        // numărul de posibilități de
        //  aranjare a intervalelor
        auto spaces = combs(L - 1, M - 1);

        cases[0] = mul(ranges, spaces);
        cases[1] = mul(ranges, spaces);

        spaces = combs(L - 1, M - 2);
        cases[2] = mul(ranges, spaces);

        spaces = combs(L - 1, M);
        cases[3] = mul(ranges, spaces);
    }
    else
    {
        // aceleași semnificații
        //  ca la cazul anterior
        auto M = (N + 1) / 2;
        auto L = V - K;

        auto ranges = combs(K - 1, M - 1);
        auto spaces = combs(L - 1, M - 1);
        cases[1] = mul(ranges, spaces);

        spaces = combs(L - 1, M - 2);
        cases[2] = mul(ranges, spaces);
    }

    // soluția este egală cu suma pe cazuri * N!
    auto result = accumulate(begin(cases), end(cases), 0ll);
    output << mul(result, factorial(N)) << endl;

    input.close();
    output.close();
}

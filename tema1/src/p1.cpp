#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    auto input  = ifstream("p1.in");
    auto output = ofstream("p1.out");

    int N; input >> N;

    auto v = vector<int>(N);
    for (auto&& it: v)
    {
        input >> it;
    }
    // sortăm întâi șirul citit
    sort(begin(v), end(v));

    // scorurile celor 2 jucători
    auto score = vector<int>(2);
    // indicele jucătorului curent
    auto player = 0;

    // cât timp nu s-a terminat jocul
    while (!v.empty())
    {
        // jucătorul curent extrage elementul maxim
        score[player] += v.back();
        v.pop_back();
        // apoi trecem la următorul jucător
        player = (player + 1) % 2;
    }

    // soluția este diferența scorurilor celor doi
    output << score.front() - score.back() << endl;

    input.close();
    output.close();
}

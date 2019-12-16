#include <fstream>
#include <iostream>
#include <deque>

using namespace std;

int main()
{
    ifstream fin("test");
    int n;
	fin >> n;
    auto rez = 0, aux = 0;
    auto v = deque<int>();
    while (n--)
    {
        fin >> aux;
        v.push_front(aux);
        for (auto&& it: v)
            if (it > aux)
                ++rez;
    }
    cout << rez << '\n';
	fin.close();    
}
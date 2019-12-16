g++ -Wall -std=c++17 src/p1.cpp -o p1
src/p1.cpp: In function ‘int main()’:
src/p1.cpp:45:21: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<std::pair<int, int> >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
   45 |  for (auto i = 0; i < min_dist.size() - 1; ++i)
      |                   ~~^~~~~~~~~~~~~~~~~~~~~
g++ -Wall -std=c++17 src/p2.cpp -o p2
g++ -Wall -std=c++17 src/p3.cpp -o p3
g++ -Wall -std=c++17 src/p4.cpp -o p4

#include <fstream>
#include <vector>
#include <queue>

using namespace std;

using vector_t = vector<int>;
using matrix_t = vector<vector_t>;

// celulele vecine accesibile celei cu indicii (x, y)
auto offsets = [&](const int& x, const int& y)
{
	return vector{pair{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
};

int lee(const int& N, const int& M,
		 const matrix_t& matrix, matrix_t& visited,
		 const int& i, const int& j, const int& K)
{
	// momentul curent
	static auto TIME = 0;

	auto q = queue<pair<int, int>>();
	// aria zonei găsite
	auto cells = 1;
	// valoarea minimă stabilită
	auto min_elem = matrix[i][j];
	// valoarea maximă stabilită
	auto max_elem = matrix[i][j] + K;

	q.push({i, j});
	// marchez celula vizitată
	//	la momentul curent
	visited[i][j] = ++TIME;

	while (!q.empty())
	{
		auto [x, y] = q.front(); q.pop();

		// pentru fiecare celulă vecină
		for (auto&& [dx, dy]: offsets(x, y))
			// dacă nu depășește marginile matricii
            if (dx >= 0 && dx < N && dy >= 0 && dy < M)
				// dacă nu a mai fost vizitată
                if (visited[dx][dy] != TIME && visited[dx][dy] != -TIME)
					if (matrix[dx][dy] >= min_elem)
					{
						// marchez celula ca vizitată
						visited[dx][dy] = -TIME;

						// dacă valoarea este între limitele stabilite
						if (matrix[dx][dy] <= max_elem)
						{
							++cells;
							q.push({dx, dy});

							if (matrix[dx][dy] == min_elem)
								visited[dx][dy] = TIME;
						}
					}
	}

	return cells;
}

int main()
{
	ios_base::sync_with_stdio(false);

	auto input = ifstream("p2.in");
	auto output = ofstream("p2.out");

	int N, M, K; input >> N >> M >> K;
	auto matrix = matrix_t(N, vector_t(M));
	auto visited = matrix_t(N, vector_t(M));

	for (auto&& line: matrix)
		for (auto&& element: line)
			input >> element;

	auto result = 0;
	for (auto i = 0; i < N; ++i)
		for (auto j = 0; j < M; ++j)
			if (visited[i][j] < 1)
				result = max(result, lee(N, M, matrix, visited, i, j, K));

	output << result << endl;
}
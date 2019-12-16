#include <fstream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

void biconnected(const int& parent, const int& son,
				 stack<pair<int, int>>& vertex_stack,
		 		 vector<unordered_set<int>>& components)
{
    components.push_back(unordered_set<int>());

    while (true)
    {
        auto x = vertex_stack.top().first;
        auto y = vertex_stack.top().second;
        vertex_stack.pop();
        components.back().insert({x, y});

        if (x == parent && y == son) break;
    }
}

void dfs(vector<vector<int>>& graph,
		 const int& node, const int& parent,
		 vector<int>& depth, vector<int>& low_point,
		 stack<pair<int, int>>& vertex_stack,
		 vector<unordered_set<int>>& components)
{
    static auto TIME = 0;

    depth[node] = low_point[node] = ++TIME;

    for(auto&& son: graph[node])
        if (!depth[son])
        {
            vertex_stack.push({node, son});
            dfs(graph, son, node, depth, low_point, vertex_stack, components);

            low_point[node] = min(low_point[node], low_point[son]);

            if (low_point[son] >= depth[node])
			{
				biconnected(node, son, vertex_stack, components);
			}
        }
        else if(son != parent)
        {
            low_point[node] = min(low_point[node], depth[son]);
        }
}

int main()
{
    auto input = ifstream("biconex.in");
    auto output = ofstream("biconex.out");

    int N, M, x, y;	input >> N >> M;

    auto graph = vector<vector<int>>(N + 1);
	auto components = vector<unordered_set<int>>();
	auto vertex_stack = stack<pair<int, int>>();
	auto depth = vector<int>(N + 1), low_point = depth;

    while (M--)
    {
        input >> x >> y;
        graph[x].push_back(y);
		graph[y].push_back(x);
    }

    for (auto&& adj_list: graph)
        adj_list.shrink_to_fit();

    dfs(graph, 1, 0, depth, low_point, vertex_stack, components);

    output << components.size() << endl;

    for (auto&& component: components)
    {
        for (auto&& element: component)
            output << element << ' ';
        output << endl;
    }
}

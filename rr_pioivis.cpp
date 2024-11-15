#include <bits/stdc++.h>
#define int int64_t
using namespace std;

void dfs(int v, vector<vector<int>>& adj, vector<bool>& used) {
    used[v] = true;
    for (int i = 0; i < adj.size(); i++) {
        if (adj[v][i] == 1 && !used[i]) {
            dfs(i, adj, used);
        }
    }
}

bool isConnected(vector<vector<int>>& adj)
{
    int n = adj.size();
    vector<bool> used(n, false);
    dfs(0, adj, used);
    for (bool v : used) {
        if (!v) return false;
    }
    return true;
}

bool check_vertex_set(vector<vector<int>>& graph, vector<int>& vertices)
{
    int n = graph.size();
    vector<vector<int>> temp = graph;

    // Удаляем выбранные вершины из графа
    for (int v : vertices)
    {
        for (int i = 0; i < n; i++)
        {
            temp[v][i] = temp[i][v] = 0;
        }
    }

    // Проверяем, стал ли граф несвязным
    vector<bool> used(n, false);
    int start = -1;

    // Ищем первую неудаленную вершину
    for (int i = 0; i < n; i++) {
        if (find(vertices.begin(), vertices.end(), i) == vertices.end())
        {
            start = i;
            break;
        }
    }

    if (start == -1) return true;

    dfs(start, temp, used);

    // Проверяем, есть ли непосещенные неудаленные вершины
    for (int i = 0; i < n; i++)
    {
        if (!used[i] && find(vertices.begin(), vertices.end(), i) == vertices.end())
        {
            return true;
        }
    }
    return false;
}

void find_vertex_connectivity(vector<vector<int>>& graph)
{
    int n = graph.size();
    int k = 1; // Начинаем с k=1 вершин
    vector<int> result;

    while (k <= n)
    {
        bool found = false;
        vector<int> current;

        // Генерируем все возможные комбинации из k вершин
        function<void(int, int)> generate = [&](int pos, int count)
        {
            if (count == k)
            {
                if (check_vertex_set(graph, current))
                {
                    found = true;
                    result = current;
                }
                return;
            }

            for (int i = pos; i < n && !found; i++)
            {
                current.push_back(i);
                generate(i + 1, count + 1);
                current.pop_back();
            }
        };

        generate(0, 0);

        if (found)
        {
            cout << k << ". Vertices to remove: ";
            for (int v : result)
            {
                cout << v + 1 << " ";
            }
            return;
        }
        k++;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    if (!isConnected(graph))
    {
        cout << "0. The graph is not connected";
    }
    else
    {
        find_vertex_connectivity(graph);
    }

    return 0;
}

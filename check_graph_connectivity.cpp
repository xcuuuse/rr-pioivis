#include <bits/stdc++.h>

#define int int64_t

using namespace std;

void dfs(int v, vector<vector<int>>& adj, vector<bool>& used)
{
    used[v] = true;

    for (int i = 0; i < adj.size(); i++)
    {
        if (adj[v][i] == 1 && !used[i])
        {
            dfs(i, adj, used);
        }
    }
}

bool isConnected(vector<vector<int>>& adj)
{
    int n = adj.size();
    vector<bool> used(n, false);

    dfs(0, adj, used);

    for (bool v : used)
    {
        if (!v) return false;
    }
    return true;
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

    if (isConnected(graph))
    {
        cout << "yes." << endl;
    }
    else
    {
        cout << "no." << endl;
    }

    return 0;
}

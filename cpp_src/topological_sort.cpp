#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXV = 1000;
vector<int> adj[MAXV];
int N, M, indegree[MAXV] = {0};

bool topological_sort()
{
    int cnt = 0;
    queue<int> q;
    for (int i = 0; i < N; i++)
    {
        if (indegree[i] == 0) q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        printf("%d ", u);
        for (auto v: adj[u])
        {
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
        cnt++;
    }
    printf("\n");
    return cnt == N;
}

int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        indegree[v]++;
    }
    topological_sort();
    return 0;
}
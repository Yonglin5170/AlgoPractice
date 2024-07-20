#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 1000;
const int INF = 1e9;
// N, M are the number of vertices and edges, S is the start vertex 
int N, M, S;
int G[MAXV][MAXV], dist[MAXV];
bool visited[MAXV] = {false};
// precursor of the shortest path from S to v
vector<int> pre[MAXV];
// number of the shortest path from S to v
int num[MAXV];
// int weight[MAXV], w[MAXV];

// use Adjacency Matrix as the data structure
void Dijkstra_M(int S)
{
    fill(dist, dist + MAXV, INF);
    dist[S] = 0;
    memset(num, 0, sizeof(num));
    num[S] = 1;
    // loop N times
    for (int i = 0; i < N; i++)
    {
        // find the vertex which has not been visited and has the minimum distance
        int u = -1, MIN = INF;
        for (int j = 0; j < N; j++)
        {
            if (visited[j] == false && dist[j] < MIN)
            {
                MIN = dist[j];
                u = j;
            }
        }
        // not connected
        if (u == -1) return;
        visited[u] = true;
        // update distances
        for (int v = 0; v < N; v++)
        {
            if (visited[v] == false && G[u][v] != INF)
            {
                if (dist[u] + G[u][v] < dist[v])
                {
                    dist[v] = dist[u] + G[u][v];
                    // w[v] = w[u] + weight[v];
                    pre[v].clear();
                    pre[v].push_back(u);
                    num[v] = num[u];
                }
                else if (dist[u] + G[u][v] == dist[v])
                {
                    // if (w[v] < w[u] + weight[v])
                    // {
                    //     w[v] = w[u] + weight[v];
                    // }
                    pre[v].push_back(u);
                    num[v] += num[u];
                }
            }
        }
    }
}

struct node
{
    int v, dist;
};
vector<node> adj[MAXV];
// use Adjacency Lists as the data structure
void Dijkstra_L(int S)
{
    fill(dist, dist + MAXV, INF);
    dist[S] = 0;
    // loop N times
    for (int i = 0; i < N; i++)
    {
        // find the vertex which has not been visited and has the minimum distance
        int u = -1, MIN = INF;
        for (int j = 0; j < N; j++)
        {
            if (visited[j] == false && dist[j] < MIN)
            {
                MIN = dist[j];
                u = j;
            }
        }
        // not connected
        if (u == -1) return;
        visited[u] = true;
        // update distances
        for (int j = 0; j < adj[u].size(); j++)
        {
            int v = adj[u][j].v, d = adj[u][j].dist;
            if (visited[v] == false && dist[u] + d < dist[v])
            {
                dist[v] = dist[u] + d;
            }
        }
    }
}

void DFS(int v, int opt_value, vector<int> &path, vector<int> &temp_path)
{
    if (pre[v].size() == 0)
    {
        temp_path.push_back(v);
        for (int i = temp_path.size() - 1; i >= 0; i--)
        {
            printf("%d", temp_path[i]);
            if (i > 0) printf(" ");
            else printf("\n");
        }
        temp_path.pop_back();
        return;
    }
    temp_path.push_back(v);
    for (int i = 0; i < pre[v].size(); i++)
    {
        DFS(pre[v][i], opt_value, path, temp_path);
    }
    temp_path.pop_back();
}

vector<vector<int>> dist_all(MAXV, vector<int>(MAXV));
void Floyd()
{
    // initialize dist
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dist_all[i][j] = G[i][j];
        }
    }
    // for each intermediate vertex
    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (dist_all[i][k] != INF && dist_all[k][j] != INF && 
                    dist_all[i][k] + dist_all[k][j] < dist_all[i][j])
                {
                    dist_all[i][j] = dist_all[i][k] + dist_all[k][j];
                }
            }
        }
    }
}

int main()
{
    int u, v, d;
    scanf("%d%d%d", &N, &M, &S);
    fill(G[0], G[0] + MAXV * MAXV, INF);
    // Adjacency Matrix
    for (int i = 0; i < M; i++)
    {
        scanf("%d%d%d", &u, &v, &d);
        G[u][v] = d;
    }
    Dijkstra_M(S);
    // Adjacency Lists
    // for (int i = 0; i < M; i++)
    // {
    //     scanf("%d%d%d", &u, &v, &d);
    //     adj[u].push_back({v, d});
    // }
    // Dijkstra_L(S);
    printf("shortest distance from S to i:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d", dist[i]);
        if (i < N - 1) printf(" ");
        else printf("\n");
    }
    int opt_value = 0;
    vector<int> path, temp_path;
    printf("all shortest paths from S to i:\n");
    DFS(5, opt_value, path, temp_path);
    printf("the number of shortest paths from S to 5:\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d", num[i]);
        if (i < N - 1) printf(" ");
        else printf("\n");
    }
    // Floyd();
    // printf("all shortest paths from i to j:\n");
    // for (int i = 0; i < N; i++)
    // {
    //     for (int j = 0; j < N; j++)
    //     {
    //         printf("%10d", dist_all[i][j]);
    //         if (j < N - 1) printf(" ");
    //         else printf("\n");
    //     }
    // }
    return 0;
}
/*
input:
6 8 0
0 1 1
0 3 4
0 4 4
1 3 3
2 5 1
3 2 2
3 4 3
4 5 3
output:
shortest distance from S to i:
0 1 6 4 4 7
all shortest paths from S to i:
0 4 5
0 3 2 5
0 1 3 2 5
the number of shortest paths from S to 5:
1 1 2 2 1 3
*/
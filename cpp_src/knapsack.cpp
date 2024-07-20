#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, V;
    scanf("%d%d", &n, &V);
    vector<int> w(n + 1), c(n + 1);
    // The maximum value that can be obtained by putting the first i items
    // into a knapsack with a capacity of v.
    vector<vector<int>> dp(n + 1, vector<int>(V + 1));
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        for (int v = 1; v <= V; v++)
        {
            if (v < w[i]) dp[i][v] = dp[i - 1][v];
            else
            {
                // 0-1 knapsack:
                dp[i][v] = max(dp[i - 1][v], dp[i - 1][v - w[i]] + c[i]);

                // // unbounded knapsack:
                // dp[i][v] = max(dp[i - 1][v], dp[i][v - w[i]] + c[i]);

                // // bounded knapsack:
                // for (int k = 0; k <= m[i] && k * w[i] <= v; k++)
                // {
                //     dp[i][v] = max(dp[i][v], dp[i - 1][v - w[i] * k] + c[i] * k);
                // }
            }
        }
    }
    printf("%d\n", dp[n][V]);
    return 0;
}
/* input:
5 8
3 5 1 2 2
4 5 2 1 3
output:
10
*/
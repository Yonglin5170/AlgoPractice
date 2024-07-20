#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
    if (n <= 1) return false;
    int sqr = sqrt(1.0 * n);
    for (int i = 2; i <= sqr; i++)
    {
        if (n % i == 0) return false;
    }
    return true;
}

void find_prime(int N, vector<int> &primes, vector<int> &visited)
{
    for (int i = 2; i <= N; i++)
    {
        if (visited[i] == 0)
        {
            primes.push_back(i);
            for (int j = i + i; j <= N; j += i)
            {
                visited[j] = 1;
            }
        }
    }
}

int main()
{
    int N = 1e3;
    vector<int> primes, visited(N + 1);
    find_prime(N, primes, visited);
    for (int i = 0; i < primes.size(); i++)
    {
        printf("%d", primes[i]);
        if (i < primes.size() - 1) printf(" ");
        else printf("\n");
    }
    return 0;
}
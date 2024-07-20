#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

void Init(vector<int> &father)
{
    for (int i = 0; i < father.size(); i++)
    {
        father[i] = i;
    }
}

int Find(vector<int> &father, int x)
{
    if (x == father[x]) return x;
    else return father[x] = Find(father, father[x]);
}

void Union(vector<int> &father, int a, int b)
{
    int fa_a = Find(father, a), fa_b = Find(father, b);
    if (fa_a != fa_b) father[fa_a] = fa_b;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> father(n);
    Init(father);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        Union(father, a, b);
    }
    unordered_set<int> st;
    for(int i = 0; i < n; i++)
    {
        st.insert(Find(father, i));
    }
    printf("%d\n", st.size());
    return 0;
}
/*
input:
7 5
1 2
2 3
3 1
1 4
5 6
output:
3
*/
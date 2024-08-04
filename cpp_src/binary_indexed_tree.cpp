#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

// 树状数组（Binary Indexed Tree，简称 BIT 或 Fenwick Tree ）
// 能高效地实现数组的单点修改和区间求和，复杂度 O(logN)
// 参考 https://zhuanlan.zhihu.com/p/574739597

int lowbit(int i)
{
    return i & -i;
}

void add(vector<int> &BIT, int i, int val)
{
    int n = BIT.size();
    // O(logN)
    while (i < n)
    {
        BIT[i] += val;
        i += lowbit(i);
    }
}

int prefix_sum(vector<int> &BIT, int i)
{
    int psum = 0;
    // O(logN)
    while (i > 0)
    {
        psum += BIT[i];
        i -= lowbit(i);
    }
    return psum;
}

int query(vector<int> &BIT, int i, int j)
{
    // O(logN)
    return prefix_sum(BIT, j) - prefix_sum(BIT, i); // (i, j]
}

int main()
{
    vector<int> nums = {4, 8, 7, 6, 5, 9, 3, 2, 1, 0};
    vector<int> BIT(nums.size() + 1);
    for (int i = 0; i < nums.size(); i++)
    {
        add(BIT, i + 1, nums[i]);
    }
    printf("%d\n", query(BIT, 1, 4)); // 21
    return 0;
}
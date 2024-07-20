#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void backtrack(vector<int> &nums, vector<int> &current, vector<bool> &visited, vector<vector<int>> &results)
{
    if (nums.size() == current.size())
    {
        results.push_back(current);
        return;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (visited[i] == true) continue;
        visited[i] = true;
        current.push_back(nums[i]);
        backtrack(nums, current, visited, results);
        current.pop_back();
        visited[i] = false;
    }
}

int main()
{
    vector<int> nums = {4, 2, 6};
    vector<vector<int>> results;
    vector<int> current;
    vector<bool> visited(nums.size());
    backtrack(nums, current, visited, results);
    for (auto v: results)
    {
        for (auto x: v)
        {
            printf("%d ", x);
        }
        printf("\n");
    }
}
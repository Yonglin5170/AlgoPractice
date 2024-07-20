#include <iostream>
#include <vector>
#include <stack>
using namespace std;

pair<vector<int>, vector<int>> GreaterElements(vector<int>& nums)
{
    vector<int> previous_greater(nums.size(), -1); // 初始化结果数组，默认值为-1
    vector<int> next_greater(nums.size(), -1); // 初始化结果数组，默认值为-1
    stack<int> decreasing_stk; // 存储元素索引的（严格）单调递减栈

    for (int i = 0; i < nums.size(); i++)
    {
        // 注意是 <=
        while (!decreasing_stk.empty() && nums[decreasing_stk.top()] <= nums[i])
        {
            decreasing_stk.pop();
        }
        if (!decreasing_stk.empty()) previous_greater[i] = decreasing_stk.top();
        decreasing_stk.push(i);
    }
    // 需要清空栈
    decreasing_stk = stack<int>();
    for (int i = 0; i < nums.size(); i++)
    {
        // 注意是 <
        while (!decreasing_stk.empty() && nums[decreasing_stk.top()] < nums[i])
        {
            next_greater[decreasing_stk.top()] = nums[i];
            decreasing_stk.pop();
        }
        decreasing_stk.push(i);
    }
    return {previous_greater, next_greater};
}

pair<vector<int>, vector<int>> SmallerElements(vector<int>& nums)
{
    vector<int> previous_smaller(nums.size(), -1); // 初始化结果数组，默认值为-1
    vector<int> next_smaller(nums.size(), -1); // 初始化结果数组，默认值为-1
    stack<int> increasing_stk; // 存储元素索引的单调递增栈

    for (int i = 0; i < nums.size(); i++)
    {
        // 注意是 >=
        while (!increasing_stk.empty() && nums[increasing_stk.top()] >= nums[i])
        {
            increasing_stk.pop();
        }
        if (!increasing_stk.empty()) previous_smaller[i] = nums[increasing_stk.top()];
        increasing_stk.push(i);
    }
    // 需要清空栈
    increasing_stk = stack<int>();
    for (int i = 0; i < nums.size(); i++)
    {
        // 注意是 >
        while (!increasing_stk.empty() && nums[increasing_stk.top()] > nums[i])
        {
            next_smaller[increasing_stk.top()] = nums[i];
            increasing_stk.pop();
        }
        increasing_stk.push(i);
    }
    return {previous_smaller, next_smaller};
}

int main() {
    vector<int> nums = {2, 1, 2, 4, 3};

    // auto result = GreaterElements(nums);
    auto result = SmallerElements(nums);
    for (int n : result.first)
    {
        cout << n << " ";
    }
    cout << endl;
    for (int n : result.second)
    {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}

/*
nums:
              $
              $ $
        $   $ $ $
        $ $ $ $ $
index:  0 1 2 3 4
*/

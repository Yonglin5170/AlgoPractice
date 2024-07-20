#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int binary_search(vector<int> &a, int x)
{
    int left = 0, right = a.size() - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        // |  [0, l): < x  |a1|  |a2|   |a3|  (r, n-1]: > x  |
        //                  l     m      r
        if (x == a[mid]) return mid;
        else if (x > a[mid]) left = mid + 1;
        else right = mid - 1;
    }
    // left is the position where it should be.
    return -1;
}
// find the first number greater than or equal to x.
int lower_bound(vector<int> &a, int x)
{
    int left = 0, right = a.size();
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        // |  [0, l): < x  |a1|  |a2|   |a3|  [r, n]: >= x  |
        //                  l     m      r
        if (x <= a[mid]) right = mid;
        else left = mid + 1;
    }
    return left;
}

int main()
{
    vector<int> a = {0, 1, 1, 3, 3, 3, 4, 5, 6, 7};
    printf("%d\n", lower_bound(a, 2));
    return 0;
}
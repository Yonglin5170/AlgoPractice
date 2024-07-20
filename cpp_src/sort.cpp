#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
void select_sort(vector<int> &a)
{
    int N = a.size();
    for (int i = 0; i < N - 1; i++)
    {
        // find the minimum number
        int min_idx = i;
        for (int j = i + 1; j < N; j++)
        {
            if (a[j] < a[min_idx]) min_idx = j;
        }
        if (min_idx != i) swap(a[i], a[min_idx]);
    }
}

////////////////////////////////////////////////////////////////////////////////
// adjust sub-heap with root a[p]
void perc_down(vector<int> &a, int p, int N)
{
    if (p >= N) return;
    int x = a[p], parent, child;
    for (parent = p; parent * 2 + 1 < N; parent = child)
    {
        child = parent * 2 + 1;
        if (child + 1 < N && a[child + 1] > a[child]) child++;
        if (a[child] > x) a[parent] = a[child];
        else break;
    }
    a[parent] = x;
}

void insert(vector<int> &a, int x)
{
    a.push_back(x);
    int N = a.size(), parent, child;
    for (child = N - 1; child > 0; child = parent)
    {
        parent = (child - 1) / 2;
        if (a[parent] < x) a[child] = a[parent];
        else break;
    }
    a[child] = x;
}

void build_heap(vector<int> &a)
{
    int N = a.size();
    for (int p = N / 2 - 1; p >= 0; p--)
    {
        perc_down(a, p, N);
    }
    // vector<int> heap;
    // for (auto x: a)
    // {
    //     insert(heap, x);
    // }
    // a = heap;
}

int delete_max(vector<int> &a)
{
    int max_e = a[0], N = a.size();
    swap(a[0], a[N - 1]);
    a.pop_back();
    perc_down(a, 0, N - 1);
    return max_e;
}

void heap_sort(vector<int> &a)
{
    build_heap(a);
    int N = a.size();
    for (int i = N - 1; i > 0; i--)
    {
        swap(a[i], a[0]);
        perc_down(a, 0, i);
    }
}

////////////////////////////////////////////////////////////////////////////////
void insertion_sort(vector<int> &a)
{
    int N = a.size();
    for (int i = 1; i < N; i++)
    {
        int x = a[i], j;
        for (j = i; j >= 1; j--)
        {
            if (x < a[j - 1]) a[j] = a[j - 1];
            else break;
        }
        a[j] = x;
    }
}

////////////////////////////////////////////////////////////////////////////////
void shell_sort(vector<int> &a)
{
    vector<int> Sedgewick = {929, 505, 209, 109, 41, 19, 5, 1, 0};
    int si, N = a.size();
    for (si = 0; Sedgewick[si] >= N; si++);
    for (int D = Sedgewick[si]; D > 0; D = Sedgewick[++si])
    {
        for (int i = D; i < N; i++)
        {
            int x = a[i], j;
            for (j = i; j >= D; j -= D)
            {
                if (x < a[j - D]) a[j] = a[j - D];
                else break;
            }
            a[j] = x;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void bubble_sort(vector<int> &a)
{
    int N = a.size();
    // loop N - 1 times
    for (int i = 0; i < N - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < N - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                flag = true;
            }
        }
        if (flag == false) break;
    }
}

////////////////////////////////////////////////////////////////////////////////
int partition(vector<int> &a, int left, int right)
{
    // ||       x <= pivot  |       x > pivot   ||
    // ||   find x > pivot  |   find x <= pivot ||
    int p = 1.0 * rand() / RAND_MAX * (right - left) + left;
    swap(a[left], a[p]);
    int L = left, pivot = a[L];
    while (left < right)
    {
        // you must start scanning from right to left rather than from left to right,
        // because of the final swap of the pivot and a[left].
        // DO NOT MODIFY ">" AND "<="!
        while (left < right && a[right] > pivot) right--;
        while (left < right && a[left] <= pivot) left++;
        swap(a[left], a[right]);
    }
    swap(a[L], a[left]);
    return left;
}

void Qsort(vector<int> &a, int left, int right)
{
    if (left >= right) return;
    int pos = partition(a, left, right);
    Qsort(a, left, pos - 1);
    Qsort(a, pos + 1, right);
}

void quick_sort(vector<int> &a)
{
    srand(time(nullptr));
    int N = a.size();
    Qsort(a, 0, N - 1);
}

////////////////////////////////////////////////////////////////////////////////
void merge(vector<int> &a, vector<int> &temp, int L1, int R1, int L2, int R2)
{
    int i = L1, j = L2, idx = L1;
    while (i <= R1 && j <= R2)
    {
        if (a[i] < a[j]) temp[idx++] = a[i++];
        else temp[idx++] = a[j++];
    }
    while (i <= R1) temp[idx++] = a[i++];
    while (j <= R2) temp[idx++] = a[j++];
    for (int k = L1; k <= R2; k++)
    {
        a[k] = temp[k];
    }
}

void Msort(vector<int> &a, vector<int> &temp, int left, int right)
{
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    Msort(a, temp, left, mid);
    Msort(a, temp, mid + 1, right);
    merge(a, temp, left, mid, mid + 1, right);
}

void merge_sort(vector<int> &a)
{
    int N = a.size();
    vector<int> temp(N);
    Msort(a, temp, 0, N - 1);
}

void merge_sort_iter(vector<int> &a)
{
    int N = a.size();
    vector<int> temp(N);
    for (int step = 1; step < N; step *= 2)
    {
        for (int L1 = 0; L1 < N; L1 += step * 2)
        {
            int R1 = L1 + step - 1;
            if (R1 >= N - 1) break;
            int L2 = R1 + 1, R2 = min(R1 + step, N - 1);
            merge(a, temp, L1, R1, L2, R2);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
void print(vector<int> &a)
{
    int N = a.size();
    for (int i = 0; i < N; i++)
    {
        printf("%d", a[i]);
        if (i < N - 1) printf(" ");
        else printf("\n");
    }
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
    vector<int> a = {4, 8, 7, 6, 5, 9, 3, 2, 1, 0};
    // vector<int> a;
    // do
    // {
    //     int temp;
    //     scanf("%d", &temp);
    //     a.push_back(temp);
    // } while (getchar() != '\n');
    
    merge_sort(a);
    print(a);
    return 0;
}
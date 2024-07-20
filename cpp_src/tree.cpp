#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <ctime>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode *left, *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
	TreeNode(int _val, TreeNode *_left, TreeNode *_right) : val(_val), left(_left), right(_right) {}
};

TreeNode* build_tree(vector<string> &v)
{
    if (v.size() == 0 || v[0] == "null") return nullptr;
    TreeNode *root = new TreeNode(stoi(v[0]));
    queue<TreeNode*> q;
    q.push(root);
    int cnt = 1;
    while (!q.empty())
    {
        TreeNode *node = q.front();
        q.pop();
        if (cnt < v.size())
        {
            if (v[cnt] != "null")
            {
                node -> left = new TreeNode(stoi(v[cnt]));
                q.push(node -> left);
            }
            cnt++;
        }
        if (cnt < v.size())
        {
            if (v[cnt] != "null")
            {
                node -> right = new TreeNode(stoi(v[cnt]));
                q.push(node -> right);
            }
            cnt++;
        }
    }
    return root;
}

////////////////////////////////////////////////////////////////////////////////
// 递归遍历
void pre_order(TreeNode *root)
{
    if (root != nullptr)
    {
        printf("%d ", root -> val);
        pre_order(root -> left);
        pre_order(root -> right);
    }
}

void in_order(TreeNode *root)
{
    if (root != nullptr)
    {
        in_order(root -> left);
        printf("%d ", root -> val);
        in_order(root -> right);
    }
}

void post_order(TreeNode *root)
{
    if (root != nullptr)
    {
        post_order(root -> left);
        post_order(root -> right);
        printf("%d ", root -> val);
    }
}

////////////////////////////////////////////////////////////////////////////////
// 非递归遍历
void pre_order2(TreeNode *root)
{
    stack<TreeNode*> stk;
    while (root || !stk.empty())
    {
        while (root)
        {
            printf("%d ", root -> val);
            stk.push(root);
            root = root -> left;
        }
        root = stk.top();
        stk.pop();
        root = root -> right;
    }
}

void in_order2(TreeNode *root)
{
    stack<TreeNode*> stk;
    while (root || !stk.empty())
    {
        while (root)
        {
            stk.push(root);
            root = root -> left;
        }
        root = stk.top();
        stk.pop();
        printf("%d ", root -> val);
        root = root -> right;
    }
}

void post_order2(TreeNode *root)
{
    stack<TreeNode*> stk;
    TreeNode *pre = nullptr;
    while (root || !stk.empty())
    {
        while (root)
        {
            stk.push(root);
            root = root -> left;
        }
        root = stk.top();
        stk.pop();
        if (root -> right && root -> right != pre)
        {
            stk.push(root);
            root = root -> right;
        }
        else
        {
            printf("%d ", root -> val);
            pre = root;
            root = nullptr;
        }
    }
}

void level_order(TreeNode *root)
{
	if (root == nullptr) return;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty())
	{
		int size = q.size();
		while (size--)
		{
			root = q.front();
			q.pop();
			printf("%d ", root -> val);
			if (root -> left) q.push(root -> left);
			if (root -> right) q.push(root -> right);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
// recursively
int maxDepth(TreeNode *root)
{
    if (root == nullptr) return 0;
    int l = maxDepth(root -> left), r = maxDepth(root -> right);
    return max(l, r) + 1;
}
// iteratively
int maxDepth_iter(TreeNode* root)
{
	stack<TreeNode*> stk;
	stack<int> l_stk, r_stk;
	// left depth, right depth and depth of the current subtree
	int l = 0, r = 0, depth = 0;
	TreeNode *pre = nullptr;
	// postorder traversal
	while (root || !stk.empty())
	{
		while (root)
		{
			stk.push(root);
			// every node has left depth and right depth
			l_stk.push(0);
			r_stk.push(0);
			root = root -> left;
		}
		root = stk.top();
		stk.pop();
		// return from left side
		if (root -> right == nullptr || root -> right != pre)
		{
			l_stk.top() = depth;
			// very important!!! 
			// otherwise if root -> right != nullptr, next left depth might not be zero.
			depth = 0;
		}
		// right subtree hasn't been visited
		if (root -> right && root -> right != pre)
		{
			stk.push(root);
			root = root -> right;
		}
		else
		{
			// return from right side. (root -> right == pre)
			if (root -> right != nullptr) r_stk.top() = depth;
			l = l_stk.top();
			l_stk.pop();
			r = r_stk.top();
			r_stk.pop();
			depth = max(l, r) + 1;
			// printf("%d, l=%d, r=%d, depth=%d\n", root -> val, l, r, depth);
			pre = root;
			root = nullptr;
		}
	}
	return depth;
}


int main()
{
	string s = "[1,2,null,3,null,null,4,5,6]";
	// cin >> s;
	int left = 1;
	vector<string> v;
	for (int i = 1; i < s.size(); i++)
	{
		if (s[i] == ',' || s[i] == ']')
		{
			if (i > left) v.push_back(s.substr(left, i - left));
			left = i + 1;
		}
	}
	TreeNode *root = build_tree(v);
	// maxDepth_iter(root);
	level_order(root);
	printf("\n");
	return 0;
}
// input:
// [1,2,null,3,null,null,4,5,6]
//			1
//		  2/
//		3/
//		 \4
//		5/ \6
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;

bool is_op(string s)
{
    return s == "+" || s == "-" || s == "*" || s == "/";
}

void infix_to_postfix(queue<string> &infix, queue<string> &postfix)
{
    stack<string> stk;
    unordered_map<string, int> priority = {{"+", 0}, {"-", 0}, {"*", 1}, {"/", 1}};
    while (!infix.empty() || !stk.empty())
    {
        if (!infix.empty())
        {
            string s = infix.front();
            infix.pop();
            if (s == "(") stk.push(s);
            else if (s == ")")
            {
                while (stk.top() != "(")
                {
                    postfix.push(stk.top());
                    stk.pop();
                }
                stk.pop();
            }
            else if (is_op(s))
            {
                if (stk.empty() || priority[s] > priority[stk.top()]) stk.push(s);
                else
                {
                    while (!stk.empty() && stk.top() != "(" && priority[s] <= priority[stk.top()])
                    {
                        postfix.push(stk.top());
                        stk.pop();
                    }
                    stk.push(s);
                }
            }
            else
            {
                postfix.push(s);
            }
            
        }
        else
        {
            while (!stk.empty())
            {
                postfix.push(stk.top());
                stk.pop();
            }
        }
    }
}

double calculate(queue<string> &postfix)
{
    stack<double> stk;
    while (!postfix.empty())
    {
        string s = postfix.front();
        postfix.pop();
        if (is_op(s))
        {
            double y = stk.top();
            stk.pop();
            double x = stk.top();
            stk.pop();
            double ans;
            if (s == "+") ans = x + y;
            else if (s == "-") ans = x - y;
            else if (s == "*") ans = x * y;
            else ans = x / y;
            stk.push(ans);
        }
        else stk.push(stod(s));
    }
    return stk.top();
}

int main()
{
    string str;
    while (getline(cin, str))
    {
        if (str == "0") break;
        queue<string> infix, postfix;
        str += " ";
        int left = 0;
        for (; str[left] == ' '; left++);
        for (int i = left; i < str.size(); i++)
        {
            if (str[i] != ' ') continue;
            string sub_str = str.substr(left, i - left);
            infix.push(sub_str);
            for (left = i + 1; left < str.size() && str[left] == ' '; left++);
            i = left;
        }
        infix_to_postfix(infix, postfix);
        double ans = calculate(postfix);
        printf("%.2f\n", ans);
    }
    return 0;
}
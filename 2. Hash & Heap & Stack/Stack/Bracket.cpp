#include<stack>
#include<iostream>
using namespace std;

/*
The core thought to solve the problem is a data structure stack.
Basically, we should scan and check the every bracket one by one in the string.
And we have to do check 2 cases.
First case is that if the bracket we get is left bracket. We put it in the stack.
Second case is that if we get the right bracket. We have to compare the right bracket with the top of the stack.
If they are a pair, it means that they are leagal and we pop the top of the stack and continue to scsan the next bracket.
Otherwise, it means that they are illeagal and we have checked the wrong sequence so we return false
Finally, if we scan all the bracket in the string, we have to check the stack, if it is empty, it means that all the bracket pairs are leagal
we return true, otherwise, there are still some brackets cannot find correspoding bracket. we return false.
The algorithm have linear space consumption for the stack and  time complexity is linear cause it has to scan the string

*/
class Solution
{
public:
    bool validBrackets(string str) 
    {
        //每次扫描到一个字符 处理后（入栈 比对出栈 比对返回）都会移动到下一个 所以可以直接for循环 
        int ptr = 0;
        stack<char> bracketStack;
        while(ptr < str.size())
        {
            if(str[ptr] == '(' || str[ptr] == '[' || str[ptr] =='{')
            {
                //cout << "Got" << str[ptr] << "   Push!" << endl;
                bracketStack.push(str[ptr]);
                ptr++;
                continue;
            }
            if(str[ptr] == ')')
            {
                if(bracketStack.top() != '(')
                {
                    return false;
                }
                else
                {
                    //cout << "Pair! Pop!" << endl;
                    bracketStack.pop();
                    ptr++;
                    continue;
                }
            }
            if(str[ptr] == ']')
            {
                if(bracketStack.top() != '[')
                {
                    return false;
                }
                else
                {
                    //cout << "Pair! Pop!" << endl;
                    bracketStack.pop();
                    ptr++;
                    continue;
                }
            }
            if(str[ptr] == '}')
            {
                if(bracketStack.top() != '{')
                {
                    return false;
                }
                else
                {
                    //cout << "Pair! Pop!" << endl;
                    bracketStack.pop();
                    ptr++;
                    continue;
                }
            }
        }
        return !bracketStack.empty();
        //if(bracketStack.empty())
        //{
        //    return true;
        //}
        //return false;
    }
};

int main()
{
    Solution s;
    string a = "[()(())[{{}}]]{}";
    cout << s.validBrackets(a);
}
#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
传入一个字符串 用字符串的元素组成的最长回文串有多长
这道题的字符可以任意组合 较简单 
最大回文子串则规定了是子串 使用n^2的中心线或动态规划求解

由于任意组合 先检查各个字符 只要各个字符是偶数即可组成回文串 并且有一个字符可以是奇数个
本质其实是统计字符的数量关系 思路清楚后实现就比较简单 
*/
int longestPalindrome(string s)
{
    map<char, int> numberOfChar;
    for(int i = 0; i < s.size(); i++)
    {
        numberOfChar[s[i]] ++;
    }

    int flag = 1;
    int length = 0;

    map<char, int> :: iterator it;
    for(it = numberOfChar.begin(); it != numberOfChar.end(); it++)
    {
        if(it -> second % 2 == 0)
        {
            length += it -> second;
        }
        else
        {
            if(flag)
            {
                length += it -> second;
                flag = 0; 
            }
            else
            {
                length += it -> second - 1;
            }
        }
    }
    return length;
}

int main()
{
    string s = "abccccddaa";
    cout << longestPalindrome(s);
}

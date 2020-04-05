#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
/*
和最大无重复子串相同 双指针维护一个满足要求的窗口 即窗口包含小串

在判断大串是否包含小串时 遍历小串检查是否在大串中出现 时间复杂度为m*n
另一种方法 利用哈希记录两个串中各字符的数量 然后比较 需要n的空间复杂度和n的时间复杂度 

维护过程和最长无重复子串类似 扩大窗口维护题目要求关系的同时 记录解
窗口问题核心就是实现好滑动-维护的过程即可
*/


bool isIncluded(string str, string sub)
{
    map<char, int> strHash;
    map<char, int> subHash;

    for(int i = 0; i < str.size(); i++)
    {
        if(strHash.find(str[i]) == strHash.end())
        {
            strHash[str[i]] = 1;
        }
        else
        {
            strHash[str[i]]++;
        }
    }
    for(int i = 0; i < sub.size(); i++)
    {
        if(subHash.find(sub[i]) == subHash.end())
        {
            subHash[sub[i]] = 1;
        }
        else
        {
            subHash[sub[i]]++;
        }
    }

    for(int i = 0; i < sub.size(); i++)
    {
        if(strHash[sub[i]] < subHash[sub[i]])
        {
            return false;
        }
    }
    return true;

}

string minIncludedWindow(string str, string sub)
{
    int left = 0;
    int right = sub.size() - 1;
    int min = 100;
    map<char, int> numberOfChar;
    string currentwindow;
    string finalWindow;

    while(right < str.size())
    {
        currentwindow = str.substr(left, right - left + 1);
        //cout << "当前窗口: " << currentwindow << endl;
        // 若当前窗口不包含 则继续右移扩大
        if(!isIncluded(currentwindow, sub))
        {
            //cout << "不包含" << sub << endl;
            right ++;
        }
        // 若包含窗口 首先循环从左缩减到最小包含包含窗口 然后右移扩大窗口 
        // 下一次循环会继续缩减
        else
        {
            //cout << "包含" << sub << endl;
            while(isIncluded(currentwindow, sub))   
            {
                left ++;
                currentwindow = str.substr(left, right - left + 1);
            }
            left --;    //循环结束后left要++ 因为循环结束条件时窗口不包含
            if(min > right - left)  //每取到一个包含的窗口 就记录最小
            {
                min = right - left;
                finalWindow = str.substr(left, right - left + 1);
            }
            right ++;   //向右移动
        }
    }
    return finalWindow;
}

int main()
{
    cout << minIncludedWindow("MADOBCCABEC", "ABCC");
    //cout << isIncluded("ADOBEODEBANC", "ABC");
}
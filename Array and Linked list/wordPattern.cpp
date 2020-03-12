#include<iostream>
#include<map>
using namespace std;
/*
传入模式和但词组检测是否匹配
思路很简单 就是通过字典检查是否出现过
实现注意字符串的处理 for扫描检查逐个添加到word中 直到分割符号 重置word即可 
*/
bool wordPattern(string pattern, string str)
{
    map<char, string> patternMap;
    int index = 0;
    string word = "";

    const char SPACE = ' ';
    str.push_back(SPACE);

    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] != SPACE)
        {
            word += str[i];
        }
        else
        {
            if(patternMap.find(pattern[index]) == patternMap.end())
            {
                patternMap[pattern[index]] = word;
            }
            else
            {
                if(patternMap[pattern[index]] != word)
                {
                    return false;
                }
            }
            word = "";
            index ++;
        }
    }
    return true;
}

int main()
{
    string pattern = "abba";
    string str = "dog sss cat dog";
    cout << wordPattern(pattern, str);
}
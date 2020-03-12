#include<iostream>
#include<map>
#include<vector>
using namespace std;
/*
传入一个长字符串 有acgt四个字符组成 找到所有长度为10的出现次数大于1的子串 
由于子串长度固定 因此枚举复杂度为n 之所以子串枚举复杂度为n^2 是要枚举不同长度
因此枚举所有子串 用map记录出现次数 最后筛选出所有次数大于1的即可
*/
vector<string> findRepeatedDnaSeq(string s)
{
    vector<string> results;
    map<string, int> seqHash;
    for(int i = 0; i < s.size(); i++)
    {
        string substr = s.substr(i, 10);
        seqHash[substr] ++;
    }
    map<string, int> :: iterator it;
    for(it = seqHash.begin(); it != seqHash.end(); it++)
    {
        if(it -> second > 1)
        {
            results.push_back(it -> first);
        }
    }
    return results;
}

int main()
{
    string s = "AAAAACCCCCAAAAACCCCCAAAAAGGGTTT";
    vector<string> r = findRepeatedDnaSeq(s);
    for(int i = 0; i < s.size(); i++)
    {
        cout << r[i]<< endl;
    }
}
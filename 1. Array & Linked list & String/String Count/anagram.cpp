#include<map>
#include<iostream>
#include<vector>
using namespace std;
/*
传入一个单词组 把由颠倒字母顺序而构成的单词分组输出
仍然是map的运用 核心就是map的key是同组单词的共同特征 value就是分组的单词
key可以是什么？
第一个方案就是 排序 排序可快速判断两个单词是颠倒顺序而成的
第二个方案就是 各字符数量表 若每个字符数量一致 则就是颠倒而成 这个表用map也可 数组更方便 代表26个字符的个数
之后就类似wordpattern 建立map 扫描单词 排序露出原型 有则加入 无则创建
*/

vector< vector<string> > groupAnagrams(vector<string>& strs)
{
    map<string, vector<string> > protoHash;
    vector< vector<string> > groups;
    for(int i = 0; i < strs.size(); i++)    //扫描所有单词归类入哈希
    {
        string proto = strs[i];     
        sort(proto.begin(), proto.end());   //sort是原地方法

        protoHash[proto].push_back(strs[i]);
    }

    map< string, vector<string> > :: iterator it;
    for(it = protoHash.begin(); it != protoHash.end(); it++)
    {
        groups.push_back(it -> second);
    }

    return groups;
}
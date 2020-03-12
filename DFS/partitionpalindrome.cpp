#include<iostream>
#include<vector>
using namespace std;
/*
传入一个字符串 返回所有切割 使得切割而成的所有子串都是回文的
首先考虑有多少种切割方式 n个字符有n-1个间隔可以切割 可以选择切或不切
落刀概念有些抽象 因为数组中没有落刀的索引 进一步的 我们可以认为是[0,1,...n-1]求子集 每个子集表示一种取值/切割
比如 [2,4] 表明在2，4号元素后落刀 或者理解为子串向右延伸到2，4 集合把字符串分割成[0,2][3,4][5,n-1]等子串  
注意等价于求子集问题 核心不在于值是什么样的 在于构造的解集合是否可以通过n步 每一步取/不取来构成 
当传入index进入递归  接下来i循环遍历下一刀的位置 就可以检查index到i之间的子串是否回文 如果是则加入子集中
求子集中则问的比较直接 直接问的是每次取元素的结果 而这道题不问落刀地点的集合 而是要显式的把切割结果返回 因此多一步构造切割结果

二叉树求子集实现无法解决 因为二叉树求子集在每次递归中 选择当前位置的取/不取 然后到下一个位置 无法记录两次取处之间的关系

*/

bool isPalindrome(string str)
{
    int left = 0;
    int right = str.size() - 1;
    for(int i = 0; i < str.size() / 2; i++)
    {
        if(str[left + i] != str[right - i])
        {
            return false;
        }
    }
    return true;
}

void recursionByMulTree(string s, vector< vector<string> > &results, vector<string> &result, int index)
{
    if(index == s.size())                   //后面无刀可落 当前子集生成完毕 加入集合后返回
    {
        results.push_back(result);
        return;
    }
    for(int i = index; i < s.size(); i++)   //遍历所有元素位置 本质上是取数组 [index, i]的区间
    {
        if( isPalindrome(s.substr(index, i - index + 1)))   // [index, i] 左右都闭 因为下一次是 [i+1, xxx
        {
            result.push_back(s.substr(index, i - index + 1));
            recursionByMulTree(s, results, result, i + 1);
            result.pop_back();
        }   
    }
}

vector< vector<string> > partition(string s)
{
    vector< vector<string> > results;
    vector<string> result;
    int index = 0;              //第一个子串是[0,...]
    recursionByMulTree(s, results, result, index);
    return results;
}

int main()
{
   string s = "aaabc";
   vector< vector<string> > results = partition(s);
   for(int i = 0; i < results.size(); i++)
   {
       for(int j = 0; j < results[i].size(); j++)
       {
           cout << results[i][j] << ",";
       }
       cout << endl;
   }
}
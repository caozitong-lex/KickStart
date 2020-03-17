#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
给定一个数组 求出其中和为0的子数组的索引范围
暴力做法是n^2的遍历所有子数组 同时求和 检查是否为0
使用前缀和数组 若前缀和predixSum i == prefixSum j 说明i到j之间和为0 
那么问题就归结为查找数组中相同的两个数 使用哈希表可以在n的时间内找到 但需要用到n的空间
*/

pair<int, int> getRangeOfSumEqualsZero(vector<int> arr)
{
    // 构造前缀和数组 时间复杂度为n
    vector<int> prefix;
    prefix.push_back(0);
    int sum = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        prefix.push_back(sum);
    }
    // 查找该数组中两个相同的数 
    // 构造哈希 建立 值-索引的映射 时间复杂度为n
    pair<int, int> result(0, 0);
    map<int, int> arrHash; 
    for(int i = 1; i < prefix.size(); i++)
    {
        if(arrHash.find(prefix[i]) == arrHash.end())
        {
            arrHash[prefix[i]] = i - 1;
        }
        else
        {
            result.first = arrHash[prefix[i]];
            result.second = i - 1;
        }
    }
    return result;  
}

int main()
{
    int t[] = {5, -1, 0, 5, -2, -3, 1, -5};
    vector<int> arr(t, t+8);
    pair<int, int> r = getRangeOfSumEqualsZero(arr);
    cout << r.first << "-" << r.second << endl;
}
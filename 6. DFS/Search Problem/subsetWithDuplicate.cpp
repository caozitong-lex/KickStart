#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
/*
求带重复元素集合的子集 
由于搜索问题会考虑全部的解 因此每个元素都被当作不同个体全部取一遍 这会导致生成的子集 有些是重复的
解决重复问题有两个插入点  1.修改求子集算法本身 这点很难 2.得到结果后统一去重
第二种方案简单可行 问题是 [1,1,2]和[1,2,1]是重复子集 但这是概念上的重复 没有函数能够判定这是重复 set不会认为这是重复
因此对所有子集排序 然后丢入set去重 
更好的方法是 直接对初始集合排序 这样的得到的子集也都是排序后的 因为求子集的算法 维护了子集元素在原集合中的相对顺序 所以原集合是有序的 子集也一定有序
*/
void recursionByMutipleTree(vector<int> &nums, vector< vector <int> > &subsets, vector<int> &subset, int level)
// 基本参数/题目参数 全局笔记本/解 辅助全局笔记本 层笔记本 （往往辅助全局笔记本和层笔记本可以互相转化 因为都是记录某层节点的局部状态 看哪种方便）
{
    subsets.push_back(subset);
    for(int i = level; i < nums.size(); i++)
    {
        subset.push_back(nums[i]);
        recursionByMutipleTree(nums, subsets, subset, i + 1);
        subset.pop_back();
    }
}
vector< vector<int> > subsetWithDup(vector<int> &nums)
{
    //必要数据结构
    vector< vector <int> > subsets;         //全局笔记本
    vector<int> subset;                     //辅助全局笔记本
    set< vector<int> > subsetsWithoutDup;   //过滤处理set
    vector< vector <int> > result;          //最终解
    int level = 0;

    sort(nums.begin(), nums.end());
    recursionByMutipleTree(nums, subsets, subset, level);
    //把解放入过滤set
    for(int i = 0; i < subsets.size(); i++)
    {
        subsetsWithoutDup.insert(subsets[i]);
    }
    //从过滤set取出最终解
    set< vector<int> > :: iterator it;
    for(it = subsetsWithoutDup.begin(); it != subsetsWithoutDup.end(); it++)
    {
        result.push_back(*it);
    }
    return result;
}


int main()
{
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    
    vector<  vector<int> > result;
    result = subsetWithDup(nums);

    for(int i = 0; i < result.size(); i++)
    {
        if(result[i].size() == 0)
        {
            cout<<"[]";
        }
        for(int j = 0; j < result[i].size(); j++)
        {
            cout<<result[i][j];
        }
        cout << endl;
    }
    return 0;
}

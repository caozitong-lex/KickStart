#include<iostream>
#include<set>
#include<vector>
using namespace std;

/*
对于有重复元素的集合 求出所有满足和等于target的子集
最暴力的方法是使用求不重复子集的结果 对所有子集一一检查和 但显然这样非常低效 因为满足和=target的子集非常少 大量子集求解被浪费
所以在求不重复子集的基础上 接口函数不变 依旧检查重复 递归函数中 在递归生成子集的过程中进行剪枝 只要当前子集和大于target 则不继续递归 以及在加入集合时 判断该子集是否符合要求 
*/


void recursionWithPruning(int target, vector<int> &nums, vector< vector<int> > &subsets, vector<int> &subset, int level, int sum)
{
    // 检查是否符合要求
    if(target == sum)           
    {
        subsets.push_back(subset);
    }
    // 递归生成子集
    for(int i = level; i < nums.size(); i++)
    {
        subset.push_back(nums[i]);
        if(sum + nums[i] <= target) //剪枝
        {
            recursionWithPruning(target, nums, subsets, subset, i + 1, sum + nums[i]);
            //注意其中的层参数 i+1 和 sum + nums[i] 它们都是和【当前节点】绑定的层局部参数 在参数中更新
            //每选择一个i节点 都会有当前的子集和 以及 取值位置i 状态 
            //也可以写作局部笔记本 但记得要回溯即可  
        }
        subset.pop_back();
    }
}
void recursionWithBinary(int target, vector<int> &nums, vector< vector<int> > &subsets, vector<int> &subset, int level, int sum)
{

    if(sum > target || level >= nums.size())
    {
        return;
    }
    

    subset.push_back(nums[level]);
    sum += nums[level];
    if(sum == target)
    {
        subsets.push_back(subset);
    }
    recursionWithBinary(target, nums, subsets, subset, level + 1, sum);  //由于要先加入子集并检测和 所以无法写到参数中更新
    
    subset.pop_back();
    sum -= nums[level];
    recursionWithBinary(target, nums, subsets, subset, level + 1, sum);
}



vector< vector<int> > combinationSum(vector<int> &nums, int target)
{
    vector< vector<int> > subsets;
    vector< vector<int> > result;
    vector<int> subset;
    set< vector<int> > subsetsWithoutDup;
    int level = 0;
    int sum = 0;

    sort(nums.begin(), nums.end());

    //recursionWithPruning(target, nums, subsets, subset, level, sum);
    recursionWithBinary(target, nums, subsets, subset, level, sum);

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
    nums.push_back(10);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(6);
    nums.push_back(1);
    nums.push_back(5);
    
    vector<  vector<int> > result;
    result = combinationSum(nums, 8);

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

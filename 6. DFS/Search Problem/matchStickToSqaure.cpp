#include<iostream>
#include<vector>
using namespace std;
/*
给定一个数组 每个元素代表一根火柴 数值代表火柴长度 判断是否能用这些火柴组成一个正方形
这道题进一步理解就是把一组数据分割为四个部分 无视相对位置
整理之前所有的dfs题目:
树的dfs
矩阵的dfs
数组的dfs 
求子集类型问题 是从数组中选择部分元素构成子集 
-> 二叉树：每一步选择取/不取 固定步数 生成取/不取的长为n的全排列 进一步结果是元素的全部子集
-> 多叉树：每一步选择元素 步数不定 结果是元素的全部子集
生成括号问题 二叉树 每一步选择左/右 固定步数 生成左/右的长为n的全排列 
字符串划分 多叉树 每一步选择位置 步数不定 结果是位置的全部子集 进一步结果是字符串的全部划分

所以解决问题 需要考虑首先树生成了什么 其次考虑利用生成的结果 可以如何进一步解决问题
两种思路考虑的都是每个位置上所做选择范围
多叉树生成的是选择范围（1/2/3/4...）的子集 选择范围往往是题目直接给出的
二叉树生成的则是选择范围（左/右 取/不取）的在特定数量下的全排列 往往选择范围并非题目直接给出 而是派生的 比如选/不选 左/右

这道题是数组dfs 我们最终需要的是一个数组的全部划分 比如1 5 | 2 4 | 2 4 | 3 3  这样显然不是直接可以求出的 那么如何从 子集或全排列转化呢
比如一个数组有6根火柴 每根火柴的选择范围是四边之一 标号为1234 这就是派生出的选择范围  如 113422 我们希望得到这样的全部排列
那么这道题要数组的全部子集有用吗？显然没用 划分类是固定的 用到的数字也是固定的 

*/

void recursionByBinTree(bool &sign, vector<int>& nums, vector<int> &edges, int index, int sideLength)
{
    
    if(index == nums.size())    //所有火柴决策做完
    {
        if(edges[0] == sideLength && edges[1] == sideLength && edges[2] == sideLength && edges[3] == sideLength)
        {
            sign = true;
        }
        return;
    }
    for(int i = 0; i < 4; i++)              //每一根有4种选择
    {
        if((edges[i] + nums[index]) <= sideLength)   //剪枝 若已超边长 无需尝试下一根
        {
            edges[i] += nums[index];
            recursionByBinTree(sign, nums, edges, index + 1, sideLength);
            edges[i] -= nums[index];
        }
    }
}

bool makeSquare(vector<int>& nums)
{
    if(nums.size() < 4) //第一次优化：检查边数是否小于4 
    {
        cout << "Side number < 4!" << endl;
        return false;
    }
    int perimeter = 0;  //第二次优化：检查周长是否能被4整除 -> 取余操作
    for(int i = 0; i < nums.size(); i++)
    {
        perimeter += nums[i];
    }
    if(perimeter % 4)
    {
        cout << "Cannot be divided!" << endl;
        return false;
    }

    vector<int> edges(4); //初始化为4个0
    int index = 0;
    bool sign = false;
    sort(nums.rbegin(), nums.rend());   //第三次优化：  逆序 从大到小 从大的火柴棒开始拼
    
    recursionByBinTree(sign, nums, edges, index, perimeter / 4);
    return sign;
    
}

int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(3);
    cout << makeSquare(nums);
}
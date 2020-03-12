#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool cmp(vector<int> a, vector<int> b)
{
    return a[0] < b[0];
}
class Solution
{
public:
    int maxSubarray(vector<int> &nums)
    //给定数组 求最大子数组
    //暴力搜索所有子数组为n^2 dp可以优化为n
    //dp[i]为以索引i的元素为尾的子数组的最大和 而不是索引i内的子数组的最大和 等于dp[i-1]+nums[i] 和nums[i]的较大值
    //间接dp的经典例题 无法直接用dp[i]求得解 但可以通过所有备选项dp[i]得到最终解
    
    {   
        //初始化状态数组
        vector<int> dp;
        for(int i = 0; i <= nums.size(); i++)
        {
            dp.push_back(0);
        }
        //边界起点
        dp[0] = nums[0];
        int maxArray = dp[0];
        //状态转移
        for(int i = 1; i < nums.size(); i++)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            //比较所有状态 最大值为最终解 也可以写在状态转移循环后 单独比较
            if(dp[i] > maxArray)
            {
                maxArray = dp[i];
            }
        }
        return maxArray;
    }

    int longestUpSubseq(vector<int> &nums)
    //传入数组 返回最长递增子序列的长度
    //dp[i]为 以i索引位置的元素为尾部的递增子序列的最大长度
    //和之前的dp相比 这道题需要打两次擂台 第一个是构造以i为尾部的最大序列 第二个是i以内所有尾部的最大序列
    //第一次擂台和背包问题类似 当前状态和之前的多个状态相关 且不是多个状态的直接加和 而是比较最大值
    //第二次擂台则是因为dp[i]状态的设置并非是解 而是间接解 比较这些dp[i] 来得到题目最终的解
    //打擂台中 需要两个变量 求最值变量 和 测试变量 求最值变量在每次和测试变量比较后更新 求最值变量不一定需要自己设置max等变量 比如dp[i]是所有dp[j]+1中最大的 那么直接用dp[i]打擂台即可 它自身就是最值变量 
    //或者直接用max函数

    //最长上升子数组问题 则不需要第一次打擂台 只需要判断一次能否和前面的一个连接即可 
    {   
        //初始化状态数组
        vector<int> dp;
        for(int i = 0; i < nums.size(); i++)
        {
            dp.push_back(1); //每个节点为尾部的序列最小长度为1 
        }
        //边界 初始化包括了边界

        //状态转移
        int longest = 0; //以各个元素为尾部的所有上升子序列的最大长度
        for(int i = 1; i < dp.size(); i++)
        {
            for(int j = 0; j < i; j++) //尝试连接到i之前的所有子序列后
            {
                if(nums[i] > nums[j])   //若是递增 可以连接到j子序列后 找到所有可连接的子序列
                {
                    if(dp[i] < dp[j] + 1) // 打擂台 找到可连接子序列中最长的
                    {
                        dp[i] = dp[j] + 1;
                    }
                    //等价于 dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            if(longest < dp[i]) //打擂台 找到所有尾部的最长子序列
            {
                longest = dp[i]; 
            }
            //等价于longest = max(longest, dp[i]);
        }
        return longest;
    }

    /*
    传入一组信封的尺寸（长，宽） 大信封可以套在小信封上 问这些信封最多可以套几层
    其实就是 最长上升子序列 只不过需要自己处理为有序序列 接龙条件由大小变成了两个值的大
    注意处理为有序数列的原则并非一定是严格的小在前 大在后 只要保证接龙时 不会出现前面的接在后面即可 
    比如信封 也许[3,4]  [4,2] 这两个谁在前在后都无所谓 有序的目的是 保证靠前元素无法接在靠后元素的后面
    因为扫描时 扫描到第i+1个元素时 检查的是 0到i 元素 后面的则不检查 
    */
    int maxEnvelope(vector< vector<int> > envelopes)
    {
        sort(envelopes.begin(), envelopes.end(), cmp);  //比最长上升子序列多的一步就是 自己构造有序序列

        int len = 0;
        vector<int> dp(envelopes.size(), 1);

        for(int i = 1; i < envelopes.size(); i++)       //填充dp[i]
        {
            for(int j = 0; j < i; j++)                  //在i之前寻找
            {
                if(envelopes[i][0] > envelopes[j][0] && envelopes[i][1] > envelopes[j][1])  //如果能覆盖之前的信封
                {
                    if(dp[j] + 1 > dp[i])               //打擂台 比较套数
                    {
                        dp[i] = dp[j] + 1;              //填充dp[i]
                    }
                }
            }
        }

        for(int i = 0; i < dp.size(); i++)
        {
            if(dp[i] > len)
            {
                len = dp[i];
            }
        }
        return len;
    }

    /*
    传入一个数组 求出最大子集的大小 其中元素任何两个元素为倍数关系
    本质是最长上升子序列 需要自己进行排序构成有序序列 接龙关系由大小变成了倍数
    */
    int longestDivideSet(vector<int> nums)
    {
        sort(nums.begin(), nums.end());

        int len = 0;
        vector<int> dp(nums.size(), 1);

        for(int i = 1; i < nums.size(); i++)
        {
            for(int j = 0; j < i; j++)
            {
                if(nums[i] % nums[j] == 0)
                {
                    if(dp[i] < dp[j] + 1)
                    {
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
        for(int i = 0; i < nums.size(); i++)
        {
            if(len < dp[i])
            {
                len = dp[i];
            }
        }
        return len;
    }

};


int main()
{
    Solution s;
    /*
    vector<int> nums;
    nums.push_back(-2);
    nums.push_back(1);
    nums.push_back(-3);
    nums.push_back(4);
    nums.push_back(-1);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(-5);
    nums.push_back(4);
    */
    int test[] = {1,3,2,3,1,4};
    vector<int> nums;
    for(int i = 0; i < 6; i++)
    {
       nums.push_back(test[i]);
    }
    cout << s.longestUpSubseq(nums);
}
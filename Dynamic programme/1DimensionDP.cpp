#include<iostream>
#include<vector>
using namespace std;

class Solution 
{
public:
//每次爬楼梯时可以走1/2阶 爬上n阶有多少种
//dp[i]为爬上i阶有多少种 等于dp[i-1] + dp[i-2] 
    int climbStairs(int n)
    {
        //初始化状态矩阵
        vector<int> dp;
        for(int i = 0; i < n; i++)
        {
            dp.push_back(0);
        }
        //边界起点
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        //状态转移
        for(int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        //返回终点
        return dp[n];
    }
    /*
    Obviously, it is a problem of combination. The direct method is brutal algorithm.
    We can try all the combination of the coins to acheive the target money.
    The better way is dynamic programming.
    First of all, we set the state dpn as the minimum number of coins.
    Next step is build the function of state. Obviously, if we want to get the minimum number of coins to acheive n, 
    it relates to the previous states, dp n minor every face value. And we compare every previous states to get the minimum one and plus one as the current state
    For example if we have collect 10 dollars, and we have 1 dollar coins and 5 dollor coins.
    so the dp[10] relate to the dp[9] and dp[5] cause we just need another coin to acheive 10 from 5 or 9.
    If we use dynamic programming we can reduce the time complexity to linear level and without additional space 
    */

    int coinChange(vector<int> &coins, int amount)
    //一维背包问题 
    //coins里包括不同面值的钞票 amount是目标金额 求组合成目标金额的最小钞票数量 若凑不成 则返回-1
    //状态转移 dp[i]和前面多个状态有关 如果是之和 那么相加即可 如果是取最值 那么擂台即可
    //还要注意一些合理性条件 比如dp[i]的i不能小于0 以及之前的状态是否有解 
    {
        //初始化状态矩阵 dp[i]为凑齐i块钱需要的最小钞票数量
        vector<int> dp;
        for(int i = 0; i <= amount; i++)
        {
            dp.push_back(-1);
        }
        //边界起点 
        dp[0] = -1;
        for(int i = 0; i < coins.size(); i++)
        {
            dp[coins[i]] = 1;
        }
        // 状态转移 dp[i]等于凑成 （i-各种钞票额度）的最小数量+1
        // 比如问凑8块钱的最小张数 额度有1 2 5 那么这个最小张数 应该是凑成 7 6 3的最小张数的最小值
        for(int i = 1;  i <= amount; i++) //遍历每个dp
        {
            for(int j = 0; j < coins.size(); j++) //每个状态和所有面值都有关 测试每个面值
            {
                if(i - coins[j] >= 0 && dp[i - coins[j]] != -1) //首先当前金额大于等于当前面值 其次上个状态有解
                {
                    if(dp[i] == -1 || dp[i] > dp[i - coins[j]] + 1) //打擂台比较最小dp[i] 当前无解 或 当前有解但不够小
                    {
                        dp[i] = dp[i - coins[j]] + 1;
                    }
                }
            }
        }
        return  dp[amount];
    }

    void FibonacciByDp(int n)
    {
        //dp状态数组
        vector<int> dp;
        for(int i = 0; i <= n; i++)
        {
            dp.push_back(1);
        }
        //边界
        dp[1] = 1;
        dp[2] = 1;
        //状态转移
        for(int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 2] + dp[i - 1];
        }
        //终点
        for(int i = 1; i <= n; i++)
        {
            cout << dp[i] << " ";
        }
    }

    int FibonacciByRec(int n)
    {
        //分治实现 有返回值 但只能计算第n个值 如果想要得到前n个 就调用n次
        //遍历实现的精髓是遍历递归树的过程中得到解 用全局笔记本记录 
        if(n == 1 || n == 2)
        {
            return 1;
        }
        return FibonacciByRec(n - 1) + FibonacciByRec(n - 2);
    }
    /*
    打家劫舍：传入一组值 不能两个相邻值取值 从这组值中取得的最大总数是多少
    对于任意一个值次序为i  有两种情况 选或不选 
	1. 选择i 那么i-1则不能选 i-1不选 就是考虑前i-2个值的最大总数+num[i]
    2. 若不选i 意味着就是考虑i-1个值的最大总数
    那么i个房间的问题 就是比较两种情况哪个较大即可 
    注意 在考虑转移方程时 不要提前考虑后面的情况 比如考虑前i个值的最大总数  不要考虑i+1或者i+k的分布情况 只要关注于前i个值如何 取到最大即可 
    这也是动态规划的核心 做好每一步的事情 每一步可以为后一步做基础 而不用提前考虑后一步

    */

    int rob(vector<int> &nums)
    {
        if(nums.size() == 0)
        {
            return 0;
        }
        if(nums.size() == 1)
        {
            return nums[0];
        }

        vector<int> dp(nums.size(), 0); //快速初始化
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);

        for(int i = 2; i < nums.size(); i++)
        {
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
        }
        return dp[nums.size() - 1];
    }

    


};

int main()
{
    vector<int> coins;
    coins.push_back(1);
    coins.push_back(2);
    coins.push_back(5);
    coins.push_back(7);
    coins.push_back(10);
    
    Solution s;
    //cout << s.coinChange(coins, 18);

    cout << s.FibonacciByRec(10);
}
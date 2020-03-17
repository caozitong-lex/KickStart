#include<iostream>
#include<vector>
using namespace std;

/*
求最大子数组和 dp方法见dp集合 这里用前缀和方法
sum i~j = prefix j - prefix i 
子数组和实际上由两个变量控制 因此暴力做法是双重for循环遍历所有子数组
或者说 每次固定一个prefix j 然后遍历找到最小的prefix i 
如果想要把n^2优化为n 意味着需要省去一重循环 如何在找最小的prefix i 的过程中把时间n简化为1？
事实上 当我们遍历所有 prefix j时 就已经计算了所有前缀和 而最小的prefix i 就等价于最小的prefix j
因此如何得到最小的prefix i? 就是在遍历prefix j的过程中记录打擂台得到最小的prefix j就作为min prefix i
有了min prefix i 显然就可以得到当前prefix j下的最大数组和 
那么每次遍历prefix j时打擂台就可以得到最终的最大数组和 

所以单次for循环中要做的事情如下：
计算所有前缀和prefix j
然后计算当前prefix j下最大子数组和 也就是prefix j - min prefix i
最后更新min prefix i 也就是打擂台得到最小的prefix j

所以 这道题优化的核心是 充分利用已经计算过的prefix
*/
int maxSubArray(vector<int> &arr)
{
    int maxSumOfSubarray = -1000;
    int prefixSumEnd = 0;
    int prefixSumStart = 0;
    int minPrefixSumStart = 0;

    for(int i = 0; i < arr.size(); i++)
    {
        prefixSumEnd += arr[i];
        maxSumOfSubarray = max(maxSumOfSubarray, prefixSumEnd - minPrefixSumStart);
        minPrefixSumStart = min(minPrefixSumStart, prefixSumEnd);
    }

    return maxSumOfSubarray;
}
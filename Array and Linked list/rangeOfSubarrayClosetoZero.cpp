#include<iostream>
#include<vector>
using namespace std;

/*
查找和为0的子数组范围的升级版 查找接近0的子数组范围
还是使用前缀和的思想 问题转化为了【如何查找数组中最接近的两个元素】
暴力法仍然是n^2的双重for循环 确定一个数后 for循环查找另一个尽可能接近的数
问题再次转化为【给定一个数 找到集合中和它最接近的另一个数】
第一种方式是高级数据结构 使用平衡搜索树 它可以查找某个数相邻的两个数 自然就可以得到最接近的那个数 
构造树的时间复杂度为n 每次查找效率为logn  n次查找效率为nlogn 
强调平衡是因为搜索树的形状不定 最差情况下是n 和for循环相同 因为只有平衡树的高度/搜索是logn
第二种是排序后二分查找 和搜索树思路类似 二分查找当找不到指定目标时 也会把结果缩小到目标值最近的两个数 比较即可
第三种是排序 无需二分查找 只需要排序后 比较每两个相邻数的差值 就可以得到最近的两个数 
*/

bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.first < b.first;
}
pair<int, int> getRangeOfSubarrayCloseToZero(vector<int> arr)
{
    pair<int, int> result;
    // 把数组构造为前缀和数组 
    // 从i到j范围内子数组接近0 即第i+1和j+1个数之间的子数组接近0 说明前i个数前缀和 和 前j+1个数前缀和相近 等价于前缀和数组第i和j+1元素最接近
    vector<int> prefix;
    prefix.push_back(0);
    int sum = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
        prefix.push_back(sum);
    }

    // 先把前缀和数组改造为结对数组 每个元素是元素值和索引
    vector< pair<int, int> > arrPairs;
    for(int i = 0; i < prefix.size(); i++)
    {
        pair<int, int> arrPair(prefix[i], i);
        arrPairs.push_back(arrPair);
    }
    //再把结对数组排序
    sort(arrPairs.begin(), arrPairs.end());
    //记录每个结对之间的差值 并打擂台得到最小差值和相应结对在前缀和数组中的索引
    int minMinor = 100;
    pair<int, int> minMinorIndex;

    for(int i = 0; i < arrPairs.size() - 1; i++)
    {
        if(abs(arrPairs[i].first - arrPairs[i + 1].first) < minMinor)
        {
            minMinor = abs(arrPairs[i].first - arrPairs[i + 1].first);
            minMinorIndex.first = arrPairs[i].second;
            minMinorIndex.second = arrPairs[i + 1].second;
        }
    }
    // 注意的一点是 前x个元素和前y个元素和相近 表明x+1,...y之和为0 即索引中x...y-1之和为0
    // 且注意索引先后顺序 
    if(minMinorIndex.first < minMinorIndex.second)
    {
        result.first = minMinorIndex.first;
        result.second = minMinorIndex.second - 1;
    }
    else
    {
        result.second = minMinorIndex.first - 1;
        result.first = minMinorIndex.second;  
    }
    

    return result;
}

int main()
{
    int t[] = {31, 42, -14, 11, 32, -19};
    vector<int> arr(t, t + 6);
    pair<int, int> result = getRangeOfSubarrayCloseToZero(arr);

    cout << result.first <<"-"<< result.second;
}
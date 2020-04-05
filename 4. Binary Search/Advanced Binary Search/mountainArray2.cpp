#include<iostream>
#include<vector>
using namespace std;
/*
在具有多个波峰波谷的数组中返回任何一个波峰的索引即可 且数组首尾分别是上坡和下坡
显然这道题难以转化为前后的两类 ooxx
但是可以用二分的思想 每次减少一半的解空间
mid有四种状态 上坡 下坡 波峰 波谷
波峰时直接返回解 波谷时 两边都有解
上坡时 则保留右半部分  下坡时保留左半部分 都使得首上坡 尾下坡
剪枝核心是 上坡和下坡之间必有波峰
因此 mid若和首尾其中一个构成了上下坡关系就可以剪枝
*/
int searchPeak(vector<int> nums)
{
    int start = 0;                      //首元素处于上坡
    int end = nums.size() - 1;    //尾元素处于下坡

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;
        if(nums[mid - 1] < nums[mid] && nums[mid] < nums[mid + 1])      //处于上坡
        {
            start = mid;
        }
        else if (nums[mid - 1] > nums[mid] && nums[mid] > nums[mid + 1])//处于下坡
        {
            end = mid;
        }
        else if(nums[mid - 1] > nums[mid] && nums[mid] < nums[mid + 1]) //波谷
        {
            start = mid;            
        }
        else                                                            //波峰 
        {
            return mid;
        }
    }
    if(nums[start] < nums[end])
    {
        return end;
    }
    return start;
}
#include<iostream>
#include<vector>
using namespace std;

/*
给定一个有序数组和目标 找到这个目标 若不存在 则插入到相应的位置使得数组仍然有序
基本的二分框架在while部分做的是把范围缩小到两个 元素中 求解的核心在于while后的判断 并且不同题只需要改变while后的判断即可
这道题若while循环中没有找到 则在后序处理
首先考虑 目标数大小就是两个数中的一个 那么和模板相同 检查start和end即可
其次 若目标数本身小于start 则返回start 或大于end 则返回end+1 考虑这一点的原因是 二分模板start和end移动的核心是 [start, end]一定包含target 但这道题可能会出现超出的情况 因此特殊判断 
最后 若目标数介于start和end之间 则返回end 

*/

int searchInsertPos(vector<int> &nums, int target)
{
    if(nums.empty())
    {
        return -1;
    }
    int start = 0;
    int end = nums.size() - 1;

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;

        if(nums[mid] == target)
        {
            return mid;
        }
        else if(nums[mid] < target)
        {
            start = mid;
        }
        else 
        {
            end = mid;
        }
    }
    if(nums[start] >= target)
    {
        return start;
    }
    if(nums[end] == target)
    {
        return end;
    }
    if(nums[end] < target)
    {
        return end + 1;
    }
    return end;
}

int main()
{
    int test[] = {1,3,5,6};
    vector<int> nums(test, test + 4);

    for(int i = 0; i < 8; i++)
    {
        //cout << nums[i];
        cout << i << ":" << searchInsertPos(nums, i)<< endl;
    }
}
#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

/*
循环条件 
三个条件判断
三个游标更新
边界判断
*/

int findPostion(vector<int> nums, int target)
{
    if(nums.empty() || nums.size() == 0)
    {
        return -1;
    }
    int start = 0;
    int end = nums.size() - 1;


    while(start + 1 < end) // 应对找第一个/最后一个问题时 偏左运算导致[2, x]陷入死循环 start无法移动 也就无法结束start < end
    {
        int mid = start + start - end / 2; //F! 每次都会重新计算mid 声明写在里面即可 
        if(nums[mid] == target)
        {
            return mid;  // 如果是找最后一个target 就是start = mid 第一个是end = mid 
        } 
        if(nums[mid] > target)
        {
            end = mid;  // 避免 找第一个/最后一个问题中 mid+1/ mid-1会把唯一答案跳过 核心是 一定要[start , end]时时刻刻包含target 
        }
        if(nums[mid] < target)
        {
            start = mid;
        }
    }
    //二分法的正确思想是 循环是为了缩小范围 然后进行边界检查 即start 和end哪一个是最终答案 而不是在循环中就把答案算出来 
    if(nums[start] == target) //找第一个target 就先检查start 
    {
        return start;
    }
    if(nums[end] == target) //找最后一个target 就先检查end
    {
        return end;
    }
    return -1;
}








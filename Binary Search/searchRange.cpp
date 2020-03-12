#include<iostream>
#include<vector>
using namespace std;
/*
传入有重复元素的数组和目标 返回目标的左右边界
先求 第一个 再求最后一个 做两次二分搜索即可 
和查找元素的区别仅在于while中对 == 情况的处理 以及后序if判断的处理 
*/
vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> range(2, -1);
    if(nums.empty())
    {
        return range;
    }
    int start1 = 0;
    int end1 = nums.size() - 1;
    int start2 = 0;
    int end2 = nums.size() - 1;

    while(start1 + 1 < end1)
    {
        int mid1 = (start1 + end1) / 2;
        if(nums[mid1] >= target)
        {
            end1 = mid1;
        }
        if(nums[mid1] < target)
        {
            start1 = mid1;
        }
    }
    if(nums[start1] == target)
    {
        range[0] = start1;
    }
    if(nums[end1] == target)
    {
        range[0] = end1;
    }
    
    while(start2 + 1 < end2)
    {
        int mid2 = (start2 + end2) / 2;
        if(nums[mid2] > target)
        {
            end2 = mid2;
        }
        if(nums[mid2] <= target)
        {
            start2 = mid2;
        }
    }
    if(nums[end2] == target)
    {
        range[1] = end2;
    }
    if(nums[start2] == target)
    {
        range[1] = start2;
    }
    return range;
}

int main()
{
    int test[] = {5,7,7,8,8,8,8,10};
    vector<int> nums(test, test + 8);

    for(int i = 0; i < 12; i++)
    {
        vector<int> r = searchRange(nums, i);
        cout << i << ": [" << r[0] << "," << r[1] << "]" <<endl;
    }
}
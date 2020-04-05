#include<iostream>
#include<vector>
using namespace std;

/*
在一个无限长的数组中查找target
难点在于 无限长的数组意味着无法定位出end 从而没有区间可以进行二分
所以可以通过简便的方法快速定位到一个区间中 然后二分
【倍增法】定位区间的时间复杂度为logk（target索引为k） 在该区间内二分时间复杂度小于logk 总体时间复杂度为logk
*/
int searchInfiniteArr(vector<int>arr, int target)
{
    int jumpIndex = 1;
    while(arr[jumpIndex] < target)
    {
        jumpIndex *= 2;
    }
    int start = jumpIndex / 2;
    int end = jumpIndex;

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;
        if(arr[mid] < target)
        {
            start = mid;
        }
        else if(arr[mid]  > target)
        {
            end = mid;
        }
        else
        {
            return mid;
        }
    }
    if(arr[start] == target)
    {
        return start;
    }
    else
    {
        return end;
    }
    
}
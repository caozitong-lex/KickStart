#include<iostream>
#include<vector>
using namespace std;

/*
传入一个数组和目标 找到和目标最接近的值 
二分法即使找不到目标 也会把范围缩小到离目标最近的两个数 循环后比较即可
*/
int getClosestNumber(vector<int> arr, int target)
{
    sort(arr.begin(), arr.end());
    int start = 0;
    int end = arr.size() - 1;
    int mid;

    while(start + 1 < end)
    {
        mid = (start + end) / 2;
        if(arr[mid] > target)
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    if(abs(arr[start] - target) > abs(arr[end] - target))
    {
        return arr[end];
    }
    else
    {
        return arr[start];
    }
    return -1;
}

int main()
{
    int t[] = {4,3,7,1,8};
    vector<int> arr(t, t + 5);
    cout << getClosestNumber(arr, 6);
}
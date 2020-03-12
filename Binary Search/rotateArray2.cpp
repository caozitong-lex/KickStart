#include<iostream>
#include<vector>
using namespace std;
/*
仍然是旋转数组 但不是求最值 而是任意查找值 
无序的数组无法直接用二分 虽然可以分成前后两类 但所求的不是第一个/最后一个 的问题
第一种方法是求最值后 找到有序的两类 然后在有序部分二分查找
第二种方法则使用一次二分 使用去除一半解空间的思想
根据start 和end找到mid 比较mid和target的关系 找到target在哪一半中？ 关键是start-end要一直包含解
虽然这道题的数组不是有序的 但还是可以通过分情况讨论 归纳出解处于哪一半中 然后缩减解空间 这是核心 它比二分法多的地方在于 二分法的解的位置是易判断的 而旋转数组虽然无法直接得到 但还是可以比较出来
*/

int rotateArray(vector<int> nums, int target)
{
    int start = 0;
    int end = nums.size() - 1;

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;
        if(nums[mid] == target)
        {
            return mid;
        }
        //确定target在左右两边的哪一段
        //此处先确定mid和target都可以
        if(target >= nums[start])       //在左段    
        {
            //进一步确定mid和target的关系
            //其实只要mid在target左 则保留右边 反之保留左边 可以合并
            //从左到右的检查所有mid可能的位置
            if(nums[start] < nums[mid] && nums[mid] < target)      //mid在target左下方
            {
                start = mid;
            }
            else if(nums[mid] < nums[start] && nums[mid] < target)     //mid在target右下方
            {
                end = mid;
            }
            else if(nums[mid] > target)                                     //mid在target右上方
            {
                end = mid;
            }
        }
        else                            //在右段
        {
            //从左到右的检查所有mid可能的位置
            if (nums[mid] > target && nums[mid] > nums[start])      //左上方
            {
                start = mid;
            }     
            else if(nums[mid] < target)                             //mid在target左下方
            {
                start = mid;
            }
            else if(nums[mid] > target && nums[mid] < nums[start])  //右上方
            {
                end = mid;
            }   
        }
    }
    if(nums[start] == target)
    {
        return start;
    }
    if(nums[end] == target)
    {
        return end;
    }
    return -1;
}

int main()
{
    int test[] = {4,5,6,7,1,2,3};
    vector<int> nums(test, test + 7);

    cout << rotateArray(nums, 5);
}
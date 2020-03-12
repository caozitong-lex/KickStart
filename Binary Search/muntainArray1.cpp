#include<iostream>
#include<vector>
using namespace std;

/*
传入序列 序列先严格递增后严格递减 求最大值  如135 6 42
递增设为o 递减设为x 分类依据是递增/递减 通过和前/后一个数值比较即可

这道腿首先需要确定是找最后一个o还是第一个x
这道题中其实是同一个值  因此都可以
比如找第一个x 即使是123456 没有x
但是找到o后还是会向右找x 最后还是能找到最大值
找最后一个o同理 654321 会向左找o 也能找到最大值

需要注意的是：
若寻找最后一个o 则把8当作递增的o 那么判断分类时要和前一个比较 
若寻找第一个x 则把8当作递减的x 那么判断分类时要和后一个比较
这道题和旋转数组一样 分类标准需要仔细考虑 要根据 找最后一个o还是第一个x来定
*/
int searchMaxinMountain(vector<int> nums)
{
    int start = 0;
    int end = nums.size() - 1;

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;
        if(nums[mid] > nums[mid - 1])   //递增 
        {
            start = mid;                //找最后一个o
        }
        else                            //递减
        {
            end = mid;
        }
    }
    if(nums[end] > nums[start])
    {
        return nums[end];
    }
    return nums[start];
}

int main()
{
    int test[5] = {1,3,5,2,1};
    vector<int> nums(test, test + 5);
    cout << searchMaxinMountain(nums);
}
#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
对于问题无法二分查找的 可以转化为ooxx问题 

标准二分法中 数组元素和target的关系有三种情况 > < = target 我们需要返回 = target的
使用二分的前提是 排序。因为通过比较mid和target 我们可以缩小解范围 

更进一步的 对于有多个等于target 我们希望返回第一个/最后一个 
使用二分的前提是 排序+是否相同
排序是找到等于target的前提  但找到target之后 第二阶段继续找到第一个/最后一个 则不需要排序 依赖的是二元相等关系
比如 45177794 当找到第二个7时 若要找到第一个7 只需要求mid比较nums[mid]是否等于7即可
若不等于7 说明前面的解空间被舍弃 若等于7 则后面的解空间被舍弃

ooxx问题中 数组虽然是无序的 但被分为两类 满足和target大小关系的 和 不满足的 
这使得二分的前提被满足：排序 + 是否相同
满足和target大小关系的 和 不满足的 两类之间是有排序关系的 因此可以轻松找到满足关系的元素
之后就可以根据相同关系找到第一个/最后一个

561234
ooxxxx 
找最小值就是找第一个x target为nums[size - 1]（最后一个x） 小于等于target为x 大于target为o
找最大值就是找最后一个o target为nums[0](第一个x) 小于target为x ≥target为o
区别的原因是极端情况123456 xxxxx
此时最小值i是找第一个x 所以target若为nums[0] 且小于nums[0]（1）为x 显然所有都是o 它会一直试图在右边寻找x 显然右边都是错误的答案
这会导致ooxx的第一步——找到任何一个满足要求的类 就失败

找最小值 在分类后 我们首先需要找到任何一个x 显然o在前 x在后 因此可以二分得到
之后找到第一个x 通过相同关系即可 
*/
int findMin(vector<int> nums)
{
    int target = nums[nums.size() - 1];
    int start = 0;
    int end = nums.size() -  1;

    while(start + 1 < end)
    {
        int mid = (start + end) / 2;
        if(nums[mid] <= target) //是x
        {
            end = mid;
        }
        else
        {
            start = mid;
        }
    }
    if(nums[start] <= target)
    {
        return nums[start];
    }
    return nums[end];
}
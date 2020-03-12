#include<iostream>
#include<vector>
using namespace std;
/*
求两个数组的交集
0. 暴力方法：逐个取出一个数组的元素 在另一个数组中遍历查找 时间复杂度为 m*n
1. 使用set 或哈希 存储一个数组的元素 然后遍历另一个数组的元素检查是否在其中即可 时间复杂度为构造哈希的m + 遍历查找的n 空间复杂度为m
2. 将一个数组排序 遍历另一个数组二分检查是否在其中即可 时间复杂度为排序的mlogm + n次二分查找的nlogm 空间复杂度为1
3. 将两个数组排序 然后像合并有序数组那样 逐个取出二者的头比较是否相等 时间复杂度为排序时间mlogm+nlogn加上遍历时间m+n 空间复杂度为1

--> 比较0/1/2这三种方法 可以发现 和twosum类似 双重遍历两个数组 两两取出（在这里取出比较大小 twosum中取出求和比较和）有三种方式实现 时空复杂度为：
    · 双重for循环     O(n * m)              O(1) 从n数组中取一个 遍历m数组元素两两配对(m)
    · 先排序后二分 O((nlogm + mlogm)        O(1)  从n数组中取一个 二分遍历m数组元素两两配对(logm) 前提是m数组已排序
    · 哈希           O(n * 1 + m)          O(m) 从n数组中取一个  哈希遍历m数组元素两辆配对(1) 前提是m数组已哈希

这里实现第三种方法 类归并的思路
*/
vector<int> findIntersection(vector<int> arr1, vector<int> arr2)
{
    vector<int> intersection;
    int ptr1 = 0;
    int ptr2 = 0;
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());

    while(ptr1 < arr1.size() && ptr2 < arr2.size())
    {
        if(arr1[ptr1] < arr2[ptr2])
        {
            ptr1 ++;
        }
        else if(arr1[ptr1] == arr2[ptr2])
        {
            intersection.push_back(arr1[ptr1]);
            ptr1++;
            ptr2++;
        }
        else
        {
            ptr2 ++;
        }
    }
    return intersection;

}


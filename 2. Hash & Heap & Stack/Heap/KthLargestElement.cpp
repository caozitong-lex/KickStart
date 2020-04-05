#include<queue>
#include<vector>
#include<iostream>
using namespace std;

class Solution
{
    //给定数组和序号k 找到 第k大的数
    //这道题还可以改编为 实现一个数据结构 具有add操作和topk操作 
    //这种数据结构题 k是在数据结构创建时确定的 也就是固定的
public:
    int findKthLargest(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int> >smallHeap;
        for(int i = 0; i < k; i++) //先填充大小为k的堆
        {
            smallHeap.push(nums[i]);
        }
        for(int i = k; i < nums.size(); i++) //比较后加入
        {
            if (nums[i] > smallHeap.top())
            {
                smallHeap.pop();
                smallHeap.push(nums[i]);
            }
        }
        return smallHeap.top();
    }
};
int main()
{
    vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(4);

    Solution s;
    int k = 3;
    int result = s.findKthLargest(nums, k);
    cout << result << endl;

    system("out");
    return 0;
}

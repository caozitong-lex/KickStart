#include<iostream>
#include<vector>
using namespace std;

void splitArrayByK(vector<int> &nums, int k)
// 给定数组nums和分割线k 把小于k的数放在数组左部 大于k的数放在数组右部
// 左右双指针解决分类 可以有其他变种分类 如正负数 大小写 奇偶数 时间复杂度为n
// 思路就是让左指针停在>k 即应该到右边的数字上 右指针停在<k的数字上 二者都停时就交换 
{
    int leftPtr = 0;
    int rightPtr = nums.size() - 1;

    while(leftPtr < rightPtr)
    {
        //cout<<"left= "<< nums[leftPtr] <<"/ right= "<<nums[rightPtr]<<endl;
        // 左右指针有几种情况
        // 1. 左换右不换 2. 左不换右换 3. 左右都换 4. 左右都不换
        // 其实 只有满足3条件时 双指针才完成交换操作 其他时刻 都在移动到目标的过程 找到相应位置后 停止 等待交换关系的达成
        // 所以双指针的过程：找到目标 —— 停止 —— 等待关系 —— 操作
        // 在同向双指针中 一个作为哨兵节点 完成上述步骤 一个作为探索节点 用来导致关系的发生 
        if(nums[leftPtr] >= k && nums[rightPtr] < k )
        {
            int temp = nums[leftPtr];
            nums[leftPtr] = nums[rightPtr];
            nums[rightPtr] = temp;
            leftPtr++;
            rightPtr--;
            continue;
        }
        if (nums[leftPtr] < k)
        {
            leftPtr ++;
        }
        if (nums[rightPtr] >= k)
        {
            rightPtr --;
        }
    }
}

void threePartition (vector<int> &nums)
//给定数组 元素有三种0 1 2 要求把0 1 2分别放在数组的左 中 右三个部分
//第一种思路是双指针分区两次  第一次分为0|12 第二次分为 0 1 2 时间复杂度仍然是n
//第二种思路仍然是使用双指针 两个指针把整个区间正好分成三份 在left左边的是0 right右边的是2 
// 还需要一个扫描指针在左右指针之间检查 扫描到0或2时 和双指针交换 把0和2冒泡到两边 
// 这道题中 mid指针作为探索指针 左右指针作为哨兵指针 等待关系的发生 关系的发生可以使得左右指针永远为对应的值 0 / 2
{
    int leftPtr = 0;
    int rightPtr = nums.size() - 1;
    int scanner = 1;
    while(scanner <= rightPtr) //scanner在左右指针之间扫描 确保scanner永远指向1
    {
        if (nums[scanner] == 0) //扫描到0 应该放到左边 和左指针交换
        {
            int temp = nums[scanner];
            nums[scanner] = nums[leftPtr];
            nums[leftPtr] = temp;

            leftPtr++;
        }
        else if(nums[scanner] ==  2) //扫描到2 应该放到右边 和右指针交换
        {
            int temp = nums[scanner];
            nums[scanner] = nums[rightPtr];
            nums[rightPtr] = temp;

            rightPtr--; 
        }
        if(nums[scanner] == 1) //虽然scanner把0 2放到左右边 左右指针可以移动 但左右边换给scanner的则不确定 因此scanner只有扫到1时才移动
        {
            scanner ++;
        }
    }
} 


int main()
{
    vector<int> n;
    n.push_back(2);
    n.push_back(2);
    n.push_back(1);
    n.push_back(1);
    n.push_back(0);
    n.push_back(1);
    n.push_back(2);

    threePartition(n); 

    for(int i = 0;  i < n.size(); i++)
    {
        cout<<n[i];
    }
}
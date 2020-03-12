#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;




//窗口和 传入一个数组和窗口大小 计算所有窗口大小长度的子数组和
// 暴力法的时间复杂度是n^2 可以容易优化到n
// for循环中的循环变量不要用双指针变量 双指针的增减不要在for循环的增减中实现 会造成功能交叉 for循环的作用是循环一个计数器 如果要移动指针 可以使用指针+计数器的方式
 
vector<int> windowSum (vector<int> nums, int windowSize)
{
    vector<int> windowSum;

    //考虑corner case 鲁棒性
    if(nums.size() == 0 || nums.size() < windowSize || windowSize == 0)
    {
        return windowSum;
    }

    int leftPtr = 0;
    int rightPtr = windowSize - 1;
    int currentSum = 0;

    // 第一个窗口数组的和
    // 通常for循环使用 小于 是因为循环的是次数 或在数组中循环的是个数 因为从0开始 所以终点需要减一 否则应该是写 int i = 1; i <= 5; i++  
    // 而窗口有明确的起始点和终点 就是数组中的索引 而不是个数 从left到right 不需要修改
    for(int i = leftPtr; i <= windowSize - 1; i++)
    {
        currentSum += nums[i];
    }
    windowSum.push_back(currentSum);

    // 以后每个窗口和 都是第一个窗口数组和 加上下一个元素 减去第一个元素
    for (int i = windowSize; i < nums.size(); i++ )  //i的循环次数 表明接下来的移动次数 
    {
        currentSum += nums[i];
        currentSum -= nums[i - windowSize];
        windowSum.push_back(currentSum);
    }
    return windowSum;
}

// 移动0和统计非重复数的共同性质是 左指针作为哨兵指针 负责检测特定元素并静止 在满足一定条件下解除静止 右指针作为探索指针 负责和左指针形成特定条件 所以要思考 静止条件/目标 - 解除条件/关系 - 解除后如何移动
// 比如移动0中 左指针负责检测0 当满足交换时才解除静止进行交换 而右指针负责形成交换关系 否则一直继续移动
// 统计非重复数中 左指针负责检测第一次遇到的值 右指针探索不同的值 当形成不等关系时 左指针解除静止跳到另一个初次遇到的值
// 给定一个数组 把数组中所有的0都移到数组末尾 保持其他元素的相对位置
void moveZeros (vector<int> &nums) //数组名不用引用 本身代表指针
{
    //不改变相对位置的移动 -> 冒泡思想 左指针负责找到0 右指针负责找到非0 进行交换 
    //左右指针从0出发 右指针保持右移 而左指针扫描到0就和非零右指针交换 否则也右移 若左指针准备交换时右指针也为0 则左指针暂停等右指针扫描到非0
    int leftPtr = 0;
    int rightPtr = 0;
    for(int i = 0; i < nums.size(); i++)    
    {
        rightPtr ++ ; //右指针保持右移 
        //接下来判断左指针的移动

        if (nums[leftPtr] == 0) //左指针指向0就交换
        {
            if(nums[rightPtr] == 0) //无法交换 
            {
                continue;
            }
            //交换 
            int temp = nums[leftPtr];
            nums[leftPtr] = nums[rightPtr];
            nums[rightPtr] = temp;
            leftPtr++;
        }
        else
        {
            leftPtr ++ ; //左指针没有指向0 则继续移动左指针
        }
    }
}

//给定一个数组 统计非重复元素的个数
int numOfNonDuplication(vector<int> &nums)
{
    //考虑暴力法 相当于制作一个访问哈希 在把元素放入哈希中时 检查是否存在 最后统计哈希中放了多少个数即可 最坏情况下 数组每个元素都不一样 那么每次放入都要检查所有放入的数据 时间复杂度是n^2
    //那么 另一个思路关键是排序 排序后的重复元素总是挨在一起 这样就可以方便检查
    //和去0操作一样 右指针始终右移 左指针则时刻跟进右指针的位置 当左指针和右指针的值相同时 左指针停下 不同则移动 
    int leftPtr = 0;
    int rightPtr = 1;
    int num = 0;
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < nums.size(); i++)
    {
        if(nums[leftPtr] == nums[rightPtr])
        {
            rightPtr++;
        }
        else{
            leftPtr = rightPtr;
            rightPtr++;
            num++;
        }
    }
    return num;
}


int main()
{
    vector<int> nums;
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(4);
    nums.push_back(4);
    nums.push_back(0);
    nums.push_back(0);
    nums.push_back(4);
    nums.push_back(4);
    //vector<int> a = windowSum(nums, 4);
    //cout << a[0];

    //moveZeros(nums);
    int a = numOfNonDuplication(nums);
    cout << a;
    //for(int i = 0; i<nums.size(); i++)
    //{
    //    cout<<nums[i]<<endl;
    //}
    system("out");
    return 0;
}


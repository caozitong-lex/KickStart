#include <iostream>
#include <vector>
#include<algorithm>
#include <map>
using namespace std;

//twosum问题 关注三个细节 重复检查（确定顺序） 多组（扫描完整） 重复数字（记录或跳过 ）

//给定数组以及目标值 找到数组中两个和为目标值的数 可能有多组 数组中可能有重复元素
//多组->从头扫描到尾 逐一检查  重复->哈希更新 使重复的找不到  重复检查-> 确定顺序 右边执行 
//三种算法： 1. 双重for循环 2.排序后for循环+二分 3.for+哈希 
vector< pair<int, int> > twoSum(vector<int> nums, int target)
{
    vector< pair<int, int> > pairs;
    pair<int, int> xyPair;
    //创建一个哈希表 把每个值作为索引 索引作为值 这样通过值可以找到索引
    // 这个步骤需要消耗n的空间复杂度 时间复杂度也是n 但不影响总体时间复杂度
    map<int, int> hash;
    for (int i = 0; i < nums.size(); i++)
    {
        hash[nums[i]] = i;
    }

    for (int i = 0; i < nums.size(); i++)
    {
        int correspondence = target - nums[i];
        if (hash[correspondence] != -1 && i < hash[correspondence]) //后者条件是为避免 1,3 的情况下 先得到1+3 后得到3+1 所以规定 前后索引关系
        {
            hash[correspondence] = -1; //更新哈希表 避免重复数字 比如 2 3 2 4... 找到2+4=6后 第二个2不应该再计算 因此哈希设置为-1 让它找不到4
            xyPair = make_pair(nums[i], correspondence);
            pairs.push_back(xyPair); // 这个加入答案的操作一定要放在判断内 和答案生成放在一起 否则会一直循环加入解
        }
    }
    return pairs;
}

// 给定一个排序数组 继续解决two sum问题 空间要求为常数级别 即不用哈希表代替for
// 多组->扫描全部 重复数字->排序后while循环跳过重复 重复检查-> left < right
vector< pair<int, int> > twoSumWithSorted(vector<int> nums, int target)
{
    //第一种方式是双循环 使用二分查找logn代替内层for循环 时间复杂度为nlogn
    //第二种是使用头尾双指针(排序)代替双循环 前提是排序 时间复杂度为nlogn + n -> nlogn 
    // 更tricky一些 若头尾和大于target 说明右指针过大 一定不是解  因为和最小的数相加都大于target
    //同理 头尾和小于target 说明左指针过小 右移
    int leftPtr = 0;
    int rightPtr = nums.size() - 1;
    vector< pair<int, int> > pairs;
    pair<int, int> xyPair;
    while (leftPtr < rightPtr)  //一直到两指针相遇到同一个位置
    {
        if ((nums[leftPtr] + nums[rightPtr]) > target)
        {
            while(nums[rightPtr] == nums[rightPtr - 1]) //去除重复 如果检测到 2 2 2 那么指针 一直移动 直到非2时
            {
                rightPtr --;    
            }
            //循环结束时 此时移动到重复元素的最后一个 再移动一次即可到达非重复元素
            rightPtr --;
            
        }
        else if (nums[leftPtr] + nums[rightPtr] < target)
        {
            
            while(nums[leftPtr] == nums[leftPtr + 1]) //去除重复 如果检测到 2 2 2 那么指针 一直移动 直到非2时
            {
                leftPtr++;
            }
            leftPtr++;
        }
        else
        {
            xyPair = make_pair(nums[leftPtr], nums[rightPtr]);
            pairs.push_back(xyPair);

            while(nums[rightPtr] == nums[rightPtr - 1]) 
            {
                rightPtr --;
            }
            while(nums[leftPtr] == nums[leftPtr + 1]) 
            {
                leftPtr++;
            }
            rightPtr--;
            leftPtr++;
        }
    }
    return pairs;
}

vector< vector<int> > threeSum(vector<int> nums)
// 给定一个数组 求出和为0的三个数字 
// 两种方案 双循环+哈希表- n^2 和 排序后 一循环+双指针- nlogn+ n^2 - n^2 
// 双指针的思路是 选定a不动 在a右边的数中进行双指针 b+c = -a
// 多组->扫描全部 重复数字->排序后while跳过重复 重复检查->内层循环在外层循环的右边执行
{
    vector< vector<int> >results;
    sort(nums.begin(), nums.end());

    for (int a = 0; a < nums.size()-2; a++) //每次定下一个a 都是一次双指针过程 因此双指针定义在循环内 循环次数-2 因为三个指针不能重合 两个位置被占据
    {
        int b = a + 1;    //避免指针撞车 每次双指针 不需要把bc设定在数组头尾 由于a从最左边开始 因此bc指针无需检查a左边的情况 只需要在a右边找即可 
        //双指针循环充当的角色和暴力法的一次循环相似 但它能找到两个值 暴力法的内层循环都在外层循环变量的右侧进行避免重复 双指针也从外层循环的右边开始
        int c = nums.size() - 1;    

        while(b < c)
        {
            if(nums[b] + nums[c] > -nums[a])
            {
                while(nums[c-1] == nums[c])
                {
                    c--;
                }
                c--;
            }
            else if (nums[b] + nums[c] < - nums[a])
            {
                while(nums[b+1] == nums[b])
                {
                    b++;
                }
                b++;
            }
            else
            {
                vector< int > tripair; //每次循环都会生成一个解 因此解要在循环内声明 确保每次生成新的解
                tripair.push_back(nums[a]);
                tripair.push_back(nums[b]);
                tripair.push_back(nums[c]);
                results.push_back(tripair); //生成解后立刻加入 而不是放在循环外 

                while(nums[c-1] == nums[c])
                {
                    c--;
                }
                c--;
                while(nums[b+1] == nums[b])
                {
                    b++;
                }
                b++;
            } 
        }
    }
    return results;
}

int triangleCount(vector<int> nums)
//给定无重复元素的数组 找到所有能组成三角形的三元组的个数
//基本思路同threeSum 组成三角形的核心是a+b > c （a<b<c）因此固定c 在左边的数中双指针求ab 其实就是求满足a+b>c的所有元组 整体思路一致 只有细节不同 
//注意首先数组没有重复数字 且这道题是找出所有可能的三元组 不是利用这个数组的数 最多能组成多少个三角形

{
    int numOfTriangle = 0;
    sort(nums.begin(), nums.end());

    for(int c = 2; c < nums.size(); c++)    //固定的是c 最右
    {
        int a = 0;              
        int b = c - 1;
        while(a < b)        //a b在c左边变化 
        {
            if (nums[a] + nums[b] <= nums[c])
            //  1 4 5 6 7 8 其中a b c指向3 7 8 且1+7 = 8 那接下来a b怎么变？借助于3sum问题 显然是a++ 
            {
                a++;
            } 
            else //注意if-if和if-else if中的更新 会应用到第二个if中 而不会应用到elseif中 注意ifelse是并列 ifif是顺序关系
            {
                // 4 5 6 7 8 其中a b c指向4 7 8 且4+7 > 8 那接下来a b怎么变？借助于3sum问题 显然就是b-- 
                // 关键在于统计三角形数量 如果4+7 > 8 事实上5或6 + 7都符合要求 因此num不能只++
                // twosum问题中 如果题目改为 找到两个数满足 > target 那么如何改进？
                // 4 5 6 7 8 假设target是10 
                // 首尾为4 8 > 10 满足 那么理论上 8-> 7即可 最后移到4+5 > 8 那么为什么会遗漏？
                // 因为在等于的问题中 若找到a+b = target 那么此时和a满足要求的b只有一个 b也同理 
                // 而>的问题中 若 a+b > target 和b满足要求的a有很多 a后面的几个其实都满足 而和a满足要求的b只有一个 b往左移后能否满足要求是不确定的
                // 所以 a+b > target 找到的是一组a 而不是一个a
                numOfTriangle += (b-a);   
                b--;
            }
        }
    }
    return numOfTriangle;
}

int twoSumClosest(vector<int> nums, int target)
// 给定数组 找到最接近目标的两个数的和 数组中可能有重复元素
// 因为找不到==的情况 所以只有>和<两种情况的指针调节 双指针根据< 和>两种情况的调节就是为了让两个数之和更接近于target
// 双指针的基础上 维护最小差值和两个数和即可 
{
    int minDist = 10000;
    int closestSum;
    int leftPtr = 0;
    int rightPtr = nums.size()-1;  

    sort(nums.begin(), nums.end());
    while (leftPtr < rightPtr)
    {
        int currentDist = abs(nums[leftPtr] + nums[rightPtr] - target); //距离是差的绝对值
        if (currentDist < minDist)
        {
            minDist = currentDist;
            closestSum = nums[leftPtr] + nums[rightPtr];
        }
        if(nums[leftPtr] + nums[rightPtr] > target)
        {
            while( nums[rightPtr - 1] == nums[rightPtr] )
            {
                rightPtr --;
            }
            rightPtr --;
        }
        else
        {
            while( nums[leftPtr + 1] == nums[rightPtr] )
            {
                leftPtr ++;
            }
            leftPtr ++;
        }
    }
    return closestSum;
}

 
int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(10);
    nums.push_back(4);
    //nums.push_back(7);
    //nums.push_back(4);
    int n = twoSumClosest(nums,7);
    cout << "sum: " << n << endl;

    return 0;
    vector< vector<int> > r;
    r = threeSum(nums);
    for (int i = 0; i < r.size(); i++)
    {
        for(int j = 0; j < r[i].size(); j++)
        {
            cout<<r[i][j]<< " | ";
        }   
        cout << endl;
    }
}

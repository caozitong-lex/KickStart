#include<queue>
#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;

class Solution
{
//丑数指因子只包含 2 3 5 的数 如 4 6 15 30 要求找到第k个丑数 1视作第一个丑数
//如果是从小到大生成丑数怎么生成 第一个是1 那么显然下三个丑数就是 1*2 1*3 1*5
//继续则是这三个丑数每个都乘以 2 3 5 那么以此循环下去 每个得到的数的因子一定只有 2 3 5
//那么为了确保大小顺序 将分解的数放入堆中 就可以自动维护大小顺序 取n次 就是得到第n小的数 
//从引子数开始 取数 - 检查 - 弹出 - 分解 的过程和BFS很相似 学习这种每次取一个数 弹出 分解新的数入队的逐个处理的核心思想

public:
    int NthUglyNumber(int k)
    {
        //堆用来分解+维护大小关系 map用来用作哈希避免重复分解 
        priority_queue< int, vector<int>, greater<int> > smallHeap;
        map<int, bool> hashMap;
        //堆和哈希的push是绑定操作 首先将第一个丑数加入堆
        int uglyNumber;
        smallHeap.push(1);
        hashMap[1] = 1;
        //k次循环 每次取出一个丑数进行 取数-输出/记录-弹出-分解-检查-入队 的工作 和BFS类似
        for(int i = 0; i < k; i++)
        {
            //取头-处理-弹出
            uglyNumber = smallHeap.top();
            //cout << i << ":" << uglyNumber << endl;
            smallHeap.pop();
            
            //分解-检查-入队 和图相似 队列和哈希的操作绑定
            vector<int> factor;
            factor.push_back(2);
            factor.push_back(3);
            factor.push_back(5);
            for(int i = 0; i < 3; i++)
            {
                if(hashMap[uglyNumber * factor[i]] == 0)
                {
                    smallHeap.push(uglyNumber * factor[i]);
                    hashMap[uglyNumber * factor[i]] = 1;
                }
            }
        }
        return uglyNumber;
    }

    //注意到 其实不需要用堆来维护大小 set本身就是有序不重合数组 其实可以只用set来实现 
    int NthUglyNumberBySet(int k)
    {
        set<int> hashMap;
        int uglyNumber;
        hashMap.insert(1);
        /*
        set<int>::iterator it;
        for(it = hashMap.begin(); it != hashMap.end(); it ++)
        {
            cout << *it << endl;
        }
        cout << "--------";
        */
        for(int i = 0; i < k; i++)
        {
            uglyNumber = *hashMap.begin();  //取头 
            hashMap.erase(uglyNumber);      //出栈

            hashMap.insert(uglyNumber * 2); //分解入队 （不需要检查 因为set自带无重复属性）
            hashMap.insert(uglyNumber * 3);
            hashMap.insert(uglyNumber * 5);
        }
        return uglyNumber;
    }
};

int main()
{
    Solution s;

    int k = 10;
    int result = s.NthUglyNumber(k);
    cout << result;
    system("out");
    return 0;
}
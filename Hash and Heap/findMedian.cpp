#include<iostream>
#include<queue>
using namespace std;
/*
设计一个数据结构 其中有两个方法 添加元素和返回中位数
这是一个构造型问题
最简单的思路是用数组实现 添加元素和数组相同 时间复杂度为1 返回中位数则对数组排序后返回中间值即可 但时间复杂度为nlogn
改进方法则是在添加元素时通过遍历插入来维护排序 时间复杂度为n 返回中位数直接返回即可 时间复杂度为1
第二个思路是堆实现（堆的特点是堆顶是最值） 中位数意味着数组可以分成两组 那么使用小数构建最大堆 大数构建最小堆 返回中位数只需要对两个堆顶处理即可
那么在添加元素时通过多情况判断 来维护两个堆规模大小相等 并且小数组 恒小于 大数组 即可 时间复杂度同堆的插入 为logn 返回中位数则判断堆规模直接返回即可 时间复杂度为1
第三个思路是搜索树 （搜索树的特性是左子节点<根<右子节点） 插入时维护这棵树的左右子树规模即可 根节点就是中位数
*/
class findMedian
{
private:
    priority_queue< int, vector<int>, greater<int> > smallHeap;
    priority_queue< int, vector<int>, less<int> > bigHeap;
public:
    findMedian(){}
    void addNum(int x)
    {
        if(bigHeap.size() > smallHeap.size())   //若小数堆数字多 则添加到大数堆中
        {
            if(x < smallHeap.top())             //若不够格加入大数堆 则和小数堆顶换位置
            {
                smallHeap.push(bigHeap.top());
                bigHeap.pop();
                bigHeap.push(x);
            }
            else                                
            {
                smallHeap.push(x);
            }  
        }
        else                                    //若大数堆数字多 则添加到小数堆中
        {   
            if(x > bigHeap.top())                //若不够格加入小数堆 则和大数堆顶换位置
            {
                bigHeap.push(smallHeap.top());
                smallHeap.pop();
                smallHeap.push(x);
            }
            else                                
            {
                bigHeap.push(x);
            }  
        }
    }
    double getMedian()
    {
        if(smallHeap.size() == bigHeap.size())
        {
            return (smallHeap.top() + bigHeap.top()) / 2;
        }
        else if (smallHeap.size() > bigHeap.size())
        {
            return smallHeap.top();
        }
        else
        {
            return bigHeap.top();
        }
    }
};
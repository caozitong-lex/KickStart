#include<queue>
#include<iostream>
using namespace std;
//若加入堆的是自定义类/结构体 重载比较运算符：https://blog.csdn.net/bat67/article/details/77585312
// 优先级队列属于queue 所以只有push和pop 以及top （queue中是front stack是top） 不能下标赋值 下标赋值只用于vector和map
// 堆具有O(logn)的add和remove  O(1)的找最值 堆和优先级队列的区别是删除复杂度 优先级队列是n而不是1  因为优先级队列使用了for循环
int main()
{
    priority_queue<int> default_bigHeap;    //默认构造最大堆
    priority_queue<int, vector<int>, greater<int> > smallHeap; //构造最小堆 
    priority_queue<int, vector<int>, less<int> > bigHeap; //构造最大堆

    int arr[] = {6, 10, 1, 7, 99, 4, 33};
    for(int i = 0; i < 7; i++)
    {
        bigHeap.push(arr[i]);
    }
    cout << "Top of the heap is :" << bigHeap.top() << endl;
    cout << "Size of the heap is: " << bigHeap.size() << endl;

    bigHeap.push(1000);
    cout << "Now, Top of the heap is:" << bigHeap.top()  << endl;

    for(int i = 0; i < 3; i++)
    {
        bigHeap.pop();
    }
    cout << "Now, top of the heap is:" << bigHeap.top() << endl;
    cout << "Now, size of the heap is: " << bigHeap.size() << endl;
    
    system("out");
    return 0;


}
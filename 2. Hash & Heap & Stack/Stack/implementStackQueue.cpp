#include<iostream>
#include<queue>
#include<stack>
#include<vector>
using namespace std;
// 这组题有两个核心 栈和队列的区别：新元素离出口的关系 以及 设计数据结构操作和设计普通函数操作的区别：数据结构操作是迭代式的 不需要一次性对所有元素修改
/*
设计一个栈类 完成基本操作 栈的内部数据存储结构为队列 
队列和栈的区别仅仅在于出栈顺序不同 也就是内部元素的顺序 和 出口的关系不同 栈中新元素离出口更近 队列中则更远
那么为了构造先进后出的栈 我们只要构造队列时 把后进的元素放到队列头部出口即可
那么怎么把后进的元素放到队列头部呢？
即每次利用另一个队列  把后进的元素先放到头部 再将原队列中的元素依次放入辅助队列 最后辅助队列依次放入原队列即可 是一种折腾转移操作
这里很关键的思想是 我们并不是把一个现成的存在元素的队列直接改造成栈 将元素顺序全部改变 而是构造一个操作 如果我们从第一个元素就开始这样做 之后形成的队列就会有栈的顺序
*/
class myStack
{
private:
    vector<int> stackByQueue;
public:
    myStack(){}
    void push(int x)
    {
        vector<int> helper_Queue;
        helper_Queue.push_back(x);
        
        while(!stackByQueue.empty())
        {
            helper_Queue.push_back(stackByQueue.front());
            stackByQueue.pop_back();
        }
        
        while(!helper_Queue.empty())
        {
            stackByQueue.push_back(helper_Queue.front());
            helper_Queue.pop_back();
        }
    }
    int pop()
    {
        int top = stackByQueue.front();
        stackByQueue.pop_back();
        return top;
    }
    int top()
    {
        return stackByQueue.front();
    }
    bool empty()
    {
        return stackByQueue.empty();
    }
};
/*
设计一个队列类 使用栈数组
和上一题的思想类似 关键在于新元素离出口的远近
区别是 从队列pop到另一个队列中 元素顺序不变 因此想要新元素离出口近 就在辅助队列中把新元素先放到出口处 然后再放入旧元素 再捣腾回来 顺序不变
从栈pop到另一个栈中 元素顺序相反 因此想要新元素离出口远 要把新元素放到离出口近的地方 先把旧元素放到离出口远的地方 这样栈元素倒腾 顺序相反
*/
class myQueue
{
private:
    stack<int> queueByStack;
public:
    myQueue(){}
    void push(int x)
    {
        stack<int> queue_helper;
        while(!queueByStack.empty())
        {
            queue_helper.push(queueByStack.top());
            queueByStack.pop();
        }
        queue_helper.push(x);
        while(!queue_helper.empty())
        {
            queueByStack.push(queue_helper.top());
            queue_helper.pop();
        }
    }
    int pop()
    {
        int top = queueByStack.top();
        queueByStack.pop();
        return top;
    }
    int peek()
    {
        return queueByStack.top();
    }
    bool empty()
    {
        return queueByStack.empty();
    }
};
/*
设计一个栈 除了最基本的入栈出栈栈顶 还要返回最小元素 操作时间复杂度为1
如果要求返回最小元素的时间复杂度为1 显然无法通过 一次性检查最小值来实现 遍历检查栈元素的时间复杂度为n
因此 就要利用构造型方法的特点 -> 维护最小值
用一个值可以维护吗？如果一直向栈中push元素 看起来是可以的 只要不断比较更新最小值即可
但问题是pop元素时 假如最小值元素被pop出去 此时最小值是原本的次小值 而一个值无法记录
因此 使用栈来记录栈在每个状态下的最小值 并且栈的pop有回溯的特点（栈状态指 栈中元素布局状态）
每当push一个元素 都在最小值栈中加入当前的最小值 每当pop一个元素 最小值栈只需要pop就可以回到上一个状态下最小值情况 
*/
class minStack
{
private:
    stack<int> myStack;
    stack<int> min;
public:
    minStack(){}
    void push(int x)
    {
        myStack.push(x);
        if(min.empty() || x < min.top())    //若新元素足够小 则记录当前状态 最小值为新元素值
        {
            min.push(x);
        }
        if(x > min.top())   //若新元素不够小 则记录当前状态 最小值仍然是原本的最小值
        {
            min.push(min.top());
        }
    }
    void pop()
    {
        myStack.pop();
        min.pop();
    }
    int top()
    {
        return myStack.top();
    }
    int getMin()
    {
        return min.top();
    }
};

int main()
{
    minStack s;
    s.push(0);
    cout << s.getMin();
    s.push(-2);
    cout << s.getMin();
    s.push(2);
    cout << s.getMin();
    s.push(-3);
    cout << s.getMin();
    s.pop();
    cout << s.getMin();
}


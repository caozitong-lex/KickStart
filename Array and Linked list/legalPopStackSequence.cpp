#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;
/*
检查合法出栈序列 将1-n的数字序列按顺序依次入栈 可以随时出栈或继续入栈 传入一个出栈序列 检查是否合法
思路1 是考虑出栈序列的特征 显然 当一个大数字出现在出栈序列 这意味着前面的小数字理应已经出栈 若未出栈 则都在栈中停留 那么比它小的数字的出栈顺序一定是逆序的 也就是大的在前 小的在后 
因此可以检查出栈序列每个数字后的序列 比它小的数字顺序是否合法 是否保持了前大后小的顺序 这种实现时间复杂度为 n^2 
思路2 模拟出栈过程 既然题目检查出栈是否合理  那我们就直接模拟这个顺序 看看最后是否能顺利出栈即可  
我们建立一个模拟栈 然后逐个将元素入栈 然后 只要栈顶和出栈序列队顶相同 就表明此时应该出栈 因此进行出栈操作  
最终若模拟栈为空 表明所有元素成功出栈 也就是说出栈序列是正确的
*/

bool checkValidOrder(queue<int> &order)
{
    stack<int> simulaStack;
    int length = order.size();

    for(int i = 1; i <= length; i++)
    {
        simulaStack.push(i);    //每次插入一个元素 但出栈的次数是不确定的 出栈时机取决于条件：栈顶和队顶  因此用while循环
        while(!simulaStack.empty() && simulaStack.top()  == order.front())  //注意连续出栈的情况 
        {
            simulaStack.pop();
            order.pop();
        }
    }
    if(simulaStack.empty())
    {
        return true;
    }
    return false;
}
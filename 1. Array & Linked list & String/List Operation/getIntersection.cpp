#include<iostream>
#include<vector>
using namespace std;

/*
传入两个链表头节点 返回第一个交叉节点指针
第一种方案是暴力 第一个链表固定 第二条链表逐个和第一条链表所有元素比较 显然这是  m*n的时间复杂度
或者将第一个链表放入哈希 第二条链表逐个在哈希中查找 时间复杂度都相同 
第二种方案是整体考虑链表的结构特点 显然比较链表长度 让两个链表从距离交点相同的位置出发就可以 同时到达交点
*/

struct listNode
{
int value;
listNode* next;
listNode(int x): value(x), next(NULL){}
};

listNode* getIntersectionNode(listNode* headA, listNode* headB)
{
    int lengthOfA = 0;
    int lengthOfB = 0;
    listNode* tempA = headA;
    listNode* tempB = headB;
    while(tempA)
    {   
        lengthOfA ++;
        tempA = tempA -> next;
    }
    while(tempB)
    {   
        lengthOfB ++;
        tempB = tempB -> next;
    }
    int delta = abs(lengthOfA - lengthOfB);

    if(lengthOfA > lengthOfB)
    {
        while(delta--)
        {
            headA = headA -> next;
        }
    }
    else
    {
        while(delta --)
        {
            headB = headB -> next;
        }
    }
    while(headA)
    {
        if(headA == headB)
        {
            return headA;
        }
        else
        {
            headA = headA -> next;
            headB = headB -> next;
        }
    }
    return NULL;
}

int main()
{
    listNode a1(1);
    listNode a2(2);
    listNode b1(3);
    listNode b2(4);
    listNode b3(5);
    listNode c1(6);
    listNode c2(7);
    listNode c3(8);
    a1.next = &a2;
    a2.next = &c1;
    c1.next = &c2;
    c2.next = &c3;
    b1.next = &b2;
    b2.next = &b3;
    b3.next = &c1;

    listNode* r = getIntersectionNode(&a1, &b1);
    cout << r->value;
}
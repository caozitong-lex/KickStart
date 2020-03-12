#include<iostream>
#include<vector>
#include<set>
using namespace std;
/*
划分链表： 传入一个链表头和目标值 使链表左部分元素比目标值小 右边部分元素比目标值大 相对顺序不变 返回修改后的链表头
这道题无法原地修改 因此需要额外开辟空间 最暴力的方法是重新建造两个链表 扫描原链表 遇到大的 就在大链表中实例化一个节点 并赋相同的值 遇到小的同理 最后拼接
更好的方法是 构造两个辅助链表 但不实际开辟空间 而是更改元素的指向即可
这道题对 结构体指针 和 结构体实例具有较好的考察 以及头节点和头指针的区别
首先整体思路是 构造两个辅助链表 一个大链表 元素大于目标值 一个小链表 元素小于目标值 
然后我们扫描原链表 比如遇到一个小节点怎么处理？ 作为小链表的头指针吗 那遇到第二个呢 作为头指针的next？ 显然这样不好实现 需要分开处理
因此 我们为两个链表开辟哨兵节点/头节点 遇到一个节点 无论是大是小 放到对应头节点之后即可 头指针继续移动
最后 两辅助链表指针都移动到了各自的尾部 只要拼接即可 
拼接时 两表尾部指针已知 头部指针则可以由哨兵节点提供 
哨兵节点的作用就是统一处理 无论是第一个节点还是第二个 都直接连接在哨兵节点之后 而不用考虑第一个节点作为头节点 第二个连在头节点后
这也是一个很好的例子 通过从前向后逐个扫描取得节点 逐个改变指向 把一个链表拆分为两个链表 （最后连接）
*/

struct ListNode
{
int value;
ListNode* next;
ListNode(int x): value(x), next(NULL){}
};

ListNode* listPartition(ListNode* head, int x)
{
    ListNode bigHead(0);        //开辟头节点
    ListNode smallHead(0);
    ListNode* bigHeadPtr = &bigHead;    //头指针指向头节点
    ListNode* smallHeadPtr = &smallHead;

    while(head)
    {
        if(head -> value > x)
        {
            bigHeadPtr -> next = head;
            bigHeadPtr = bigHeadPtr -> next;
        }
        else
        {
            smallHeadPtr -> next = head;
            smallHeadPtr = smallHeadPtr -> next;
        }
        head = head -> next;
    }
    smallHeadPtr -> next = bigHead.next;    //连接的不是哨兵节点 是哨兵节点的next
    bigHeadPtr -> next = NULL;

    return smallHead.next;
}

int main()
{
    ListNode a(3);
    ListNode b(4);
    ListNode c(5);
    ListNode d(1);
    ListNode e(2);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    
    ListNode* r = listPartition(&a, 3);
    while(r)
    {
        cout << r->value << endl;
        r = r->next;
    }
}
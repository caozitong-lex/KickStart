#include<iostream>
#include<vector>
using namespace std;

struct ListNode
{
int value;
ListNode* next;
ListNode(int x):  value(x), next(NULL){}
};

/*
合并有序链表：传入两个有序链表头指针 合并它们并返回合并后链表头指针
和链表划分类似 通过逐个改变指针进行穿插式的链表拆分 链表划分是把一个链表拆分为两个 链表合并是把两个链表合并为一个
核心都是相同 逐个扫描原链表 通过逐个改变指向 把节点拆下来添加到新链表后
构造新链表的重要技巧：哨兵节点
*/
ListNode* merge2list(ListNode* l1, ListNode* l2)
{
    ListNode dummyNode(0);
    ListNode* head = &dummyNode;
    
    while(l1 && l2)
    {
        if(l1 -> value > l2 -> value)
        {
            head -> next = l2;
            l2 = l2 -> next;
        }
        else
        {
            head -> next = l1;
            l1 = l1 -> next;
        }
        head = head -> next;
    }

    if(!l1)
    {
        head -> next = l2;
    }
    else
    {
        head -> next = l1;
    }
    return dummyNode.next; 
}


/*
合并k路有序链表
和k路归并相同 先分解问题再合并 
将k个链表无限分解至1个链表 当合并1个链表时 显然直接返回 最后再两两合并
具体来说 先把当前组链表拆解为两组链表 然后把递归合并结果返回 最后取得左右子节点的结果 调用双链合函数合并结果得到最终结果
时间复杂度为 k个链表 平均链长n 第一轮合并了k/2次 每次处理2n个节点 共kn节点 第二轮合并了k/4次 每次处理4n个节点 共kn节点 最后一轮合并了k/log2k次 每次处理 2^logk * n = kn个节点 最终是knlogk 本质上就是进行了logk轮 每轮都要处理所有kn个节点 
*/
ListNode* mergeKlist(vector<ListNode*> l)
{
    if(l.size() == 1)
    {
        return l[0];
    }

    vector<ListNode*> listSetA;
    vector<ListNode*> listSetB;
    for (int i = 0; i < l.size(); i++)
    {
        if(i < l.size() / 2)
        {
            listSetA.push_back(l[i]);
        }
        else
        {
            listSetB.push_back(l[i]);
        }
    }

    ListNode* leftMerged = mergeKlist(listSetA);
    ListNode* rightMerged = mergeKlist(listSetB);
    return merge2list(leftMerged, rightMerged);
}
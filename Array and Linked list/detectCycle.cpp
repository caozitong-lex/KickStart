#include<iostream>
#include<vector>
#include<set>
using namespace std;
/*
第一种基本思路和检查链表交点一样 用set作为检查集合 每遍历到一个 节点就扔到集合中 如果存在重复就说明有环 时间复杂度最大为m*n 
第二种思路是快慢指针 快慢指针可以用于检测环 若都从起点出发 相遇表明检测到环 则慢指针从起点 快指针从相遇点出发 二者以相同速度1前进会在环处相遇 时间复杂度是n
*/
struct ListNode
{
int value;
ListNode* next;
ListNode(int x): value(x), next(NULL){}
};

ListNode* detectCycle(ListNode* head)
{
    set<ListNode*> checkCycle;
    while(head)
    {
        if(checkCycle.find(head) == checkCycle.end())
        {
            checkCycle.insert(head);
            head = head -> next;
        }
        else
        {
            return head;
        }
    }
    return NULL;
}

int main()
{
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    ListNode f(6);
    ListNode g(7);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    e.next = &f;
    f.next = &g;
    g.next = &c;

    ListNode* r = detectCycle(&a);
    cout << r -> value;

}
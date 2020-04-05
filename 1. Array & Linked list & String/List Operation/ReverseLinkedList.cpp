#include<iostream>
#include<vector>
using namespace std;


struct listNode
{
    int value;
    listNode *next;
    listNode(){} //默认构造函数
    listNode(int x): value(x), next(NULL){}
};
//重载输出运算符 对listnode指针输出的是链表
ostream &operator<< (ostream &os, listNode *head)
{
    while(head) //因此这里不能填&a 因为这是一个固定值 而head这是一个变量 
    {
        cout << head->value << "-";
        head = head->next;
    }
    cout << endl;
    return os;
}

class Solution
{
public:
    listNode* reverseLinkedList(listNode* head)
    //1-2-3-4 >> 4-3-2-1
    {
        listNode *preNode = NULL;
        listNode *nextNode = NULL;
        //nextnode用来记录head的下一个位置
        //head则记录了prenode的下一个位置 
        //pre和next是两个指针 并非实际的节点 它们的值是某个节点的内存地址 为NULL表明尚未存储地址 
        //逆置后 原本的头节点的next指向了空 表明不指向任何一个节点 而并非一个实实在在的节点 
        //也可以开辟一个实实在在的哑节点 将原本的头节点指向这个哑节点
        //注意 指向一个值为空的哑节点 和 指向一个空地址 是两回事 
        while(head)
        {
            nextNode = head -> next; //插旗
            head->next = preNode; //翻桥
            preNode = head; //过桥
            head = nextNode; //过桥
        }
        return preNode;
    }

    listNode* reverseFromMtoN(listNode* head, int m, int n)
    // 1->2->3->4 | m=2,n=3 >> 1->3->2->4 链表的序号从1开始 不是数组
    // 逆置过程同上 使用preNode以及nextNode进行逆置 逆置三兄弟 pre head next
    // 除了逆置过程之外 在随着head的遍历过程中 需要记录4个关节节点 逆置后 连接头1 逆置头3 逆置尾2 连接尾4
    // 链表中节点移动的代码可以写作while(head && n--) 假设头节点是1号节点 那么n--表示移动n次 循环结束后移动到了n+1号节点 如果移动到n号节点 则移动n-1次 也就是--n
    {
        // 以 1->2->3->4 | m=1,n=2 >> 1->3->2->4 为例
        int reverseNode = n - m + 1; //逆置的节点个数 也就是2
        listNode *preNode = NULL;  //prenode nextnode用于逆过程
        listNode *nextNode = NULL;
        
        listNode *resultHead = head; //正常情况下 如果不是从第一个节点开始逆置 最终头节点仍然是现在的头节点
        listNode *dummyNode = new listNode(); //哨兵节点 对一些链表改造会改造头节点 有了哨兵节点 无论头节点有没有被修改 都不需要找新链表的头节点 只需要返回dummynode -> next即可
        
        dummyNode -> next = head;
        preNode = dummyNode;
        //【语法】
        //栈中实例化 listNode dummyNode 和堆中实例化 listNode *dummyNode = new listNode()区别不大 
        //注意 如果不写成 listNode dummyNode(1)  listNode *dummyNode = new listNode(1) 则要有默认构造函数
        //无论是哪种实例化 都实实在在开辟了一块listNode类型的内存 存储了listnode类型的数据 
        //如果是 listNode *dummyNode; 则开辟了一块指针变量的内存 这块内存存储的是listNode类型的地址 而内存中并没有开辟一块listNode类型的内存 它只是一个指针 内存中是NULL
        //哨兵节点和链表中的节点一样 是一个实实在在的listNode变量 它是一个节点 有着自己的值（不重要）和next 如果只声明为一个指针 而不开辟node内存 没有实例化就无法谈及next    
        //而preNode和nextNode 只作为游标使用 它不是实际的一个节点 因此不用开辟节点

        //1. 第一次移动 随着head找到逆置后的连接头 逆置尾
        // --m意味着移动m-1次 从1到m  移动完后 head指向m号节点 preNode指向m-1号节点
        while(head && --m) //链表移动节点时可以这么写 
        {
            preNode = head;
            head = head -> next;
        }
        listNode *connectionHead = preNode; //找到逆置后的连接头 也就是1
        listNode *reverseTail = head; //找到逆置后的逆置尾 也就是2

        //2. 第二次移动并逆置 随着head找到逆置后的逆置头和连接尾
        // 接下来开始逆置 从m号节点开始逆置 
        while(head && reverseNode--) //逆置多少节点 就移动多少次
        {
            nextNode = head -> next;
            head ->next = preNode;
            preNode = head;
            head = nextNode;
        }
        //逆置完成后 链表状态为 1 <- 2 <- 3 4
        listNode *reverseHead = preNode; //找到逆置后的逆置头 也就是3
        listNode *connectionTail = head; //此时head处于逆置后的逆置头3的下个节点 找到逆置后的连接尾4

        //3. 开始连接逆置尾和连接尾
        //把逆置尾和连接尾连接 也就是把逆置尾2从指向1变成指向4  1 3->2->4
        reverseTail -> next = connectionTail;

        //4. 开始连接 连接头和逆置头
        //现在的问题就是把连接头和逆置头连接 即1指向3
        //若此时的连接头是空的 表明从第一个节点开始逆置 1是不存在的 那么直接返回逆置头
        //if(connectionHead == NULL)
        //{
        //    return reverseHead;
        //}
        //若此时连接头存在 说明不是从第一个节点开始逆置 把1指向3后 返回初始状态的链表头节点即可
        //else
        //{
        connectionHead -> next = reverseHead;
        //有了dummynode不需要考虑特殊情况 直接连接 直接返回 
        return dummyNode -> next;
        //}

        /*
        listNode *startConnection;
        if(m > 0) //若不是从第一个点开始逆置 
        {
            for(int i = 0; i < m - 1; i++)
            {
                currentNode = currentNode -> next; //到达逆置节点部分前一个
            }
            //记录逆置后待连接的头
            startConnection = currentNode;
        }
        //若从第一个点开始逆置 则不存在逆置后待连接的头
        
        for(int i = 0; i < reverseNode; i++)
        {
            currentNode = currentNode -> next; //到达逆置节点部分的后一个
        }
        //记录逆置后待连接的尾部
        listNode *endConnection = currentNode;
        //cout<<"!:"<<endConnection->value<<endl;

        //使用head完成逆置 到达逆置的第一个点 开始逆置
        for(int i = 0; i < m ; i++)
        {
            head = head -> next; //到达第一个逆置节点
        }
        //记录逆置后尾
        listNode *reverseTail = head;
        // 开始逆置
        for(int i = 0; i < reverseNode; i++)
        {
            nextNode = head -> next;
            head -> next = preNode;
            preNode = head;
            head = nextNode;
        }
        // 此时逆置部分逆置完毕 preNode到达逆置部分的最后一个节点 
        // 记录逆置后头
        listNode *reverseHead = preNode;

        //把 连接头-逆置后头 逆置后尾-连接尾拼接起来
        startConnection -> next = reverseHead;
        reverseTail -> next = endConnection; 

        //如果从第一个节点开始逆置 那么最终链表头节点就是逆置后头 因为连接头部分不存在
        if(m == 0)
        {
            return reverseHead;
        }
        return resultHead;
        */
    } 


    listNode* reverseByGroup(listNode* head)
    // 1->2->3->4 | k=2 >> 2->1->4->3
    // 
    {
       return NULL;
    }
};


int main()
{
    listNode a(1);
    listNode b(2);
    listNode c(3);
    listNode d(4);
    listNode e(5);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;

    Solution s;
    listNode *head = &a; //变量a所代表的地址&a是常量 而head是存储这个地址的变量
    cout<<"Before: "<< head;
    head = s.reverseFromMtoN(&a, 2, 3);
    cout << "After: " << head;


}
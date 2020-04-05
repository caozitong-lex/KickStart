#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
模拟LRU缓存 
LRU是一个有限空间 当空间满后 若再加入元素 先移除最久没有使用的元素 -> 显然 这可以通过队列实现 先进放到队头 先出 
此外 LRU的存和取还要满足两个条件 
当空间满后 若再加元素 若新元素在LRU中存在 则更新元素的值 把该元素放到队尾 否则添加到队尾并 移除队头
取元素时 除了返回元素的值 还有把该元素放到队尾
 -> 显然 从中间移动元素并保证其他元素顺序的数据结构是链表
具体来说 LRU需要实现两个操作 取元素和放元素 取时传入索引key 放时传入索引key和值 都要满足上述规则

对外来看 LRU就是一个有限空间的哈希表 即根据key来存取 
内部实现来看 由于移除规则的约束 必须使用一个链表来实现
本质就是链表的元素移动操作

存取元素免不了head->next的遍历 这次为了提高效率 可以使用单向链表+哈希 记录前躯节点并直接锁定某节点 而不需要head -> next遍历判断
并且LRU可以添加一个尾节点 方便操作
使用dummynode和head 哨兵节点指针指向哨兵节点 不存储值 相当于不动坐标 虽然可以拿来定位头部 head指针指向实际的第一个节点 可能会改变 
在这道题中head指针指向不变 有时需要head->next 头指针拿来遍历 但不建议 若遍历则另外复制一个游标指针 尽量让头指针指向第一个节点 
*/

struct LRUnode
{
    int key;
    int value;
    LRUnode* next;

    LRUnode(){}
    LRUnode(int x, int y): key(x), value(y), next(NULL){}
};

class LRUcahe
{
private:
    LRUnode* head;
    LRUnode* tail;
    LRUnode* dummyNode;
    map<int, LRUnode*> recordPre;
    int currentSize;
    int maxSize;
    // 存/取操作中都有把节点从链表拿出放到队尾的操作 因此提取出来单独写成函数
    // 不仅是节点的移动  还有考虑到哈希的更新
    void moveToTail(LRUnode* element)
    {
        if(element == tail)
        {
            return;
        }
        LRUnode* pre = recordPre[element -> key];   //获得前躯
        LRUnode* post = element -> next;            //获得后继

        pre -> next = post;                         //拆下
        recordPre[post -> key] = pre;               //更新哈希

        tail -> next = element;                     //放到尾部
        recordPre[element -> key] = tail;           //更新哈希 
        tail = tail -> next;                        //更新尾指针
        tail -> next = NULL;
    }
public:
    LRUcahe(int capacity)
    {
        currentSize = 0;
        maxSize = capacity;
        LRUnode* dummyNode = new LRUnode();
        head = dummyNode;
        tail = dummyNode;
        dummyNode -> next = NULL;
    }

    int get(int key)
    {
        if(recordPre.find(key) == recordPre.end())
        {
            return -1;
        }
        LRUnode* pre = recordPre[key];
        moveToTail(pre -> next);
        return pre -> next -> value;
    }

    void put(int key, int value)
    {
        // 待插入节点已存在 则不管满不满 移动即可
        if(recordPre.find(key) != recordPre.end())
        {
            LRUnode* pre = recordPre[key];
            pre -> next -> value = value;
            moveToTail(pre -> next);
        }
        //待插入节点不存在
        else
        {
            //LRU满时 需要删除头节点
            if(currentSize >= maxSize)
            {
                dummyNode -> next = head -> next;               //移除头节点
                recordPre.erase(head -> key);                   //更新哈希：删除头节点哈希
                recordPre[head -> next -> key] = dummyNode;     //更新哈希：添加新头节点的哈希
                head = head -> next;                            //更新头节点
                currentSize --;
            }
            // 不管满不满 都需要在尾部插入新节点
            tail -> next = new LRUnode(key, value); //添加到尾部
            recordPre[tail -> next -> key] = tail;  //更新哈希
            tail = tail -> next;                    //更新尾节点
            currentSize ++;
        }
    }
};
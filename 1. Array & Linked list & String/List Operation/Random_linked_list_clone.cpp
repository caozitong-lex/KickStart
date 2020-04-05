#include<iostream>
#include<vector>
#include<map>
using namespace std;

/*
链表的深度拷贝：传入原链表的头指针 返回复制链表的头指针
简单版本的图拷贝 核心思想仍然是 逐个取原图/链表的点 先复制点 同时搭建映射 最后复制边 
区别是由于图的连接是一对多的 无法使用neighbor来逐个获得所有节点 为了能够逐个取出点进行克隆 必须使用bfs一次性取得所有节点并用vector将它们框起来方便逐个处理 在vector中的顺序就是遍历顺序 但顺序并不重要 
而链表的连接是一对一的 可以直接用->next 来逐个获得所有节点进行复制 因此不再需要get函数进行收集
*/
struct Node
{
int value;
Node* next;
Node* random;
Node(int x): value(x), next(NULL), random(NULL){}
};

Node* copyRandomList(Node* head)
{
    map<Node*, Node*> nodeMapping;
    vector<Node*> clone;

    //通过链表->next方式代替循环 逐个获取原链表每个点 
    //没有使用for循环 因此需要复制一遍头进行两次循环 以及建立一个等价于i的索引
    Node* temp = head;
    int i = 0;
    //复制点
    while(temp)
    {
        clone.push_back(new Node(temp->value)); //实例化复制点
        nodeMapping[temp] = clone[i];           //构建映射
        i ++;                                   //推动循环 
        temp = temp -> next;                    //推动循环 
        
    }

    i = 0;  //重置循环的索引
    temp = head;
    //复制边
    while(temp)
    {
        if(temp->next)  //和图不同的是 链表每个节点可能存在next/random指针为NULL的情况 映射中没有NULL的字典 因此判断一下防止报错
        {
            clone[i] -> next = nodeMapping[temp -> next];
        }
        
        if(temp->random)
        {
            clone[i] -> random = nodeMapping[temp -> random];
        }

        i ++;                   //推动循环
        temp = temp -> next;    //推动循环
    }

    return clone[0];
}

int main()
{
    Node a(7);
    Node b(13);
    Node c(11);
    Node d(10);
    Node e(1);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = &e;
    b.random = &a;
    c.random = &e;
    d.random = &c;
    e.random = &a;

    Node* r = copyRandomList(&a);
    
    // 如果next/random是NULL 那么还调用next/random -> value 会报错 打印next/random 也就是空指针 是合法的 但打印空指针的属性是不合法的
    /*
    while(r)
    {
        
        if(r -> random)
        {
            cout << r->value << "->random:" << r->random->value << endl;
        }
        else
        {
            cout << r->value << "->random: NULL" << endl;
        }
        if(r -> next)
        {
            cout << r->value << "->next:" << r->next->value << endl;
        }
        else
        {
            cout << r->value << "->next: NULL" << endl;
        }
        r = r -> next;
    }
    */
    return 0;
}
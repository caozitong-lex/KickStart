#include<iostream>
#include<vector>
#include<map>
using namespace std;

class treeNode
{
    int value; 

};

struct nodee
{
    int value;

    nodee(int x): value(x){}
};


int main()
//在编码习惯中 对于节点 或单个对象往往传入 指针 而对于多个对象的集合 如节点的vector  会传入引用 因为往往这些对象集合提供信息/查询 而不修改它们 索引往往是 const &xxx 
//写题一开始初始化好所需的数据结构和边界 判断 往往能启发你第一步
{
    nodee a(1);
    nodee b(2);


  
    
    
    system("out");
    return 0;
}
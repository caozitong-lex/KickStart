#include<iostream>
#include<map>
#include<vector>
using namespace std;

/*
二分搜索树的性质：
按照前序遍历的结果顺序插入可以复原搜索树结构 因为搜索树的形状取决于根节点 
也就是说 从大到小确定了根节点 也就能确定一棵树的形状 因为根节点确定了 左右子树的节点内容也就确定了 
而前序遍历就是首先输出根 
中序遍历则先左后中最后右 也就是从小到大 可以得到排序结果 可以用来验证一棵树是否是bts
想象一下这样插入一棵空搜索树 结果是一个链表 因为一直往右子节点插入
*/

struct btsNode
{
    int value; 
    btsNode* left;
    btsNode* right;
    btsNode(int x): value(x), left(NULL), right(NULL){}
};

// 二分搜索树的插入
void bts_Insert(btsNode* currentNode, btsNode* insertNode)
{
    if(insertNode -> value < currentNode -> value)
    {
        if(currentNode -> left)
        {
            bts_Insert(currentNode -> left, insertNode);
        }
        else
        {
            currentNode -> left = insertNode;
        }
    }
    else
    {
        if(currentNode -> right)
        {
            bts_Insert(currentNode ->right, insertNode);
        }
        else
        {
            currentNode -> right = insertNode;
        }
    }
}

void midorder_print(btsNode* root, int layer)
{
    if(!root)
    {
        return;
    }
    
    
    midorder_print(root -> left, layer + 1);
    for(int i = 0; i < layer; i++)
    {
        cout << "---";
    }
    cout << root << ":" << root -> value << endl;
    midorder_print(root -> right, layer + 1);
}

int strToNum(string str)
{
    int num = 0;
    for(int i = 0; i < str.size(); i++)
    {
        num = num * 10 + str[i] - '0';
    }
    return num;
}

string numToStr(int num)
{
    string str;
    while(num)
    {
        str.push_back(num % 10 + '0');
        num /= 10;
    }
    reverse(str.begin(), str.end());
    return str;
}

/*
序列化即利用前序遍历的过程 通过一个全局笔记本记录遍历过程 并且节点之间添加#分割
需要用到数字转字符串  
*/
void recursionHelper(btsNode* root, string &serial)
{
    if(!root)
    {
        return;
    }
    string num_str = numToStr(root -> value);
    serial = serial + num_str;  // +用于两个string拼接
    serial.push_back('#');      // pushback用于string和char

    recursionHelper(root -> left, serial);
    recursionHelper(root -> right, serial);
}

string serialization(btsNode* root)
{
    string serial;
    recursionHelper(root, serial);
    return serial;
}
/*
读取序列字符串处理 碰到完整数字就实例化节点插入 思路简单 注意字符串的处理过程
需要字符串转数字 
还有一点就是类指针的问题 node* root 仅仅得到一个指针 并没有node类型的实例 node指向一个空对象 因此node->value等于 NULL->value会报错
new node()会创建出一个实例对象后 返回对指针 
此外由于类的构造函数为node(int x) 没有无参构造函数 因此 栈实例化node a()和 堆实例化node *a = new node() 都会报错 除非在类补充无参构造函数
*/

btsNode* deserialization(string &serial)
{
    btsNode* root;
    int rootFlag = 1;
    string str_num;

    for(int i = 0; i < serial.size(); i++)
    {
        if(serial[i] == '#')
        {
            int int_num = strToNum(str_num);
            //cout << "当前加入数字：" << int_num << endl;

            if(rootFlag)
            {
                root = new btsNode(int_num);    //实例化出一个节点 将指针返回
                rootFlag = 0;
            }
            else
            {
                bts_Insert(root, new btsNode(int_num));
                str_num = "";
            }
        }
        else
        {
            str_num.push_back(serial[i]);
        }                                                       
    }
    return root;
}

int main()
{
    btsNode a(8);
    btsNode b(3);
    btsNode c(10);
    btsNode d(1); 
    btsNode e(6);
    btsNode f(15);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;

    string data = serialization(&a);
    cout << data << endl;
    btsNode* root = deserialization(data);
    midorder_print(root, 1);

}
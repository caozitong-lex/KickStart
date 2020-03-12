#include<iostream>
#include<vector>
using namespace std;

/*
求树中两个节点最近公共祖先
遍历实现：
实际上是当作链表来做题 求出根到两个节点到路径 当作链表 题目就转化为了 两个链表找分叉 因此只需要一个求路径的遍历函数
遍历函数参数：主参数（头节点 目标节点） 全局笔记本（解路径）局部笔记本（当前路径）辅助笔记本（目标笔记本 找到标志）
前序判断递归深度是否到叶节点 先更新节点状态/当前路径 然后检查更新全局笔记本 中序对左右子树递归 后序回溯
接口函数则对两个链表进行同步前进 找到分叉点即可  比链表的分叉简单

分治实现：
分治的核心是找到左右子树和根树的解关系 
若左右子树的节点都非空 表明当前节点就是解
若左子树为空 说明解在右子树 反之同理
若都空 说明左右子树都没有解 返回NULL
这个关系找的非常巧妙 尤其是当找到解时 如何将解传递上去 
因为找到解时 p q和解一定都在当前这棵树 另一棵树一定是NULL
那么就会一直向上传递有解的这棵树的根节点 
*/
struct TreeNode
{
int value;
TreeNode* left;
TreeNode* right;
TreeNode(int x): value(x), left(NULL), right(NULL){}
};

void findPath(TreeNode* root, vector<TreeNode*> &finalPath, vector<TreeNode*> &currentPath, TreeNode* target, int foundFlag )
{
    if(!root || foundFlag)
    {
        return;
    }
    currentPath.push_back(root);        //先同步节点和路径 这里不需要记录当前和整体 没有先后冲突
    if(target == root)
    {
        finalPath = currentPath;        //当前路径是局部笔记本 不是全局 每个节点都有自己的局部笔记本 并且最终都会回溯到空 因此需要一个全局笔记本记录解
        return;                         //那么考虑找到后就返回呢？这是遍历递归 不同递归深度之间的结果不进行传递和汇合 深层递归的结果无法传递到最外部
    }

    findPath(root -> left, finalPath, currentPath, target, foundFlag);
    findPath(root -> right, finalPath, currentPath, target, foundFlag);

    currentPath.pop_back();
}

TreeNode* lowerstCommonAncesterByTraversal(TreeNode* root, TreeNode* p, TreeNode* q)
{
    
    TreeNode* ancester;
    vector<TreeNode*> pathP;
    vector<TreeNode*> pathQ;
    vector<TreeNode*> tempPathP;
    vector<TreeNode*> tempPathQ;
    int foundFlag = 0;
    
    findPath(root, pathP, tempPathP, p, foundFlag);
    findPath(root, pathQ, tempPathQ, q, foundFlag);

    
    TreeNode* preP = root;
    TreeNode* rootP = root;
    TreeNode* preQ = root;
    TreeNode* rootQ = root;

    int shorterLength = min(pathP.size(), pathQ.size()); //这里如果不取短者遍历 虽然理论上没错 但若找不到公共祖先时 短的会先走到NULL 此时索引空节点的value会报错
    for(int i = 0; i < shorterLength; i++)
    {
        if(pathP[i] -> value != pathQ[i] -> value)
        {
            ancester = pathP[i - 1];
        }
    }
    
    return ancester;        
}
TreeNode* lowerstCommonAncesterByConquer(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(root == NULL || root == p || root == q)  //前序是递归终点 遍历到叶节点/目标节点 则无需递归下去
    {
        return root;
    }
    TreeNode* left = lowerstCommonAncesterByConquer(root -> left, p, q);
    TreeNode* right = lowerstCommonAncesterByConquer(root -> right, p, q);

    if(left != NULL && right != NULL)
    {
        return root;
    }
    if(left != NULL)
    {
        return left;
    }
    if(right != NULL)
    {
        return right;
    }
    return NULL;
}

int main()
{
    TreeNode a(3);
    TreeNode b(5);
    TreeNode c(1);
    TreeNode d(6);
    TreeNode e(2);
    TreeNode f(0);
    TreeNode x(8);
    TreeNode y(7);
    TreeNode z(4);


    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.left = &f;
    c.right = &x;
    e.left = &y;
    e.right = &z;



    //TreeNode* r = lowerstCommonAncesterByTraversal(&a, &d, &z);
    TreeNode* r = lowerstCommonAncesterByConquer(&a, &d, &z);
    if(r)
    {
        cout << r->value;   //若r为NULL NULL -> value会报错
    }
    else
    {
        cout << "NULL!";
    }
    
}
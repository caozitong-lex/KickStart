#include<iostream>
#include<vector>
using namespace std;
struct TreeNode
{
int value;
TreeNode* left;
TreeNode* right;
TreeNode(int x): value(x), left(NULL), right(NULL){}
};
/*
传入一棵树的根节点 将这棵树转化为链表 元素顺序为前序遍历 中-左-右
最暴力的方式是另开辟一组链表节点 按前序遍历顺序浅复制即可 但不是原地方法
*/

/*
首先是遍历实现 遍历实现很好的考察的遍历dfs的过程
基本思想是 既然是把树转化为前序遍历的右链表 那么就按照前序遍历的顺序 把每个节点放到前一个节点的右节点就行了
具体实现时 由于题目本身无返回值 则 正好符合遍历递归 不需要写接口函数和 递归函数
但仍要有一个全局笔记本 记录上一个节点指针 写在函数外
仍然是在前序进行操作 首先把当前节点放到上一个节点的右节点  然后把当前节点作为【上一个节点】 进行递归 注意递归过程会改变结构 因此递归前先取出右节点再递归

首先 这样实现完全利用了遍历dfs的遍历顺序 回顾纯遍历的实现 root其实就是按前序遍历取到各个节点 这次多加了一个前节点和它一起遍历
其次 反直觉的部分在于 直接把前节点的右节点设置为当前节点 那原本的右节点怎么办？ 原本的右节点被递归记录下来 
prenode和root就像追逐游戏 root按照前序遍历进行游走各个节点 prenode则在后面把root整体不断移动到自己的右节点 虽然root的整体位置在变 但root的内部不变
虽然prenode->right = root看起来把right拆掉了 但其实上一层调用右子树递归时 right子树已经开始等待递归 当左递归结束后 就开始右递归 而遍历顺序和是否与root相连无关 这是理解这道题遍历实现的核心 
preNode root会按一直按照前序遍历的顺序取点 当root走到原本的右节点时 preNode -> right = root 会将它们重新连接
*/
TreeNode* preNode = NULL;
void flattenByTraversal(TreeNode* root)
{
    if(!root)
    {
        return;
    }
    if(preNode !=  NULL)
    {
        preNode -> right = root;
        preNode -> left = NULL;
    }
    preNode = root;
    TreeNode* right = root -> right;

    flattenByTraversal(root -> left);
    flattenByTraversal(right);
}

/*
分治实现的思路是 将左右子树掰直后 将左子树链表放到右子树链表 就得到根树链表
链表移动合并的关键是链表的首尾 首可以通过root->left/right得到 尾部则是返回的合并解 
分治实现需要返回值 而这道题反而无返回值 因此分开写作接口函数和分治函数
得到左右子树的掰直结果后
若左链表不为空 则拼接到右链表和根节点之间
此时检查 若右不为空 则表明原本右子树存在 所以返回右链表尾
若右空 左不为空 则右子树不存在 所以返回左链尾
若都空 表明是叶节点 返回root
*/
TreeNode* conquerHelper(TreeNode* root)
{
    if(!root)
    {
        return NULL;
    }
    
    TreeNode* leftLast = conquerHelper(root -> left);
    TreeNode* rightLast = conquerHelper(root -> right);

    if(leftLast != NULL)
    {
        leftLast -> right = root -> right;
        root -> right = root -> left;
        root -> left = NULL;
    }
    
    if(rightLast != NULL)
    {
        return rightLast;
    }
    if(leftLast != NULL)
    {
        return leftLast;
    }
    
    return root;
}
void flattenByConquer(TreeNode* root)
{
    conquerHelper(root);
}
int main()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(5);
    TreeNode d(3);
    TreeNode e(4);
    TreeNode f(6);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    e.right = &f;

    flattenByConquer(&a);
    TreeNode* head = &a;
    while(head)
    {
        if(head -> left)
        {
            cout << "error"<< endl;
        }
        else
        {
            cout << head -> value;
            head = head -> right;
        }
    }
}
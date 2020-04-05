// 二叉树的dfs 遍历和分治都可 基本模板外加入了额外参数
// 额外参数是每个节点所特有的 维护的值 比如当前节点的深度 当前节点到根节点的距离 等等 它是层笔记本
// 和【树的最长路径】同类题

#include<iostream>
#include<vector>
#include<stdio.h>

using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};
// 传入根节点 返回树的高度 
// (BFS层级遍历也可解)
class Solution
{
public:
// -> dfs遍历实现 遍历每一条路径 维护最大深度变量 和二叉树dfs模板不同的是 全局笔记本是一个int变量 记录最大深度 传引用  
// 【因为无法直接更新全局笔记本】 递归函数中还加了额外需要记录的参数 当前深度 这个变量跟随每层遍历变化 通过当前深度来更新最大深度
// 为什么不每往下递归一次就直接最大深度+1呢 因为最大深度是全局变量 一层有很多节点 每个节点内部都对最大深度加一 显然不对 因此 记录当前深度变量 进而更新最大深度 避免所有节点都更新最大深度
// dfs的遍历实现的接口函数就做三件事 递归函数的参数变量的构建（全局笔记本和额外参数） 传入递归函数 返回全局笔记本

    void treeRecursion(TreeNode *root, int &maxDepth, int currentDepth)
    {
        if(root == NULL)
        {
            return;
        }
        if(currentDepth > maxDepth)
        {
            maxDepth = currentDepth;
        }
        treeRecursion(root->left, maxDepth, currentDepth + 1);
        treeRecursion(root->right, maxDepth, currentDepth + 1);

    }
    int depthOfTreeByTraversal(TreeNode *root)
    {
        int maxDepth = 0;
        int currentDepth = 1;
        treeRecursion(root, maxDepth, currentDepth);
        return maxDepth;
    }
// 分治法遵循 任何一棵树高度=  左子树和右子树的最大值+1
// 解的合并策略就是左右解取较大值后加一 这个+1就是一种动态更新 成为新的解
    int depthOfTreeByDC(TreeNode *root)
    {
        //int maxDepth = 0;
        //分治法不需要打擂台 因为是从底层从0累加上来 打擂台只出现在遍历实现
        if (root == NULL)
        {
            return 0;
        }

        int leftDepth = depthOfTreeByDC(root->left);
        int rightDepth = depthOfTreeByDC(root->right);

        return max(leftDepth, rightDepth) + 1;
    }
};


int main()
{
    TreeNode a(1);
    TreeNode b(2);
    TreeNode c(5);
    TreeNode d(3);
    TreeNode e(4);
    TreeNode f(6);
    TreeNode g(7);
    a.left = &b;
    a.right = &c;
    b.left = &d;
    b.right = &e;
    c.right = &f;
    f.left = &g;

    Solution s;
    int dd = s.depthOfTreeByTraversal(&a);
    int ddd = s.depthOfTreeByDC(&a);
    printf("%d", ddd);

    system("out");
    return 0;
}
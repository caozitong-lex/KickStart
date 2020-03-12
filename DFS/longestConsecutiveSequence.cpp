#include<iostream>
#include<vector>
using namespace std;
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};
/*
传入树根节点 返回树中连续递增序列的最大长度
可以用分治也可以用遍历
对于分治 和最大子树和类似 若直接返回子树中的最长连续递增序列 我们无法确定这个序列是否和根节点相连 无法合并解
因此我们只返回以本节点为头的递增序列最大长度 打擂台维护辅助全局笔记本最大长度即可
这里的辅助全局笔记本可以写作参数中也可以写作外部全局变量 
这道题可以和最大子树和比较 体会间接返回结果 打擂台更新全局笔记本的流程

*/
int longestseq = 0;
int divideConquerHelper(TreeNode* root)
{
    if(!root)
    {
        return 0;
    }
    int leftLength = divideConquerHelper(root -> left);
    int rightLength = divideConquerHelper(root -> right);
    int currentLength;
    // 根节点连接到可连接且更长的子树上
    bool leftConnection;
    bool rightConnection;
    if(root -> value < root -> left -> value)
    {
        leftConnection = true;
    }
    if(root -> value < root -> right -> value)
    {
        rightConnection = true;
    }
    if(leftConnection && !rightConnection)
    {
        currentLength = leftLength + 1;
    }
    else if(!leftConnection && rightConnection)
    {
        currentLength = rightLength + 1;
    }
    else if(leftConnection && rightConnection)
    {
        currentLength = max(leftLength, rightLength) + 1;
    }
    else
    {
        currentLength = 1;
    }
    
    if(longestseq < currentLength)
    {
        longestseq = currentLength;
    }
    return currentLength;
}

int longestConsecutiveSequence (TreeNode* root)
{
    divideConquerHelper(root);
    return  longestseq;
}
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
传入根节点 判断是否为二叉搜索树（即任何子树的左子树所有节点小于根节点 根节点小于右子树的所有节点）
这道题第一种方法是中序遍历 若结果是递增序列 则可以验证是二叉搜索树
第二种方法和判断平衡树非常相似 使用分治 一棵树为bts则左右子树是bts 且左子树的最大值小于根节点 小于右子树的最大值
体会 制作结果类 以及 分治实现在后序通过子树的信息合并解的过程
*/

struct resultType
{
    int max;
    bool isBTS;
    resultType(){}
    resultType(int x, bool r): max(x), isBTS(r){}
};

resultType* divideConquerHelper(TreeNode* root)
{
    //空树是bts
    if(!root)
    {
        return new resultType(0, true);
    }
    //得到左右子树的最大值和判断信息
    resultType* leftResult = divideConquerHelper(root -> left);
    resultType* rightResult = divideConquerHelper(root -> right);
    // 判断本树是否为bts
    bool currentIsBTS;
    //判断左右子树都是搜索树
    if(leftResult -> isBTS == false || rightResult -> isBTS == false)
    {
        currentIsBTS = false;
    }
    //判断本树是否为搜索树
    else
    {
        currentIsBTS = leftResult -> max < root -> value && root -> value < rightResult -> max;
    }
    //计算本树的最大值
    int currentMax = max(root -> value, leftResult -> max, rightResult -> max);
    //记录结果 返回解
    return new resultType(currentMax, currentIsBTS);
}
bool validBTS(TreeNode* root)
{
    resultType* final = divideConquerHelper(root);
    return final -> isBTS;
}
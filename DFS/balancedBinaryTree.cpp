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
传入树的根节点 判断这棵树是否为平衡二叉树（即任何子树包括根树 的左右子树高度差不超过1）
涉及到子树显然适合分治 即判断子树是否平衡 若子树都平衡 且这两棵子树高度差不超过1 那么根树则平衡
显然合并解的时候 如果只合并返回的布尔值 即子树是否平衡  无法得知高度 这意味着返回解的信息不充分 还需要返回子树高度 
那么返回解与题目解不统一 意味着要写成分治函数和接口函数 
且返回解可以制作成一个结构体 包含树高的信息和是否为平衡树的信息
【当你合并解时 发现返回的信息多于一个 否则无法合并时 要考虑制作结果类 分治和接口分开实现】
注意求树高时不要和遍历实现混淆 分治求树高是通过逐步合并左右子树信息 在归纳合并解时+1即可得到树高 然后记录到返回解中 
level是用在遍历实现 充当记录局部状态的参数笔记本 从上向下递归递增 一直触底得到整棵树高
*/
struct resultType
{
    int height;
    bool isBBT;
    resultType(int x, bool r): height(x), isBBT(r){}
};

resultType* divideConquerHelper(TreeNode* root)
{
    //空树是bbt
    if(!root)
    {
        return new resultType(0, true);
    }
    //得到左右子树的高度和判断信息
    resultType* leftResult = divideConquerHelper(root);
    resultType* rightResult = divideConquerHelper(root);
    //计算本树的高度
    int currentHeight = max(leftResult -> height, rightResult -> height) + 1;
    //判断本树是否为bbt
    bool currentBBT;
    //首先左右子树必须是平衡的
    if(leftResult -> isBBT == false || rightResult -> isBBT == false)
    {
        currentBBT = false;
    }
    //其次本树必须是平衡的
    else
    {
        currentBBT = abs(leftResult -> height - rightResult -> height) < 2;
    }
    //记录结果 返回解
    resultType* currentResult = new resultType(currentHeight, currentBBT);
    return currentResult;
}

bool validBalancedBinaryTree(TreeNode* root)
{
    resultType* final = divideConquerHelper(root);
    return final -> isBBT;
}
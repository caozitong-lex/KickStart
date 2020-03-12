#include<iostream>
#include<vector>
#include<set>
using namespace std;

/*
将（）视为一组括号 传入n表明使用n组括号 返回所有能够生成的合法括号序列
求子集问题实际上是 各个组合问题的和 n取1的组合+n取2的组合+...n取n的组合 加起来为2^n
求解时第一种思想是 取/不取 形成二叉树
第二种思想是通过全排列的思想求解的 形成多叉树 1 2 3 4 5 对于全排列来说 第一个位置有5种 第二个位置有四种 ...最后一个位置有一种
利用这种思想求子集 则是 第一个位置有5种 第二个位置要根据第一个位置确定种数 若第一个位置选择4 则第二个位置只有4后面的数可以选 仅1种 这是为了确保顺序唯一 避免重复集合 因此不是真正意义上的全排列 
多叉树求全排列 则循环从0到最后而不是从i到最后 如果遍历到已经取过的元素则跳过 因此需要记录取过的元素

括号生成暴力方法是递归生成所有排列 检查括号序列合法性
生成全排列第一种方法是全排列思想的多叉树 这是标准的全排列问题
第二种方法是求子集思想的二叉树 虽然是全排列问题 但可以当作子集问题 因为子集问题是取/不取做n次 2个元素的全排列问题则是取a/取b做n次）
/一个序列 子序列有n^2 子集/子序列/组合有2^n（由于子集不考虑顺序 因此可以看做是一种顺序 子序列同样是固定顺序的组合） 全排列有n!/
更优的方法是在生成过程中进行剪枝 提前去除已经不合法的序列 
检查括号的合法序列 第一步是左右括号数量必须相等  第二步是当左括号数量 <= 右括号 不能再放置右括号 
首先在求子集的基础上 两个递归 取(或取) 区别是 各自添加了两个剪枝条件 条件下无需进行下一步递归
此外 使用了局部笔记本因此没有明式写出子集的回溯
最后 由于计数和subset是同步更新 最开始left right都为0 进入下一层前 子集已经被更新 因此先检查记录 再添加新的子集 
求子集中 最开始进入第0层 subset是空的 然后才加入nums[0] 所以是计数/层数/索引先i+1递归至下一层 而后子集才根据新的i添加 因此要先添加 再记录子集
求子集中也可以改为初始化时subset加入nums[0] 之后递归时 index + 1和 subset加入nums[index + 1]同步 这样就先记录子集
*/
void recursionByBinTree(int n, int left, int right, string subset, vector<string> &subsets)
{
    if(left + right == 2 * n)   //若所有括号放完 生成结束
    {
        subsets.push_back(subset);
        return;
    }
    if(left < n)        //取左括号。限制了左括号数量
    {
        recursionByBinTree(n, left + 1, right, subset + '(', subsets);  //把子集写作层局部笔记本 注意不能用引用 因为引用不能是右值
    }
    if(left > right)    //取右括号。限制了左右括号的数量关系
    {
        recursionByBinTree(n, left, right + 1, subset + ')', subsets);
    }
    
}
vector<string> generateParathesis(int n)
{
    vector<string> subsets;
    string subset;
    int left = 0;
    int right = 0;
    recursionByBinTree(n, left, right, subset, subsets);
    return subsets;
}

// 二叉树dfs的遍历+分治 分治体现在局部笔记本/解的合并 遍历体现在对接口函数+分治函数 打擂台的构造 
// 需要求出最值的都免不了打擂台 涉及遍历
// 接口+分治/遍历函数的架构具体为： 接口函数创建题目解（全局笔记本）的数据结构 传入到分治/遍历函数中处理 

// 遍历函数无返回值 参数除了基本参数（根节点） 全局笔记本（题目解） 还有一些在层之间传递的关于每层信息的额外参数 额外参数包括辅助全局变量和函数参数
// 辅助全局笔记本和 全局笔记本一起声明 如最大子树和的最大值 （也可以写在函数外做全局变量） 在遍历的过程（前序）对全局笔记本进行更新维护
// 函数参数则是局部/层笔记本 绑定了每层的信息 如求树高的深度参数 如果用辅助全局笔记本来实现局部笔记本 则需要回溯 如求树路径和的当前路径 或当前路径和

// 分治函数有返回值 因此分治函数往往就是解题函数 不再分开写 因此参数和题目 一致 参数除了基本参数（根节点） 局部笔记本（返回解 通常也是题目解，不放在参数里 需要得到左右子解后合并返回） 
// 一般情况下 分治函数需要在开始自己创建局部笔记本 即返回解 取得左右子树的返回解后 根据已有的信息进行合并返回自身的解
// 若题目解和合并解无法统一 需要把分治法写成两部分 接口函数和分治函数时 
// 在需要求最值的分治实现问题中 参数中还可以添加辅助合并解的全局笔记本 如最值（ 否则单个分治函数只有基本参数）或写成全局变量
// 分治函数会向接口函数返回最终解 但接口函数可以不接收返回值 因为那是局部笔记本（如这道题的子树最大和） 不是题目要求的解（如最大和的子树的节点指针） 全局笔记本在分治过程就被维护完成

#include<iostream>
#include<vector>

using namespace std;
// 给定一棵树的根节点 返回这棵树的最大平均值的子树的根节点 最大平均值指的是树中节点和/节点数
struct TreeNode
{ 
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};

struct SubtreeResult
{
    int sum;
    int size;
    TreeNode* head;
    SubtreeResult(int x, int y): sum(x), size(y){}
};
int globalMin = -100;
class Solution
{
public:
// 分治法的核心是解的合并 这道题如何合并？
// 我们看下面的几种题型：
// 1. 问最大子树和max 
// 首先考虑一种方案 每次返回的是当前根树的最大子树和（该树根不一定就是当前的根）那么如何合并解？显然无法合并 因为左右子树内部的最大子树 和当前的根不一定相连 无法合并成当前根树内部的最大子树和 
// 另一种方式是 外部声明一个最大值变量 作为辅助全局笔记本 递归每次返回的解是树和 = 左子树+右子树 而不直接求当前树的最大和 知道了所有树和 也就能打擂台得到最大子树和 多了一个打擂台的步骤 将求最大子树和 转化为两步 求子树和 再求最大值
// 辅助全局笔记本在分治中的作用类似遍历实现的全局笔记本 更新好后 在接口函数中返回
// 归并的核心是弄清楚解的合并关系 根的解等号右边能利用的值 只有左右子树的解 或加上常数 如+1 或加上可用的函数参数 如+本节点的值 等等
// 如果返回的解 和 题目要求的解不一致 就写作接口函数+归并函数（类比 接口函数+递归函数）的形式 在归并函数的函数参数中加入接口函数的全局笔记本进行维护 和遍历实现的递归函数类似 只不过接口函数中需要接受归并函数返回的解 虽然用不到 但归并函数必须返回值 进行合并过程
    int divideConquerHelper(TreeNode* root)
    {
        int sumLeft = 0;
        int sumRight = 0;
        int selfSum = 0;
        
        if(root == NULL)
        {
            return -1;
        }
        sumLeft = divideConquerHelper(root->left);
        sumRight = divideConquerHelper(root->right);
        selfSum = root->value + sumLeft + sumRight;
        if(globalMin > selfSum) //打擂台 -> 遍历
        {
            globalMin = selfSum;    //globalMin是全局最小值 selfSum是当前子树的最小值
        }
        return selfSum;
    }
    int minSumSubtree(TreeNode* root)
    {
        divideConquerHelper(root);
        return globalMin;
    }


// 2. 问最大子树和的树根节点。此时分开写成接口函数和分治函数 因为分治返回的无论是树和 还是 树最大和 都和题目要求的节点指针不一致 
// 分治函数返回树和 那么节点指针和树的最大和作为全局笔记本 最大和用于遍历树和打擂台找到目标树 节点指针则需要在归并中不停更新为目标树 

// 3. 问最大平均和的子树根节点。显然一棵树的最大子树和可以分治直接得到 但平均和涉及到了子树的节点个数 这时 解的合并关系就不再追截了当了 父树的最大平均和 无法从子树的最大平均和中直接推导而来 而是需要计算
// 显然 计算父树的的平均和 需要子树的平均和之外 需要的是子树的节点个数 
// 既然如此 那我们希望修改分治函数返回的解 是两个内容 节点个数 和 平均和 
// 分治函数必须有一个辅助全局笔记本 维护最大子树根节点指针 还需要维护一个最大和辅助全局笔记本 用以和返回的解进行打擂台 
// 有了节点个数 就可以得到父树的最大子树平均和 然后返回出去 由于返回值的类型不再一样 所以要写成接口函数和分治函数

//1. 这道题使用分治 2. 这道题要求的返回值是节点 这无法直接合并返回解 因此必须拆分成分治函数和接口函数
//3. 分治实现中若需要打擂台找最值 可以设为外部全局变量 或设为辅助全局笔记本在参数中维护（一般分治实现没有其他参数 但这道题必须用接口函数 因此可以使用其他参数） 
//4. 这道题的比较过程略复杂 因此专门构建一个结构体来存储分治返回的解 进行比较 
    SubtreeResult* treeDivideConquer(TreeNode* root, SubtreeResult* maxResult)
    {
        SubtreeResult *currentResult; // 局部笔记本 即返回的解

        if(root == NULL)
        {
            return currentResult;
        }
        // 取得左右子树的解
        SubtreeResult *leftResult = treeDivideConquer(root->left, maxResult);
        SubtreeResult *rightResult = treeDivideConquer(root->right, maxResult);
        // 根据左右子树的解（树的平均和） 来计算本树的平均和
        int currentSum = leftResult->sum + rightResult->sum + root->value;
        int currentSize = leftResult->size + rightResult->size + 1;
        double currentAvg = currentSum / currentSize;
        // 比较本节点的均值 和 传入的最大均值 打擂台
        // 注意要考虑一开始最大值为空的情况
        // 若成功 则维护全局笔记本（节点指针和最大结果） 其实题目要求的解只有树根节点指针 理论上参数中的全局笔记本只需要树根节点指针 分治完成后也就得到解
        // 但多维护一个平均和节点 利于快速比较 否则还要写一个函数 根据树根节点求树的均值 
        if( maxResult == NULL || currentAvg > maxResult -> sum / maxResult -> size) 
        {
            maxResult->sum = currentSum;
            maxResult->size = currentSize;
            maxResult->head = root;
        }

        //返回局部笔记本(解)
        currentResult -> size = currentSize;
        currentResult -> sum = currentSum;
        currentResult -> head = root;
        return currentResult;
    } 

    TreeNode* maxAvgSubtree(TreeNode *root)
    {
        SubtreeResult *maxResult = NULL;
        SubtreeResult *temp = treeDivideConquer(root, maxResult);
        return maxResult->head;
    }
};
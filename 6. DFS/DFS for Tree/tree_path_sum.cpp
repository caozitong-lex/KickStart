// 二叉树dfs的遍历实现 —— 回溯 基本模板加入更多的额外参数 由于这些参数描述了树的局部性质 因此后序加入了回溯 
// 如果用分治 怎么解？
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};
//传入根节点和整数sum 找到所有根节点到叶节点的路径和为sum的路径 
// ‘找出所有’ -> dfs
class Solution
{
public:
// 遍历实现 即搜索每条路径 进行计算路径节点值的和 找到等于sum的路径就记录到路径集合中
// 全局笔记本是所有路径集合 递归函数的参数[基本参数，全局笔记本，额外信息参数]除了根节点 目标和的基本参数外 还有全局笔记本 
// 【这里的额外参数是辅助全局笔记本——当前路径 和当前路径和 还有一种层笔记本 记录每层的信息 如深度 往往层笔记本和辅助全局笔记本可以相互转化】
// 递归过程会记录每层的路径长度 和目标比较 然后更新笔记本
// 若还没到叶就已经超过sum 说明无需继续下探
    vector< vector<int> > pathSumByTraversal(TreeNode *root, int sum)
    {
        //构建解的数据结构/全局笔记本和辅助全局笔记本
        vector< vector<int> > pathSet;  //全局笔记本必须传应用 因为不返回结果 因此要在原笔记本上改动
        vector<int> currentPath;
        int currentSum = 0;

        treeRecursion(root, sum, pathSet, currentPath, currentSum);
        return pathSet;
    }
    void treeRecursion(TreeNode *root, int sum, vector< vector<int> > &pathSet, vector<int> currentPath, int &currentSum)    //这里currentpath和currentSum是辅助全局笔记本 但它的值完好的被传递 即使是传递副本 因此不是必须传引用
    {
        //遍历到该节点 首先判断是不是空节点
        if(root == NULL)
        {
            return;
        }
        currentPath.push_back(root->value);
        currentSum += root->value; 

        //更新完后 检查是不是符合路径要求的叶节点 如果是则记录该路径到集合中
        if(root->left == NULL && root->right == NULL && currentSum == sum) 
        {
            pathSet.push_back(currentPath);
        }
        //如果不是符合要求的叶节点 或 还没到叶节点 则继续递归子树探索路径 
        //注意额外参数都没有在传参时更新 而是写在外面 因为这些额外参数是辅助全局笔记本 而不是层笔记本
        //对于路径更新 xx.push / pop()返回的是void 因为push/pop没有返回值 而不是返回一个更新了的xx 
        //对于路径和更新 之前需要检查路径和 所以已经更新
        treeRecursion(root->left, sum, pathSet, currentPath, currentSum); //currentSum+root->value 局部参数的写法 
        treeRecursion(root->right, sum, pathSet, currentPath, currentSum);
        //这道题的核心操作是 后序的回溯部分 
        //这个算法没有剪枝 也就是不会提前因为 路径和已经超过sum而返回
        //在后序阶段 意味着节点即将返回到上一层 那么需要对路径和 以及路径 这两个参数进行回溯
        //因为这两个额外参数和 树的最大深度 这类参数不同 这类参数的范围是整棵树
        //而路径和 以及路径 的范围是每一条路径 这意味着 一旦进入了其他路径 就得修改当前的路径和sum 因为不适合其他路径
        //那么什么时候表明要进入其他路径？ —— 函数执行到后序。 表明左右子树进行遍历完 下一步就是返回上一层 试探其他支路
        //如何修改？弹栈。 比如对于路径来说 123 那么3即将返回到2 探索2的另一个节点4 那么123中当前节点3就得被弹出 路径和也要减去 再进入4 变成124
        //对于一路返回 如4作为2的右节点返回到2 2作为1的右节点直接返回到1 这样的情况同样适用 4弹出自己变成12 返回到2的函数 弹出自己变成1 
        //如何实现？ 路径和只需要加减即可 路径则需要一个栈 能够把后进的先弹出去 vector就可以 pushback和popback可以完成
        currentPath.pop_back();
        currentSum -= root->value;
        //如果想要省去回溯操作 那么将辅助全局笔记本写作层笔记本 在函数参数中更新 就不需要回溯 因为函数参数会和每个节点的绑定 反应的是每个节点的状态
        //而辅助全局笔记本则需要手动更新 
    }
};
// 分治很难写 因为难以合并子问题的解【*】 分治法的核心是能否合并左右递归返回的解
// 如果每次递归返回的是 符合要求的路径集合 那么当前路径的状态就必须要在参数中传递 而分治没有额外参数 这违背了分治的概念
// 所以分治的特性使得它能解决那些原子问题的解 和 父问题的解存在直接关系的问题 如树深 如遍历节点 而这道题没有这样的合并关系 没有一种关系是 树中满足和为x的路径集合?左右子树中满足和为x的路径集合
/*
vector< vector<int> > DcHelper (TreeNode *root, int sum, TreeNode *base)
{
    vector< vector<int> > pathSet;
    vector< vector<int> > currentPath;

    int currentSum = 0;

    if(root == NULL)
    {
        return pathSet;
    }

    vector< vector<int> > leftPathSet = DcHelper(root->left, sum, base);
    vector< vector<int> > rightPathSet = DcHelper(root->right, sum, base);

    for(int i = 0; i<leftPathSet.size(); i++)
    {
        leftPathSet[i].push_back(root->value);
        currentPath.push_back(leftPathSet[i]);
    }
    for(int i = 0; i<rightPathSet.size(); i++)
    {
        rightPathSet[i].push_back(root->value);
        currentPath.push_back(rightPathSet[i]);
    }

    for(int i = 0;i < leftPathSet.size(); i++)
    {
        int pathSumTemp = 0;
        for(int j = 0; j<leftPathSet[i].size(); j++)
        {
            pathSumTemp += leftPathSet[i][j];
        }
        if(pathSumTemp == sum && root == base)
        {
            pathSet.push_back(leftPathSet[i]);
        }
    }
    for(int i = 0;i < rightPathSet.size(); i++)
    {
        int pathSumTemp = 0;
        for(int j = 0; j<rightPathSet[i].size(); j++)
        {
            pathSumTemp += rightPathSet[i][j];
        }
        if(pathSumTemp == sum && root == base)
        {
            pathSet.push_back(rightPathSet[i]);
        }
    }
    return currentPath;
}
vector< vector<int> > pathSumByDC (TreeNode *root, int sum)
{
    vector< vector<int> >result;
    TreeNode *base = root;
    DcHelper(root, sum, base);
    return result;
    
}
*/



int main()
{
    TreeNode a(5);
    TreeNode b(4);
    TreeNode c(8);
    TreeNode d(11);
    TreeNode e(13);
    TreeNode f(4);
    TreeNode g(7);
    TreeNode h(2);
    TreeNode x(5);
    TreeNode y(1);

    a.left = &b;
    a.right = &c;
    b.left = &d;
    c.left = &e;
    c.right = &f;
    d.left = &g;
    d.right = &h;
    f.left = &x;
    f.right = &y;

    Solution s;
    vector< vector<int> > r = s.pathSumByTraversal(&a, 22);
    for(int i = 0; i<r.size(); i++)
    {
        for(int j= 0; j<r[i].size(); j++)
        {
            cout<<r[i][j]<< " ";
        }
        cout<<endl;
    }

    system("out");
    return 0;
}


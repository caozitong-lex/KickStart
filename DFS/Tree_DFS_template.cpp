#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#include<stack>

using namespace std;
/*
DFS的模板 包括：
1. 二叉树DFS的遍历实现
2. 二叉树DFS的分治实现 
3. 二叉树DFS的非递归实现
*/

//分治实现的关键在后序 取得左右子树递归返回的解之后 如何合并？
//遍历实现的关键在前序 和 参数部分 如何记录更新参数 如何维护全局笔记本  

// 二叉树节点的结构体
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};

//二叉树的DFS的简单实现
//因为不需要记录任何信息 只需要打印 所以没有返回值 参数只有根节点
//此时就是遍历实现 随着遍历过程一个一个生成输出结果 用不到分治实现 不存在结果的合并
void simpleTreeDFS(TreeNode *root)
{
    if(!root)
    {
        return;
    }

    cout<<root->value<<endl;
    simpleTreeDFS(root->left);
    simpleTreeDFS(root->right);
}


/*
dfs的实现有两种 遍历实现和分治实现
分治实现使用标准的输入和输出 通过递归的返回值传递局部笔记本
遍历实现由于递归不返回值 因此必须通过函数参数传递全局笔记本 而原函数没有该参数 因此必须多写一个接口函数
*/
//二叉树dfs的标准实现是传入根节点 返回遍历结果数组
// 二叉树DFS的遍历实现 
// 需要返回遍历结果 而递归函数不返回结果 且递归函数需要额外参数 因此分开为递归部分和接口部分 
void treeRecursion(TreeNode *root, vector<int> &traversalResult)
{
    if(root == NULL)
    {
        return;
    }
    //在前序填充笔记本
    traversalResult.push_back(root->value);

    treeRecursion(root->left, traversalResult);
    treeRecursion(root->right, traversalResult);
}
vector<int> treeDFSbyTraversal (TreeNode *root)
{
    vector<int> traversalResult; //构建笔记本
    treeRecursion(root, traversalResult); //把笔记本传入到递归函数中 引用传递在创建函数的参数列表指明即可
    return traversalResult; //递归结束后 笔记本被填写完成 返回
}

//二叉树的分治实现
//基于 一棵树的前序遍历 = 根节点 + 左子树的前序遍历 + 右子树的前序遍历
vector<int> treeDFSbyDC (TreeNode *root)
{
    vector<int> traversalResult; //声明局部笔记本
    if(root == NULL)
    {
        return traversalResult; //对于有返回值的函数 不能写return; 而要根据返回值类型返回
    }
    
    //在后序之前 递归左右子树 分解子问题并返回子问题的解
    vector<int> left = treeDFSbyDC(root->left);
    vector<int> right = treeDFSbyDC(root->right);
    //在后序合并子问题的解
    traversalResult.push_back(root->value); //把自身加入
    traversalResult.insert(traversalResult.end(), left.begin(), left.end()); //把左子树结果加入
    traversalResult.insert(traversalResult.end(), right.begin(), right.end()); //把右子树结果加入
    /*
    vector的拼接可以用insert或循环 循环效率较低
    for(int i = 0; i < left.size(); i++) //把左子树加入
    {
        traversalResult.push_back(left[i]);
    }
    for( int i = 0; i < right.size(); i++) //把右子树加入
    {
        traversalResult.push_back(right[i]);
    }
    */
    //返回的是局部笔记本的副本 为什么不返回局部笔记本的引用或指针呢？
    //没有意义 递归函数中创建的变量会在每一层递归函数中创建 传指针也起不到节省空间的作用 并且也不能简化代码 
    //即使可以只在底层的节点创建笔记本 也没什么意义 因为分治是并行的 也就是原子解都需要一个笔记本 即使父节点不创建笔记本 拿到了左右子树的笔记本 也还是要处理合并 
    return traversalResult; 
}

//二叉树DFS的非递归实现
//和BFS很像
vector<int> treeDFSbyNonRec(TreeNode *root)
{
    //辅助数据结构 结果数组和递归栈
    vector<int> traversalResult;
    stack<TreeNode*> recurStack;

    if(root == NULL)
    {
        return traversalResult;
    }
    
    recurStack.push(root);  //根节点入栈 开始循环

    while(!recurStack.empty())
    {
        //取顶 记录 - 出栈
        TreeNode *top = recurStack.top(); //取顶
        traversalResult.push_back(top->value); //记录
        recurStack.pop(); //出栈
        //检查子节点分解 - 入栈
        if(top->left)
        {
            recurStack.push(top->right);
        }
        if(top->right)
        {
            recurStack.push(top->left);
        }
    }  
    return traversalResult;
}






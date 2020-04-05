/*
二叉树的层级遍历
传入二叉树根节点 返回从右侧观察该树的节点数组
*/

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

/*
树的层级遍历的基础上 在每层循环展开节点前 把每层当前的最后一个数放入结果数组 搭配一个数据结构vector作为结果数组 
*/
class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        // 初始化数据结构
        queue<TreeNode*> treeQueue; //bfs队列
        vector<int> results; //侧面观察结果数组 
        treeQueue.push(root); //根节点入队 开启循环

        while(!treeQueue.empty())
        {
            int levelSize = treeQueue.size(); //获得每层的元素个数 用于层级遍历
            results.push_back(treeQueue.back()->value); //此处是处理每层元素（出队分解）前 因此此时每层的队尾就是右侧面观察到的元素 
            for(int i = 0; i < levelSize; i++) //循环处理每层的元素 检查分解 -> 入队构造下一层
            {
                TreeNode *head = treeQueue.front();
                treeQueue.pop();
                
                if(head->left)
                {
                    treeQueue.push(head->left);
                }
                if(head->right)
                {
                    treeQueue.push(head->right);
                }
            }
        }
        return results;
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
    vector<int> result = s.rightSideView(&a);
    for (int i = 0; i < result.size(); i++)
    {
        cout<<result[i]<<endl;
    }
    system("out");
    return 0;
}
/*
二叉树的标准遍历
二叉树的序列化 传入二叉树根节点 返回序列化结果 字符数组 即层次遍历节点 空节点记为#
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

char pound = '#';

struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):value(x), left(NULL), right(NULL){}
};

/*
在二叉树bfs的基础上 调整了记录操作的顺序 每次节点入队时 就绑定记录操作 而不是在取头时记录 本质相同 只是记录的时机不同 取头时记录的代码更简洁
这是因为不需要把#做成节点入队 也可以按照原来的思路 但每次要把#做成一个节点 修改节点node 把value定义为char

*/

class Solution
{
public:
    vector<char> serialization(TreeNode *root)
    {
        queue<TreeNode*> treeQueue;
        vector<char> results;

        treeQueue.push(root);
        results.push_back(root->value + '0'); //结果是字符串 数字转化为字符 
        
        while(!treeQueue.empty())
        {
            TreeNode *head = treeQueue.front();
            treeQueue.pop();

            if(head->left)
            {
                treeQueue.push(head->left);
                results.push_back(head->left->value + '0');
            }
            else
            {
                results.push_back(pound);
            }
            if(head->right)
            {
                treeQueue.push(head->right);
                results.push_back(head->right->value + '0');
            }
            else
            {
                results.push_back(pound);
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
  
    Solution s;
    vector<char> result = s.serialization(&a);
    for (int i = 0; i < result.size(); i++)
    {
        cout<<result[i]<<endl;
    }
    system("out");
    return 0;
}


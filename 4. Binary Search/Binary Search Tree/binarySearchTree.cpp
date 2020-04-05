#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
/*
二分搜索树类的常用方法：
节点插入
遍历
*/
struct btsNode
{
    int value; 
    btsNode* left;
    btsNode* right;
    btsNode(int x): value(x), left(NULL), right(NULL){}
};

// 二分搜索树的插入
void bts_Insert(btsNode* currentNode, btsNode* insertNode)
{
    if(insertNode -> value < currentNode -> value)
    {
        if(currentNode -> left)
        {
            bts_Insert(currentNode -> left, insertNode);
        }
        else
        {
            cout << insertNode<< ":" << insertNode -> value << " has been placed!" << endl;
            currentNode -> left = insertNode;
        }
    }
    else
    {
        if(currentNode -> right)
        {
            bts_Insert(currentNode ->right, insertNode);
        }
        else
        {
            cout << insertNode<< ":" << insertNode -> value << " has been placed!" << endl;
            currentNode -> right = insertNode;
        }
    }
}

void midorder_print(btsNode* root)
{
    if(!root)
    {
        return;
    }
    /*
    for(int i = 0; i < layer; i++)
    {
        cout << "---";
    }
    */
    cout << root << ":" << root -> value << endl;
    midorder_print(root -> left);
    midorder_print(root -> right);
}

int main()
{
    btsNode root(8);
    vector<btsNode*> node_vec;
    int test[] = {3,10,1,6,15};
    for(int i = 0; i < 5; i++)
    {
        node_vec.push_back(new btsNode(test[i]));
    }
    for(int i = 0; i < node_vec.size(); i++)
    {
        bts_Insert(&root, node_vec[i]);
    }
    midorder_print(&root);
}
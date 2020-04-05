#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;
/*
bfs的函数模板 包括：
1. 二叉树的bfs：数据结构：节点队列 入根后while 取头-处理-弹出-分解-入队 检查的是子节点是否存在
2. 图的bfs：数据结构：队列+哈希 二者操作绑定 可用数组或map实现 入根（更新哈希） 更新哈希后while 取头-处理-弹出-分解-入队（更新哈希） 检查的是邻接节点是否被访问 
// 注意 处理和取头绑定 哈希和入队绑定 其实哈希和处理 都可以和 取头/入队任意绑定 因为每个入队的节点都会经历一次 入队-出队
3. 图的bfs之层级遍历：区别是多了一层循环 需要提前取出当前层/队列的元素个数 不可以在循环中直接写 每次循环中队列尺寸会变化
(二叉树的层级遍历同理 在二叉树BFS上添加一个for循环实现层级即可 )
4. 矩阵/棋盘的bfs
*/
//——————————————————————————————————————————————————————
/*
树节点的结构体
*/
struct TreeNode
{
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): value(x), left(NULL), right(NULL){} //构造函数
};
/*
图节点的结构体
*/
struct GraphNode
{
    int value;
    vector<GraphNode* > neighbors; //邻接表 vector的元素是节点指针
    GraphNode(int x): value(x){}
};
//——————————————————————————————————————————————————————

/*
二叉树上的bfs
*/
void bfsTree(TreeNode *root) //传入树的根节点 进行遍历
{
    //数据结构初始化
    queue<TreeNode*> treeQueue; //队列中存储的是节点的指针
    //根节点入队 开启循环
    treeQueue.push(root);
    
    while(!treeQueue.empty())
    {
        //取头 -> 出队
        TreeNode *head = treeQueue.front();
        printf("[%d]\n", head->value);
        treeQueue.pop();

        //分解 -> 入队
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

/*
图上的bfs
实现和二叉树的区别 一个是入队时多了和hash操作的绑定 还有检查子节点的操作不同
传入的数组作为哈希表 图节点的值value作为索引 isVisited[value]上的值为0/1 表明未访问/已访问
*/
void bfsGraph(GraphNode* startNode, int isVisited[])
{
    //备用数据结构初始化
    queue<GraphNode* > graphQueue;
    //根节点入队 开启循环 注意队列push和hash更新永远绑定 
    graphQueue.push(startNode);
    isVisited[startNode->value] = 1;

    while(!graphQueue.empty())
    {
        //取队头->出队
        GraphNode *head = graphQueue.front();
        printf("[%d]", head->value);
        graphQueue.pop();

        //对每个子节点检查分解->入队
        for (int i = 0; i < head->neighbors.size(); i++) //vector有.size()方法
        {
            if (isVisited[head->neighbors[i]->value] == 0) //和二叉树不同 树节点直接从neighbor取子节点 不用确定在不在 但要确定是否出现过
            {
                //push和hash操作绑定 
                graphQueue.push(head->neighbors[i]);
                isVisited[head->neighbors[i]->value] = 1;
            }
        }
    }
}

/* 
图上的层级遍历bfs
实现上 层级体现在多了一个内循环
*/
void bfsHierGraph(GraphNode *startNode, int isVisited[])
{
    //初始化辅助数据结构
    queue<GraphNode* >graphQueue;
    //根节点入队 更新哈希
    graphQueue.push(startNode);
    isVisited[startNode->value] = 1;

    while(!graphQueue.empty())
    {
        int levelSize = graphQueue.size(); // 获得当前队列中带分解元素的个数 要提前取出 不能直接写在for中
        for(int i = 0; i < levelSize; i++) // 分解这些元素
        {
            // 取队头 -> 出队
            GraphNode *head = graphQueue.front();
            printf("[%d]\n", head->value);
            graphQueue.pop();
            // 对每个子节点检查分解 -> 入队 
            for(int j = 0; j < head->neighbors.size(); j++)
            {
                if(isVisited[head->neighbors[j]->value] == 0)
                {
                    graphQueue.push(head->neighbors[i]);
                    isVisited[head->neighbors[j]->value] = 1;
                }
            }
        }
    }
}




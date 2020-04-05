/*
图的最短路径
传入图节点的数量 起始节点和目标 找到图中的值为目标值的节点 返回节点
*/

#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<set>

using namespace std;

struct graphNode
{
    int value;
    vector<graphNode* > neighbors;
    graphNode(int x): value(x){} //冒号
};
/*
在标准图bfs的基础上 在取头时的记录/输出操作变成检查操作即可 检查是否是目标数 
这道题要求返回目标节点 如果要求路径长度 则使用分层图BFS即可 
*/
class Solution
{
public:
    graphNode* searchNode(int num, graphNode *startNode, int target)
    {
        queue<graphNode*> graphQueue;
        vector<int> isVisited; //参数没有提供访问哈希 就自己创建一个 和队列一起 记得初始化
        for(int i=0; i<num; i++)
        {
            isVisited.push_back(0);
        }

        graphQueue.push(startNode);
        isVisited[startNode->value] = 1;

        while(!graphQueue.empty())
        {
            graphNode *head = graphQueue.front();
            if(head->value == target) //取头时检查是否为target
            {
                return head;
            }
            graphQueue.pop();

            for(int i = 0; i < head->neighbors.size(); i++)
            {
                if(isVisited[head->neighbors[i]->value == 0])
                {
                    graphQueue.push(head->neighbors[i]);
                    isVisited[head->neighbors[i]->value] = 1;
                }
            }
        }
        return NULL;
    } 
};

int main()
{
    //构造图框架 
    vector<graphNode*> graph;
    //构造点 从堆中实例化
    for(int i =0; i<5; i++)
    {
        graph.push_back(new graphNode(i));
    }
    /* 语法：考虑一下从栈中实例化
    for(int i =0; i<5; i++)
    {
        graphNode n(i); 
        graph.push_back(&n); 
        for(int j = 0; j < i; j++)
        {
            cout << graph[j] -> value;
        }
        cout << endl;
    }
    每次循环内声明变量n并赋值i 其实变量n的地址是同一个 相当于对同一个变量重新赋值 然后把同一个地址赋值给各个节点
    c++里相同作用域内 相同代号也代指着同一块地址 先后int a = 1, int a = 2 本质上始终是那个a 先被赋值为1 后被赋值为2
    如果这里每次从栈中实例化节点n 再pushback &n到图中 会产生一个问题 n相当于被重新赋值
    */
    //构造边
    graph[0]->neighbors.push_back(graph[4]);
    graph[0]->neighbors.push_back(graph[2]);
    graph[1]->neighbors.push_back(graph[0]);
    graph[1]->neighbors.push_back(graph[2]);
    graph[2]->neighbors.push_back(graph[3]);
    graph[3]->neighbors.push_back(graph[4]);
    graph[4]->neighbors.push_back(graph[3]);
    
    int target = 2;
    graphNode *startnode = graph[0];
    int num=5;

    Solution s;
    //graphNode *r = s.searchNode(num, startnode, target);
    //cout<<r->value<<endl;
    
    system("out");
    return 0;
}
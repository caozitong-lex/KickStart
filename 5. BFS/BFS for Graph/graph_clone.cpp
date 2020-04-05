#include<iostream>
#include<queue>
#include<stack>
#include<map>
#include<vector>
#include<set>
using namespace std;

/*
图的深度拷贝： 传入一个图的某节点 返回克隆图的一个节点
考察对图数据结构和指针的理解 

克隆分为三步：
1. 根据原图的节点 通过遍历dfs/bfs找到原图并返回 本质是一个节点指针数组 1，2，3，4
2. 克隆节点 克隆节点包括 
2.1新建图（即新建一个节点指针数组）
2.2在新建图中逐个实例化节点并赋值 值从哪里来？ 循环逐个取得原图各节点的value 1‘，2’，3‘，4’
2.3新建一个映射 当我们逐个取得原节点的value时 也新建了对应的克隆节点 此时将原节点-克隆节点 建立映射  1-1‘ 2-2’ 3-3‘ 4-4’
2.4图建立完成后 克隆图和原图在同顺序的节点上具有相同的值 接下来就是克隆点之间的关系
3. 克隆边 
3.1再次循环取得原图各节点的邻居 我们无法直接将新图对应节点的邻居赋值为原图的邻居 比如1有邻居3 那么1‘的邻居显然是3‘
3.2从映射中取得3的映射3’ 将3‘加入3的邻居即可

注意点和边的构建要分开 不要同时做两件事
*/

struct GraphNode
{
int value;
vector <GraphNode*> neighbors;
GraphNode(int x): value(x){}
};


vector<GraphNode*> getOriginalGraph(GraphNode* node)
{
    queue<GraphNode*> graphQueue;
    set<GraphNode*> visitHash;
    vector<GraphNode*> originalGraph; 

    graphQueue.push(node);
 
    while(!graphQueue.empty())
    {
        GraphNode* head = graphQueue.front();
        originalGraph.push_back(head);
        graphQueue.pop();
        visitHash.insert(head);

        for(int i = 0; i < head->neighbors.size() ; i++)
        {
            if(visitHash.find(head->neighbors[i]) == visitHash.end())
            {
                graphQueue.push(head->neighbors[i]);
            }
        }
    }

    return originalGraph;
}
    
GraphNode* graphClone(GraphNode* node)
{
    if(node == NULL)
    {
        return node;
    }
    //建立原图 新图 和节点映射
    map<GraphNode*, GraphNode*> nodeMapping;
    vector<GraphNode*> originalGraph = getOriginalGraph(node);
    vector<GraphNode*> cloneGraph;
    //克隆点 包括实例化 取值赋值 建立映射
    for(int i = 0; i < originalGraph.size(); i++)
    {
        cloneGraph.push_back(new GraphNode(originalGraph[i]->value));
        nodeMapping[originalGraph[i]] = cloneGraph[i];
    }
    //克隆边 包括取边 映射 添加边
    for(int i = 0; i < originalGraph.size(); i++)
    {
        for(int j = 0; j < originalGraph[i]->neighbors.size(); j++)
        {
            cloneGraph[i]->neighbors.push_back(nodeMapping[originalGraph[i]->neighbors[j]]);
        }
    }
    return cloneGraph[0];
}
int main()
{
    //构造图框架 
    vector<GraphNode*> graph;
    vector<GraphNode*> clone;
    //构造点 从堆中实例化
    for(int i =0; i<5; i++)
    {
        graph.push_back(new GraphNode(i));
    }
    //构造边
    graph[0]->neighbors.push_back(graph[1]);
    graph[0]->neighbors.push_back(graph[2]);
    graph[0]->neighbors.push_back(graph[4]);
    graph[1]->neighbors.push_back(graph[0]);
    graph[2]->neighbors.push_back(graph[0]);
    graph[4]->neighbors.push_back(graph[0]);

    graph[1]->neighbors.push_back(graph[3]);
    graph[3]->neighbors.push_back(graph[1]);

    GraphNode* newNode = graphClone(graph[0]);
    clone = getOriginalGraph(newNode);
    
    for(int i = 0; i < graph.size(); i++)
    {
        cout << graph[i] << ":" << graph[i] -> value << " - " ;
        cout << clone[i] << ":" << graph[i] -> value << " - ";
    }

    system("out");
    return 0;
}
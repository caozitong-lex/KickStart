/*
图的BFS: 拓扑排序 
传入课程数 整数对数组表明依赖关系 返回是否合理
区别是1. 自己构造图和哈希/入度表 2. 没有start 初始时所有0度节点入队  3. 不检查哈希表 而是检查入度表即可 
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

/*
这种节点可以用于构造有向图和无向图 
无向图只要在构造的时候 1的neighbor加了2 2就要在neighbor中加1 
如果2没加1 那么就是单向图
图的标准bfs是基于无向联通图的 这样可以保证从起点出发能遍历整张图
而单向图则无法保证 bfs题目都是绝大多是无向图 更能体现bfs的特点
拓扑排序就是少有的有向图题  
*/
struct graphNode
{
    int value;
    vector<graphNode* > neighbors;
    graphNode(int x): value(x){}
};
/*
标准图bfs的参数是起始点和访问哈希表 这道题中都需要自己构造 (图 哈希 队列)
这道题需要根据课程关系和课程数量 自己构造出有向图 即子节点指针数组 
拓扑排序中 不需要使用访问哈希表 而是使用入度哈希表 也需要自己构造
具体的 由于题目没有给定图以及节点的排列 因此我们直接把图构建为节点数组 并且下标和节点值相同 因此可以用下标来索引节点 入度表同理（哈希表一直是下标 == 节点值 直接用下标取到该值的节点 更新访问状态/入度）
正常bfs问题中 我们不需要知道节点数组的下标 和 某个节点的关系 因为我们不需要找到某个特定value的节点 但这道题中 构建图时 我们有了依赖关系 需要方便的取到某个特定value的节点更新它的邻接点 因此需要把索引和节点值统一 或者直接使用数组方式或map方式（词语阶梯）可以方便索引
因此 需要自己建图的问题 都需要把值和索引统一因为需要取到某个特定值的节点
这道题也可以直接用二维数组来建图 索引是节点值 值是节点的邻接点数组 
*/

class Solution
{
public:
    bool courseSchedule(int numCourse,  vector< pair<int, int> > &prerequisites)
    { 
        //必要数据结构初始化
        vector<graphNode*> graph;   //初始化图的框架
        vector<int> degree;         //入度数组是整数
        queue<graphNode*> graphqueue;

        //构造图 和 初始化入度数组 
        //构造点 初始化入度数组 所有节点入度初始化为0 注意不能用下标赋值 必须用pushback 初始化图为各个节点指针组成的数组 节点值为 1-n的数字
        for(int i = 0; i < numCourse; i++)
        {
            degree.push_back(0); //初始状态下所有节点入度为0
            graph.push_back(new graphNode(i)); //填充图的点 节点值按顺序排列
        }
        //建图这部分可以放入另一个辅助函数中
        //构造边 根据课程关系 构造图的边和入度数组（题目说了pre中有numCourse对pair）
        for(int i = 0; i < numCourse; i++)
        {
            //取得依赖关系
            //pair通过.first/second属性取得其中的元素 这里就是获得节点值 
            graphNode *begin = graph[prerequisites[i].second]; //取得节点
            graphNode *end = graph[prerequisites[i].first]; //[1,2]表明1依赖2 也就是2->1
            //构造图 即加入子节点 
            begin->neighbors.push_back(end);
            //构造入度数组 即被指向的节点的入度加一
            degree[prerequisites[i].first]++;
        }

        //开始bfs部分
        //和图bfs把startnode加入队列不同 拓扑排序把所有入度为0的点加入队列
        for (int i = 0; i < numCourse; i++)
        {
            if(degree[i] == 0)
            {
                graphqueue.push(graph[i]);
            }
        }
        //循环
        while(!graphqueue.empty())
        {
            //取队头 - 出队
            graphNode *head = graphqueue.front();
            graphqueue.pop();
            //检查子节点分解 - 入队
            //检查所有子节点时 从检查访问哈希变成了入度哈希 
            //若子节点入度不为0无法入队 还需要把入度减1 而标准图bfs则是修改入队的节点的访问哈希
            //Review：对所有子节点的入度一开始都要减一 表明它们的父节点已经弹出被分解 然后再检测入度
            for(int i = 0; i < head->neighbors.size(); i++)
            {
                degree[head->neighbors[i]->value]--;
                if(degree[head->neighbors[i]->value]==0)
                {
                    graphqueue.push(head->neighbors[i]);
                }
            }
        }
        //当所有节点进出节点后 检查入度哈希是否存在非0元素
        for(int i = 0; i < numCourse; i++)
        {
            if(degree[i])
            {
                return false;
            }
        }
        return true;
    } 
};

int main()
{
    vector<pair<int, int> >pre;
    pre.push_back(make_pair(1,0));
    pre.push_back(make_pair(2,0));
    pre.push_back(make_pair(3,1));
    pre.push_back(make_pair(3,2));
    Solution s;
    cout<<s.courseSchedule(4, pre);
    system("out");
    return 0;
}
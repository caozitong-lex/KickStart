#include<iostream>
#include<vector>
#include<queue>
using namespace std;


/*
给定矩阵 起点坐标和目标终点坐标 其中0是可落脚点 1是不可落脚点 走日字形 从起点到终点最少跳几步 
经典的矩阵最短路径bfs 和更新哈希的时机一样 检查点是否为目标的时机可以放在出队也可以放在入队 都相同 但建议都放在出队 只需要写一次 入队需要写两次 因为初始化时头节点入队也要写 
这里哈希没有使用原矩阵 专门新建了一个哈希矩阵 用以练习不同方法实现
*/
const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int knightShortestPath(vector< vector<int> > &grid, pair<int, int> start,  pair<int, int> end)
{
    int width = grid[0].size();
    int length = grid.size();
    int steps = 0;
    queue< pair<int, int> > matrixQueue;
    vector< vector<int> > matrixHash(grid.size(), vector<int>(grid[0].size()));
    matrixQueue.push(start);
    
    while(!matrixQueue.empty())
    { 
        int levelSize = matrixQueue.size();
        for(int i = 0; i < levelSize; i++)
        {
            pair<int, int> currentPoint = matrixQueue.front();
            if(currentPoint.first == end.first && currentPoint.second == end.second)
            {
                return steps;
            }
            matrixQueue.pop();
            matrixHash[currentPoint.first][currentPoint.second] = 1;

            for(int j = 0; j < 8; j++)
            {
                int newX = currentPoint.first + dx[j];
                int newY = currentPoint.second + dy[j];
                if(newX < 0 || newY < 0 || newX >= width || newY >= length)
                {
                    continue;
                }
                if(matrixHash[newX][newY] == 0)
                {
                    matrixQueue.push(make_pair(newX, newY));
                }
            }
        }
        steps ++;
    }
}
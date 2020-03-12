#include<iostream>
#include<map>
#include<queue>
using namespace std;

/*
传入一个矩阵 其中0 1 2代表人 僵尸  墙 每个僵尸每天可以把邻近（上下左右）的人都变成僵尸 人类全部消失需要多少天
bfs的扩散过程类似水波纹的扩散 这里的僵尸感染也类似这个过程
这里的一天 指的就是bfs中的一次层次bfs 即取队-出队-对邻接节点的检查入队的过程
只不过初始化时 不是从一个节点开始扩散遍历 而是从多个节点同时开始 传染四周的人后 被传染的人继续传染四周的人 直到所有遍历到的人被传染 这就是一次BFS过程
这道题非常形象的展示了BFS的一次过程 就是逐层传染的过程 只不过这道题的特色是 【多起点层次遍历bfs】只需要在bfs框架处修改初始化队列的部分即可
其实不需要额外创建哈希 因为我们可以直接修改原矩阵 遍历到的人修改为僵尸即可 
另一个实现的细节时 由于每天传染/每层遍历都要考虑到人类数量是否为0 不需要每次遍历整个矩阵统计人类数量 而是一开始记录人类数量 当访问到一个人 就维护这个人类数量变量 -1即可

而小岛题中对bfs过程进行延伸 由于存在离散的区域 也就是多个面 这就使得由点及面的过程要多次进行 每次感染一个面 那么感染的次数就是小岛的个数 
*/

const int dx[] = {0, 0, -1, 1};
const int dy[] = {1, -1, 0, 0};
const int PEOPLE = 0;
const int ZOMBIE = 1;
const int WALL = 2;


int zombieMatrix(vector< vector<int> > &grid)
{
    int width = grid[0].size();
    int length = grid.size();
    int days = 1;
    int people = 0;
    //创建并将多个起点入队 顺便统计人类数量
    queue< pair<int, int> > matrixQueue;
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < length; j++)
        {
            if(grid[i][j] == ZOMBIE)
            {
                matrixQueue.push(make_pair(i, j));
            }
            if(grid[i][j] == PEOPLE)
            {
                people ++;
            }
        }
    }

    //bfs
    while(!matrixQueue.empty())
    {
        cout << "======================感染第" << days <<"天！=========================" << endl;
        int levelSize = matrixQueue.size();
        cout << "当前即将感染人的僵尸数量：" << levelSize << endl; 
        for(int i = 0; i < levelSize; i++)
        {
            pair<int, int> point = matrixQueue.front();
            matrixQueue.pop();
            grid[point.first][point.second] = ZOMBIE;

            for(int j = 0; j < 4; j++)
            {
                int newX = point.first + dx[j];
                int newY = point.second + dy[j];
                cout << "当前僵尸坐标：" << point.first << "," << point.second << endl;
                cout << "尝试感染：" << newX << "," << newY << endl;
                if(newX < 0 || newY < 0 || newX >= width || newY >= length)
                {
                    cout << "当前位置不可取！" << endl;
                    continue;
                }
                if(grid[newX][newY] == PEOPLE)  //四周为人类才可以继续遍历
                {
                    cout << "感染成功" << endl;
                    matrixQueue.push(make_pair(newX, newY));
                    grid[newX][newY] = ZOMBIE;  //更新哈希 人类改为僵尸 表明传染
                    people--;
                    if(people == 0)
                    {
                        return days;
                    }
                }
                else
                {
                    cout << "对象非人类，无法感染！" << endl;
                }
            }
        }
        days++; 
    }
    return -1;
}

int main()
{
    // 构造地图的时候 由于地图是个二维vector 因此不能直接赋值 要循环一个一个push 从另一个字符二维数组中push
    vector< vector<int> > grid;
    int matrix[3][3] = {{1,0,0},{0,2,0},{0,0,1}};
    for(int i = 0; i<3; i++)
    {
        grid.push_back(vector<int>());
        for(int j = 0; j<3; j++)
        {
            grid[i].push_back(matrix[i][j]);
        }
    }
    cout << zombieMatrix(grid);
    return 0;
}
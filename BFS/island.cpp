/*
矩阵的灌水法（由点到面）

*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*
基本思路是多次bfs bfs部分中 每一次bfs都是一个点的全力扩张 利用漫水的性质来标记矩阵
接口部分中 则利用bfs的结果来计算bfs的次数 作为解
bfs部分中访问哈希仍然需要自己构造 但不需要构造图 因为矩阵形式的bfs的邻接点是现成的 上下左右的点就是邻接点 
//接口部分
· 题目需要自己构造访问哈希 即二维vector的构造 双重循环push back
· 对于所有二维地图上的未访问的小岛点 都以这个点开始进行bfs 每次bfs完 访问哈希就会在bfs的过程中被更新 表明找到一个岛 并记录数量 当找不到未访问的小岛点 也就表明所有岛被找到
· 这道题的哈希充当了两个作用 首先是每次bfs过程的哈希 检查是否有重复遍历 其次 由于多次bfs之间共用这个哈希（每次bfs遍历的区域面之间是离散的 所以遍历过的点不会在其他bfs中被遍历）这个哈希可以用来检测整张图中是否还有未被遍历的小岛
  但其实也不需要额外创建哈希 可以直接利用地图  把遍历的小岛点设置为海面点 能起到相同的作用 
// bfs部分
· 方向数组 不使用vector 因为方向数组不需要修改 直接使用整数数组
· bfs队列中存储的不再是二叉树的节点 或图的节点 而是一个 pair 但我们也不需要特定写一个节点类 因为可以直接用pair
· 把出发点x 和y组成我们想要的 节点类型 使用make_pair(x,y)
· 和图bfs一样 给定了访问哈希 和 出发点 一开始头节点入队 标记 并修改哈希 哈希是二维的
· 取队头时 不需要取得节点类型(x,y) 我们需要的是x 和 y 然后出栈
· 分解时 通过x y和方向数组找到4个子节点
· 检查时 第一重检查子节点有没有越界 出地图 
· 第二重检查访问状态 以及是不是岛屿 因为矩阵中点都是四联通的 相当于二叉树中都是满二叉树 题目往往会让有些点无效 这样就和树/图一样 需要判断左右节点存不存在 或 有哪些邻接点
· 检查通过 入队时再转化为节点类型(x,y) 并更新访问哈希
//测试部分
·构造地图的时候 由于地图是个二维vector 因此不能直接赋值 要双重循环一个一个push 从另一个初始化好了的字符数组中push

总之 思路都没变 核心是节点的类型变化 (x,y) 导致了
队列的类型变化（存储了pair） 哈希的变化（一维变二维） 节点入队的变化（入(x,y)） 取队头的变化（取x和 y） 分解的变化（方向数组） 检查的变化（双重检查:检查 访问与否以及节点是否可访问） 
*/


class Solution
{
public:
    void spreadByBFS (vector< vector<int> > &mark, vector< vector<char> > &grid, int x, int y)
    {
        //初始化队列 哈希在接口函数中实现
        //构建方向数组 由于是常量数组 不初始化为vector 直接用整数数组即可
        const int dx[] = {-1, 1, 0, 0}; 
        const int dy[] = {0, 0, -1, 1};
        //bfs的队列 这里给定了起始点x y 和访问哈希mark 注意队列存储的是pair 是个坐标
        queue<pair<int, int> > matrixQueue;

        //开始bfs
        //出发点入队并标记
        matrixQueue.push(make_pair(x, y));
        //mark[x][y] = 1; //此时可以下标赋值 因为不是空的

        while(!matrixQueue.empty())
        {
            //取队头 - 出队
            int headX = matrixQueue.front().first;
            int headY = matrixQueue.front().second;
            matrixQueue.pop();
            mark[headX][headY] = 1; //取队头时标记和入栈时绑定标记的效果相同 取队头时标记更简洁

            //检查分解子节点-入队
            for(int i = 0; i < 4; i++)
            {
                //移动头节点 找到子节点 
                int newX = headX + dx[i];
                int newY = headY + dy[i];

                //检查边界
                if(newX < 0 || newX >= mark.size() || newY < 0 || newY >= mark[newY].size()) //mark.size是行数 mark[newY].size是列数 
                {
                    continue;
                }
                //检查访问状态和有效性
                if(mark[newX][newY] == 0 && grid[newX][newY] == '1')
                {
                    matrixQueue.push(make_pair(newX, newY));
                }
            }
        }

    }
    int numIsland(vector< vector<char> > &grid)
    {
        //初始化辅助变量小岛数 
        int numOfIsland = 0;
        //声明并初始化访问标记矩阵 初始化为0 表明未访问
        //二维矩阵vector的声明和初始化方法 
        //注意不能在空的时候用下标赋值 而要用pushback 同理适用于所有vector的初始化 如isVisit degree等
        vector< vector<int> > mark(grid.size(), vector<int>(grid[0].size()));
        
        //检查所有未访问小岛点 以此为出发点进行bfs
        for(int i = 0; i < grid.size(); i++)
        {
            for(int j = 0; j < grid.size(); j++)
            {
                if(mark[i][j] == 0 && grid[i][j] == '1')
                {
                    spreadByBFS(mark, grid, i, j);
                    numOfIsland++;
                }
            }
        }
        return numOfIsland;
    }
};

int main()
{
    // 构造地图的时候 由于地图是个二维vector 因此不能直接赋值 要循环一个一个push 从另一个字符二维数组中push
    vector< vector<char> > grid;
    char str[10][10] = {"11100", "11000", "00100", "00011"};
    for(int i =0; i<4; i++)
    {
        grid.push_back(vector<char>());
        for(int j = 0; j<5; j++)
        {
            grid[i].push_back(str[i][j]);
        }
    }
    Solution s;
    cout<<s.numIsland(grid);
    return 0;
}

// 数组/矩阵的DFS
#include<iostream>
#include<vector>
using namespace std;
// 传入n 表明边长为n的矩阵 返回所有棋盘 每个棋盘都是合法的放置 皇后用Q表示 空位用 . 表示
// n*n的矩阵可以看做n高的n叉树 每一行的放置都有n种尝试 当测试到最后一行 表明合法的棋盘完成 就可以记录 
// 递归部分的总体架构就是  在前序记录解 在后序需要回溯 包括当前棋盘和访问矩阵 随后随着函数结束回到上一层 
// 实现使用了接口函数和递归函数 多出的访问矩阵相当于遍历过程中的剪枝
class Solution
{
public:
//该函数模拟放置皇后之后 访问矩阵的更新 
    void placeQueen(int x, int y, vector< vector<int> > &mark)  
    {
        //方向数组 常数组 {}初始化
        const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
        const int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};
        //放置皇后
        mark[x][y] = 1;
        //将皇后的横竖斜方向上的点全部记录为1
        for(int i = 0; i < mark.size(); i++) //移动次数 每个方向上最多移动边长次
        {
            for(int j = 0; j < 8; j++) //移动方向 八个方向 
            {
                int newX = x + i * dx[j]; //移动x
                int newY = y + i * dy[j]; //移动y
                if(newX >= 0 && newX < mark.size() && newY >= 0 && newY < mark.size()) //检测移动后是否出界
                {
                   mark[newX][newY] = 1; //未出界则标记
                }
            }
        }
    }
//基本参数 n 全局笔记本（题解）所有合法放置 辅助全局笔记本 当前放置和访问矩阵 额外参数当前行数 相当于树/图遍历时的层 
    void matrixRecursion (int n, vector< vector<string> > &allPlace, vector< string > &currentPlace, vector< vector<int> > &mark, int level)
    {
        //当递归到最后一层+1时 表明全部皇后被放置完成 记录结果 后返回
        //树/图中使用 root == NULL检测 数组/矩阵中则需要记录额外参数深度 
        if(level == n)
        {
            allPlace.push_back(currentPlace);
            return;
        }
        for(int i = 0; i < n; i++) //递归部分 每层/行 放置有四个选择 相当于四个子节点 对每个子节点进行递归
        {
            if(mark[level][i] == 0) //当前点可放
            {
                vector< vector<int> > markCopy = mark; //复制访问状态矩阵

                currentPlace[level][i] = 'Q'; //放置 更新棋盘
                placeQueen(level, i, mark); //更新访问状态矩阵

                matrixRecursion(n, allPlace, currentPlace, mark, level + 1); //遍历每个节点相当于遍历每棵子树 level是额外参数 记录每层的深度 使到达最后一层时能终止

                currentPlace[level][i] = '.'; //尝试完当前子节点 在后序回溯
                mark = markCopy;
            }
        }
    }

//接口函数中创建并初始化全局笔记本 包括题解 即所有合法棋盘 
//辅助全局笔记本currentPlace表示当前棋盘 记录解的构造过程  mark用来检测当前解的构造是否合法 （额外参数指那些只在函数参数中修改的参数） 
    vector< vector<string> > NQueens(int n)
    {
        vector< vector<string> > allPlace;
        vector< string > currentPlace;
        vector< vector<int> > mark;

        //初始化访问矩阵和当前棋盘 
        //访问矩阵对棋盘每个点设置为0 表明可放置  二维vector的初始化
        //当前棋盘则每个点设置为 .  string的vector的初始化
        for(int i = 0; i < n; i++)
        {
            mark.push_back(vector<int>());
            for(int j = 0; j < n; j++) //每行填充0
            {
                mark[i].push_back(0);
            }

            currentPlace.push_back(""); // vector的元素是字符串 加入一个空串
            currentPlace[i].append(n, '.'); //在空串后连接n个 . 这是string的方法   
        }
        //传入到递归函数中 递归结束后 会自动填充解
        matrixRecursion(n, allPlace, currentPlace, mark, 0); //从第0行开始 相当于根节点
        return allPlace;
    }
};

int main()
{
    vector< vector<string> > allplace;
    Solution s;
    allplace = s.NQueens(5);
    cout<<allplace[0].size()<<endl;
    for(int i = 0; i < allplace.size(); i++)
    {
        for(int j = 0; j<allplace[i].size(); j++)
        {
            cout<<allplace[i][j].c_str()<<endl;
        }
        cout<<endl;
    }
    system("pause");
    return 0;
}

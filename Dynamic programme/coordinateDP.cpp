#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//在三角形/矩阵中的坐标dp 先考虑从上到下和从下到上是否等价 考虑实现方便的方向 矩阵/三角形 从上到下的路径长度 和从下到上的路径长度 是等价的
// 然后考虑坐标出界的情况 一般起点都是边界
class Solution
{
public:
    int minPathInTriangle(vector< vector<int> > &triangle)
    //传入一个三角形矩阵 求三角形顶端到底端各数字的路径和中 最小的路径和 可走的方向为向下相邻的两位置
    //状态转移为 dp[x][y]表明起点到该点的最短路径 等于起点到[x+1,y+1] [x, y+1]的路径的较小值加上[x,y]值
    {
        if(triangle.size() == 0)
        {
            return 0;
        }
        vector< vector<int> > dp; //状态设定为 dp[x][y]为该点到底端的最短路径
        for(int i = 0; i < triangle.size(); i++) //初始dp矩阵 复制三角形 并赋值为0
        {
            dp.push_back(vector<int>());
            for(int j = 0; j < triangle[i].size(); j++)
            {
                dp[i].push_back(0);
            }
        }
        //构造边界 最后一层节点的dp就是那一层的节点值
        for(int i = 0; i < dp.size(); i++)
        {
            dp[dp.size() - 1][i] = triangle[dp.size() - 1][i];
        }
        //状态转移 自下而上 自左向右填充
        for(int i = dp.size() - 2; i >= 0; i--)
        {
            for (int j = 0; j < dp.size(); j++)
            {
                dp[i][j] = min(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j] ;
            }
        }
        //返回解
        return dp[0][0];
    }  

    int minPathInRectangle(vector< vector<int> >&rectangle)
    //传入二维数组 求出从左上角到右下角的最短路径和 方向只能向下或向右
    //状态转移为 dp[x][y]表明左上点到该点的最短路径 等于左上点到[x-1,y] [x, y-1]的路径的较小值加上[x,y]值
    {
        if(rectangle.size() == 0)
        {
            return 0;
        }
        //初始化状态矩阵
        vector< vector<int> > dp;
        for(int i = 0; i < rectangle.size(); i++)
        {
            dp.push_back(vector<int>());
            for(int j = 0; j < rectangle[i].size(); j++)
            {
                dp[i].push_back(0);
            }
        }
        // 边界
        dp[0][0] = rectangle[0][0];
        //状态转移 边界部分特殊考虑 
        //左竖边的状态填充
        for(int i = 1; i < rectangle.size(); i++)
        {
            dp[i][0] = rectangle[i][0] + dp[i - 1][0];
        }
        //上横边的状态填充 
        for(int i = 1; i < rectangle[0].size(); i++)
        {
            dp[0][i] = rectangle[0][i] + dp[0][i - 1];
        }
        //中心区域的状态填充
        for(int i = 1; i < rectangle.size(); i++)
        {
            for(int j = 1; j < rectangle[i].size(); j++)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j-1]) + rectangle[i][j];
            }
        }

        //返回解
        return dp[rectangle.size() - 1][rectangle[0].size() - 1];
    }
};

    

int main()
{
    vector< vector<int> > triangle;
    //int test[][10] = {{2}, {3,4}, {5,6,7},{4,1,8,3}}; //二维数组方便构造样例  
    int test[][3] = {{1,3,1},{1,5,1},{4,2,1}};
    for(int i = 0; i < 3; i++) //vector方便算法实现 为了传入 vector 需要循环复制二维数组到vector中
    {
        triangle.push_back(vector<int>());
        for(int j = 0; j < 3; j++)
        {
            triangle[i].push_back(test[i][j]);
        }
    }
    Solution s;
    cout << s.minPathInRectangle(triangle);
}
#include<iostream>
#include<vector>
using namespace std;

/*
传入一个01矩阵 其中所有的1相连 找到一个子矩阵 能够覆盖所有的1 返回它的最小面积
由于是求子矩阵 因此需要得到左右上下的四个边界
对于每列 若有1则标记为1 否则标记为0 则每列的情况可以用 00011110表示 
同理 每行可以用
0
0
1
1
1
0
表示 我们需要找到每个维度上的第一个1和最后一个1
那么这就是一个典型的ooxx问题 只不过像二分法的求区间问题一样 我们需要找到横向上的区间 以及纵向上的区间
所以 重复四遍过程
这道题能够体现ooxx的核心 那就是对于一个序列 如果能分成前后的两类 就可以进行查找到某类的第一个/最后一个
前后关系可以帮助找到任何一个满足条件的元素 两类则可以帮助找到第一个/最后一个满足条件的元素

由于在这样的ooxx问题中 二分法的判断操作需要判断列/行中是否存在0/1 这是一个O(n)的判断操作 因此最终时间复杂度为 O(nlogn

*/

bool includeOne(vector< vector<int> > matrix, int index, int dimension)
{
    if(dimension == 1)  //列
    {
        for(int i = 0; i < matrix.size() - 1; i++)
        {
            if(matrix[i][index] == 1)
            {
                return true;
            }
        }
    }
    else               //行 
    {
        for(int i = 0; i < matrix[0].size(); i++)
        {
            if(matrix[index][i] == 1)
            {
                return true;
            }
        }
    }
    return false;
}


int minSquareCover1(vector< vector<int> > matrix)
{
    int verticalStart1 = 0;
    int verticalStart2 = 0;
    int verticalEnd1 = matrix[0].size() - 1; //行长
    int verticalEnd2 = matrix[0].size() - 1;
    int horizonStart1 = 0;
    int horizonStart2 = 0;
    int horizonEnd1 = matrix.size() - 1;     //列深
    int horizonEnd2 = matrix.size() - 1;
    int upperBound, bottomBound, leftBound, rightBound;

    // 找到左边界
    while(verticalStart1 + 1 < verticalEnd1)
    {
        int verticalMid1 = (verticalStart1 + verticalEnd1) / 2;
        if(includeOne(matrix, verticalMid1, 1))
        {
            verticalEnd1 = verticalMid1;
        }
        else
        {
            verticalStart1 = verticalMid1;
        }
    }
    if(includeOne(matrix, verticalStart1, 1))
    {
        leftBound = verticalStart1;
    }
    else
    {
        leftBound = verticalEnd1;
    }

    // 找到右边界
    while(verticalStart2 + 1 < verticalEnd2)
    {
        int verticalMid2 = (verticalStart1 + verticalEnd1) / 2;
        if(!includeOne(matrix, verticalMid2, 1))
        {
            verticalEnd2 = verticalMid2;
        }
        else
        {
            verticalStart2 = verticalMid2;
        }
    }
    if(includeOne(matrix, verticalEnd2, 1))
    {
        rightBound = verticalEnd2;
    }
    else
    {
        rightBound = verticalStart2;
    }

    //找到上边界
    while(horizonStart1 + 1 < horizonEnd1)
    {
        int horizonMid1 = (horizonStart1 + horizonEnd1) / 2;
        if(includeOne(matrix, horizonMid1, 1))
        {
            horizonEnd1 = horizonMid1;
        }
        else
        {
            horizonStart1 = horizonMid1;
        }
    }
    if(includeOne(matrix, horizonStart1, 1))
    {
        upperBound = horizonStart1;
    }
    else
    {
        upperBound = horizonEnd1;
    }

    //找到下界
    while(horizonStart2 + 1 < horizonEnd2)
    {
        int horizonMid2 = (horizonStart2 + horizonEnd2) / 2;
        if(!includeOne(matrix, horizonMid2, 1))
        {
            horizonEnd2 = horizonMid2;
        }
        else
        {
            horizonStart2 = horizonMid2;
        }
    }
    if(includeOne(matrix, horizonEnd2, 1))
    {
        bottomBound = horizonEnd2;
    }
    else
    {
        bottomBound = horizonStart2;
    }

    return (bottomBound - upperBound) * (rightBound - leftBound);
    
}
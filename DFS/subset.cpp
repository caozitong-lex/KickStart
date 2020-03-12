//数组/矩阵的DFS with回溯
//数组/矩阵的DFS和树或图的DFS 带回溯实现过程不太一样
// 树和图的实现：前序记录当前节点到一些数据结构中 中序递归所有子节点 后序把数据结构状态回溯到刚进入节点时的状态
// 因为在前序 访问本节点 中序访问子节点 后序时 表明本节点构成的树的信息已经全部收集完 下一步就是回到本节点的父节点 然后进入它的兄弟节点
// 因此 回到父节点时 要保持数据结构状态是父节点的数据结构状态 那也就是刚进入本节点时 未记录本节点时的数据结构 

// 矩阵/数组的实现 ：矩阵和数组进行dfs时 对应于树中【层】概念的是矩阵/数组中的【行/列】/【索引】  
// 数组每个索引可取的数有多少种 就代表下个索引有多少子节点 比如[123]求子集 在考虑第一个位置时 有4种选择 1，2，3，空 
// 矩阵每一行的位置有多少种 就代表下一行有多少子节点 比如N皇后问题 4*4的表格 第一行放皇后有四个位置可以放
// 主要的区别在于 矩阵和数组 是没有 总根节点的多叉树 在参数中可以看到 传递的是第一层 而不是根节点 
// 这就意味着它们不是传入一个根节点 而是传入了一组根节点 然后对每个根节点重复同样的操作 前序记录 中序递归 后序回溯 
// 其中中序递归部分 同样并不是像树/图那样 对每个子节点一个一个递归 因为递归函数本身就是按层传入的 因此直接传入一层 由下一个递归函数对每个子节点一个一个递归 就像刚刚发生的那样
// 最后关于根节点的问题 其实树/图的 真正根节点也是空 虽然参数传入了根节点 但是在函数最开始没有记录根节点时 也就是前序的前序 集合是空的 当后续把根节点pop后 回到了空树的状态 因此可以看作是 不管是树图还是矩阵 都有一个 空节点 它是树最开始的状态 只不过这个状态只有在记录型的题目中才会表现出来 
//总之 树/图是传入一个根节点 一次记录 循环一个一个递归所有子节点 而数组/矩阵是 传入一组节点 循环一个一个记录 但一次递归所有子节点
// 此外 n皇后和子集问题中 函数参数都用到了层笔记本index或level 相当于树的深度depth 用来判断是否到达叶节点

// 核心就是 理解递归过程的三次访问 第一次访问和第三次 函数的状态是相同的（这个状态指具有回溯的题目中的状态） 一个是从父节点刚进入节点 一个是从节点即将返回父节点
// 以及对于搜索问题 它的搜索树是什么样的？ 基于这个搜索树来写出递归解题

// 一个数组 子数组有n^2(双循环) 子序列有2^n（每个元素取或不取 有序） 子集同子序列 全排列有n!
// 子集是一种元素的组合 而子序列虽然有序 但每个子序列其实都是特定顺序下的一种元素组合 和子集是同理的

#include<iostream>
#include<vector>
using namespace std; 

class Solution
{
public:
// dfs的遍历实现 完成搜索 分成接口函数和遍历函数 
// 遍历函数的参数除了基本参数nums 还有全局笔记本subsets 辅助全局笔记本subset 函数局部参数index 相当于根节点指针 nums相当于树本身 因为和二叉树不一样 传入树根就可以 数组必须要传入整体
//求子集相当于测试每一个节点 有取或不取的两种选择 取或不取都是当前节点的子节点 取和不取之间需要回溯操作 和求路径和一样 因为辅助全局笔记本subset的作用范围是每一条路径 因此选择另一条路径时 需要撤回 但不同之处是 这个pop是在两个递归之间 
// 撤回的核心原则是 后序和前序 该节点的状态相同 因此push - pop可以保证节点状态相同 第二个递归不影响节点状态
    void dfsByBinaryTree(int index, vector<int> &nums, vector< vector<int> > &subsets, vector<int> &subset)
    {   
        if(index >= nums.size())
        {
            return;
        }

        subsets.push_back(subset);        //先加入当前的生成的子集

        subset.push_back(nums[index + 1]);//生成下一个子集
        //subsets.push_back(subset);      //若在加入新元素前记录子集 那么加入最后一个新元素后 再次递归超出界限 再也无法记录子集 
        //加入子集的时机取决于 此时节点状态和节点索引的关系 先同步还是先记录
        dfsByBinaryTree(index + 1, nums, subsets, subset);  //进入下一层 带着新的子集

        subset.pop_back();
        dfsByBinaryTree(index + 1, nums, subsets, subset);
    }

    //多叉树的实现 按照讲义中的多叉树进行搜索 从根节点到每个节点的路径 都是一个子集 搜索的过程也是搜索并构造子集的过程
    // 这棵多叉树的深度是不一的 每棵子树的深度都不同 和N皇后一样 每层的节点 先选后选存在一些限制 
    // 可以看做是 求这个多叉树上 从根节点到所有节点的路径 因此每次进入一层都先记录 当前路径 
    // 每当切换兄弟节点进行递归时 都要回溯到刚刚进入本层的时候
    // 关于记录：记录和所有dfs遍历实现一样 记录都发生在前序 但这个记录操作不需要判断 因为就是记录每条路径
    // 关于返回：这道题没有显式的return 往往dfs的返回发生在前序的检查和后序的自然返回 这里因为不需要判断层数满足什么要求 所以就只有自然返回
    // 关于空集：构造的起点就是空集 

    //在树的路径和中 递归进入某个节点后 先记录该节点的信息 再递归到该节点的所有子节（显式的对左右子树递归） 最后撤回信息 维持在进入该节点前的状态
    //在子集树中 递归进入某层节点后 逐个记录该层所有节点的信息 再逐个递归到下一层（隐式的对下一层递归 本质就是对该节点的所有子节点递归） 最后逐个撤回信息 维持在进入该点前的状态
    //特殊在 子集树中递归函数无法进入某一个节点 而是必须进入一组节点 用index表示的一层节点 那么就要循环对每个节点分别记录/递归/撤回 特别的是 递归到下一层也使用的是层来表示
    void dfsByMultipleTree (int index, vector<int> &nums, vector< vector<int> > &subsets, vector<int> &subset )
    {
        subsets.push_back(subset); 
        for (int i = index; i < nums.size(); i++)   //尝试本层所有节点 逐个 选-继续递归-不选
        {
            subset.push_back(nums[i]);
            
            dfsByMultipleTree(i + 1, nums, subsets, subset);

            subset.pop_back();
        }
        //subsets.push_back(subset); 什么时候加入集合 只关系到结果的顺序 但生成结果都是对的
        //一个是在前序加入一个是后序加入 中序的过程由于有push和pop 不影响进入刚刚这一层时的已生成路径
        //树的路径和那道题中 前序修改路径以及路径和 后序回溯 是为了保证第一次访问前和第三次访问后 数据结构的状态是相同的
    }


    vector< vector<int> > subset(vector<int> &nums)
    {
        vector <vector<int> > subsets;
        vector<int> subset;
        subsets.push_back(subset); //先加入空集 二叉树dfs生成的子集中不包括空集
        subset.push_back(nums[0]);
        dfsByBinaryTree(0, nums, subsets, subset);
        //dfsByMultipleTree(0, nums, subsets, subset);
        return subsets;
    } 
};

int main()
{
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    vector < vector<int> > result;
    Solution s;
    result = s.subset(nums);
    for(int i = 0; i<result.size(); i++)
    {
        if(result[i].size() == 0)
        {
            cout<< "[]";
        }
        for(int j = 0; j < result[i].size(); j++)
        {
            cout<<"["<<result[i][j]<<"]";
        }
        cout<<endl;
    }

    system("out");
    return 0;
}



#include<iostream>
#include<vector>
#include<map>
#include<queue>
using namespace std;

class Solution
{
//传入单词表 初始词 目标词 每次转化变动一个字符 找到转化的最短路径 -> 图的BFS
public:
    //把题目转化为图的问题 本质是层次化索引解决最短路径问题 
    //图的边->单词之间能否转化  图的点->每个单词
    //传统图的节点用结构体表示 节点封装了节点值和邻接节点指针数组 图则是节点指针数组 
    //这道题 图的实现使用map 节点是一个key-value对 key是节点值/单词 value是邻接节点 也就是字符串列表 
    //为什么这道题不使用结构体实现？因为题目给定了节点 是字符串形式 而没有给定结构体形式 于是就直接使用简单的方式
    //同理 如果节点值是数字 也可以直接用数组 index是节点值 value是节点vector
    //如果使用结构体也可以 图就是节点指针数组 节点值就是string 构造函数就是 wordNode(string str): value(str){} 然后根据单词列表 new wordNode(wordList[i])进行初始化节点 并pushback到图中
    //数据结构的核心在于思想 如果一个图节点的实现 能起到结构体中 拿到节点就能拿到值 拿到邻接点 的功能 那就是合理的 字典式图的节点和值合二为一 通过字典可以拿到邻接点 
    //最短路径问题的实现区别是多了一个计数器初始化为0 在每层循环结束前计数器++ 循环表明即将进入下一层
    //【语法】
    // 为什么c++必须使用指针来实现链表等数据结构？ 见笔记链表逆序-a
    //实现时 对于数据结构如队列 究竟应该存储指针还是存储自身的问题 这关系到函数传递的问题
    //首先 题目传递的root等一定是对象指针 传递类对象将拷贝构造一个临时对象， 所有针对的操作皆操作在这个临时对象上； 指针也要创建一个临时指针对象，只是他们指向同样的对象，对所指向的对象操作不会操作在临时变量上； 引用不创建临时对象，只是一个别名，不占内存
    //因此相对应的数据结构自然存储的是指针 而这道题传递的是string 队列存储的也是string
    //对象的函数传递 https://www.cnblogs.com/whale90830/p/10536281.html
    //此外 对象的左右节点也是指针 那么定义类时 左右节点可以不定义为指针吗？
    //关于类定义时无法把数据成员指定为自身类型：
    //实例化一个类对象时 编译器会根据类的定义来分配相应内存 这意味着类的定义必须完整 否则无法计算所需内存
    //而类中成员若是自身类对象 相当于递归定义 永远无法分配内存
    //若成员定义为自身类对象的指针 则可以分配内存 因为只需要分配指针类型的内存 也就是8个字节
    //从对象构造角度来看 构造类对象会先构造成员变量 再调用自身类对象的构造函数 若成员变量是自身对象 那么构造这个对象需要先构造变量 构造变量要调用自身构造函数 这就矛盾
    bool transAllowed(string word1, string word2)
    {
        //检查两个单词是否能进行转化 - 即不同字母数为1
        int count = 0;
        for(int i = 0; i < word1.size(); i++)
        {
            if(word1[i] != word2[i])
            {
                count ++;
            }
        }
        return count == 1; // 代替下面的if else语句
        /*
        if(count != 1)
        {
            return false;
        }
        return true;
        */
        
    }
    void constructGraph (string beginWord, vector<string> &wordList, map< string, vector<string> > &graph )
    {
        wordList.push_back(beginWord);  //初始词不在单词列表中 放入
        // 两两对比单词 检查是否能够形成边
        for(int i = 0; i < wordList.size(); i++)
        {
            for(int j = i + 1; j < wordList.size(); j++)
            {
                if(transAllowed(wordList[i], wordList[j]))
                {
                    graph[wordList[i]].push_back(wordList[j]);  //map和vector不同 map可以不需要初始化就直接使用索引map[i]对vector进行赋值/插入 而构造vector的vector 必须要先pushback(vector<>()) 才能使用m[i].pushback加入元素 否则无法直接使用索引
                    graph[wordList[j]].push_back(wordList[i]);
                }
            }
        }
    } 
    
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        map< string, vector<string> >graph;             //声明图
        constructGraph(beginWord, wordList, graph);     //构建图 边/点 传引用在函数定义处声明即可

        map<string, bool> wordDic;                      //BFS哈希
        for(int i = 0; i < wordList.size(); i++)        //初始化
        {
            wordDic[wordList[i]] = 0;
        }
        //这里的哈希其实只需要实现 查询一个字符串 返回0/1 因此使用了map 若查询一个数字可以用标准数组
        //还有一种通用的实现方式是set（或vector） 若出现在集合中 说明它被访问过 重要函数是find 关于find和迭代器 见hash and heap集
        queue<string> wordQueue;                        //BFS队列
        int steps = 0;                                  //步数初始化为1                        

        wordQueue.push(beginWord);                      //入根
        wordDic[beginWord] = 1;

        while(!wordQueue.empty())                       //每次while循环 都是一个节点的裂开
        {
            int len = wordQueue.size();
            steps ++;                                   //一层的节点分解完 进入下一层

            for(int i = 0; i < len; i++)                //层次化bfs 每个for循环内是一层节点的裂开
            {
                string root = wordQueue.front();            //取根
                if(root == endWord)                         //检查步数
                {
                    return steps;
                }
                wordQueue.pop();                            //出队

                for(int j = 0; j < graph[root].size(); j++) //分裂子节点
                {
                    if(wordDic[graph[root][j]] == 1)        //检查哈希
                    {
                        continue;
                    }
                    wordQueue.push(graph[root][j]);         //入队
                    wordDic[graph[root][j]] = 1;            //更新哈希
                }
            } 
            cout << endl;
        }
        return -1;
    }
};

int main()
{
    string begin = "hit";
    string end = "cog";
    vector<string> wordlist;
    wordlist.push_back("hot");
    wordlist.push_back("dot");    
    wordlist.push_back("dog");
    wordlist.push_back("lot");
    wordlist.push_back("log");
    wordlist.push_back("cog");
    Solution s;
    cout << s.ladderLength(begin, end, wordlist);

}
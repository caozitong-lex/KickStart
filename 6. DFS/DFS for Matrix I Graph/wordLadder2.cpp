#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
using namespace std;


bool formEdge(string word1, string word2)
{
    int difference = 0;
    for(int i = 0; i < word1.size(); i++)
    {
        if(word1[i] != word2[i])
        {
            difference += 1;
        }
    }
    return  difference == 1;
}
map<string, vector <string> > constructGraph(vector<string> &wordlist, string begin)
{
    map<string, vector <string> > graph;
    for(int i = 0; i < wordlist.size();i++)
    {
        if(wordlist[i] != begin)
        {
            wordlist.push_back(begin);
        }
    }

    for(int i = 0; i < wordlist.size(); i++)
    {
        for(int j = i; j < wordlist.size(); j++)
        {
            if(formEdge(wordlist[i], wordlist[j]))
            {
                graph[wordlist[i]].push_back(wordlist[j]);
                graph[wordlist[j]].push_back(wordlist[i]);
            }
        }
    }
    return graph;
}

int getShortest(map<string, vector <string> > graph, string begin, string end)
{
    queue<string> graphQueue;
    set<string> stringHash;
    graphQueue.push(begin);
    int step = 1;

    while(!graphQueue.empty())      //直至分解所有节点 while和for循环搭配不是m*n的组合 for相当于分割while的循环空间
    {
        int levelSize = graphQueue.size();
        for(int i = 0; i < levelSize; i++)  //逐层分解
        {
            string top = graphQueue.front();
            if(top == end)
            {
                return step;
            }
            graphQueue.pop();
            stringHash.insert(top);         //bfs有两入一出 哈希更新要不然和入绑定 要不然和出绑定

            for(int j = 0; j < graph[top].size(); j++)
            {
                if(stringHash.find(graph[top][j]) == stringHash.end())
                {
                    graphQueue.push(graph[top][j]);
                }
            }
        }
        step += 1;
    }
    return -1;
}

void getPathByRecursion(string begin, string end, map<string, vector <string> > &graph, int shortest, int currentStep, vector< vector<string> > &results, vector<string> result, set<string> stringHash)
{
    if(currentStep > shortest)
    {
        return;
    }

    result.push_back(begin);
    stringHash.insert(begin);
    
    if(begin == end)
    {
        results.push_back(result);
    }

    for(int i = 0; i < graph[begin].size(); i++)
    {
        if(stringHash.find(graph[begin][i]) == stringHash.end())
        {
            getPathByRecursion(graph[begin][i], end, graph, shortest, currentStep + 1, results, result, stringHash);
        }
    }
    result.pop_back();
    stringHash.erase(begin);


}
vector< vector<string> > wordLadder(string begin, string end, vector<string> &wordlist)
{
    map<string, vector <string> > graph = constructGraph(wordlist, begin);
    int shortest = getShortest(graph, begin, end);
    vector< vector<string> > results;
    vector<string> result;
    set<string> stringHash;
    int currentStep = 1;
    getPathByRecursion(begin, end, graph, shortest, currentStep, results, result, stringHash);

    set< vector<string> > filter;
    vector< vector<string> > resultsWithoutDup;
    for(int i = 0; i < results.size(); i++)
    {
        filter.insert(results[i]);
    }
    set< vector<string> > :: iterator it;
    for(it = filter.begin(); it != filter.end(); it++)
    {
        resultsWithoutDup.push_back(*it);
    }

    return resultsWithoutDup;
}

//回溯的时机 每次递归都回溯 最后回溯 不回溯
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
    
    vector< vector<string> > results = wordLadder(begin, end, wordlist);

    
    for(int i = 0; i < results.size(); i++)
    {
        for(int j = 0; j < results[i].size(); j++)
        {
            cout << results[i][j] << "-";
        }
        cout  << endl;
    }
    
    

}
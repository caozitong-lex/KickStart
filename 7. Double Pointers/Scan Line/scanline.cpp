#include <iostream>
#include <string>
#include <sstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

bool cmp(pair<int, int> a, pair<int ,int> b)
{
    if(a.first == b.first)
    {
        return a.second < b.second;
    }
    return a.first < b.first;
}


int main()
{
    int numOfCall = 0;
    //cin >> numOfCall;
    vector< pair<int,int> > points;
    int point;
    
    points.push_back(make_pair(0,1));
    points.push_back(make_pair(30,0));
    points.push_back(make_pair(0,1));
    points.push_back(make_pair(50,0));
    points.push_back(make_pair(10,1));
    points.push_back(make_pair(20,0));
    points.push_back(make_pair(15,1));
    points.push_back(make_pair(30,0));
    points.push_back(make_pair(20,1));
    points.push_back(make_pair(50,0));
    points.push_back(make_pair(20,1));
    points.push_back(make_pair(60,0));
    /*
    for(int i = 0; i < 2 * numOfCall; i++)
    {
        cin >> point;
        if(i % 2 == 0)
        {
            points.push_back(make_pair(point, 1));
        }
        else
        {
            points.push_back(make_pair(point, 0));
        }
    }
    */
    int maxNum = -10;
    int currentNum = 0;
    sort(points.begin(), points.end(), cmp);
    
    for(int i = 0; i < points.size(); i ++)
    {
        if(points[i].second == 1)
        {
            currentNum++;
            //cout << "起飞" << endl;
            if(currentNum > maxNum)
            {
                maxNum = currentNum;
            }
        }
        else
        {
            //cout << "降落" << endl;
            currentNum--;
        }
    }
    cout <<  maxNum;
}
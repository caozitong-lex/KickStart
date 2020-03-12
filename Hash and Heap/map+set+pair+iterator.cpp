#include<iostream>
#include<map>
#include<string>
#include<set>
#include<vector>
using namespace std;
    // stl的迭代器 可以理解为被封装了的指针 
    // 每个容器有自己的iterator类 因此需要 xxx<oo>::iterator i; 来实例化一个迭代器对象
    // 其中set/map是双向迭代 vector是随机访问 栈队和优先级队列不支持迭代器
    // xx.begin()和xx.end()会返回收尾元素的迭代器
int main()
{
    map<string, int> hash_map;
    string str1 = "Genji";
    string str2 = "Mercy";  
    hash_map[str1] = 1;     //下标式插入
    hash_map[str2] = 2;
    hash_map.insert(make_pair("76", 3));    //函数式插入
    //map有索引 但hash_map['xx']若索引到了一个不存在的键值 会自动添加 那么如何检查一个键值在不在字典里？
    //有索引但无法用于查询 -> map的find()返回一个迭代器 如果未找到则 = .end(）
    // 找到后 返回目标pair的迭代器 目标str其实就等于 .find(str)->first dic[str]就等于 ->second
    cout << "【Dictionary】: " << endl;
    if(hash_map.find(str1) != hash_map.end())
    {
        cout << "Index = " << str1 << ". And number = " << hash_map[str1]<<endl;
        //cout << "Index = " << hash_map.find(str1)->first << ". And number = " << hash_map.find(str1)->second <<endl;
    }
    // 没有数字索引 -> map的遍历需要iterator 
    map<string, int>::iterator mapIt;
    for(mapIt = hash_map.begin(); mapIt != hash_map.end(); mapIt++)
    {
        cout << mapIt->first << ":" << mapIt->second<<endl;
    }
    // 字典结构的单位是pair 字典本质就是pair的set 即无重复的pair对
    // 它不仅可以用来构建字典 也可以单独用来做别的事情 和vector搭配可以做一些有关记录的工作
    pair<string , int > hero1;
    hero1.first = "genji";
    hero1.second = 1;   
    cout << "【Pair】:" <<endl;
    cout << hero1.first << " :  " << hero1.second << endl;
    pair<string, int> hero2 = make_pair("Hanzo", 2);
    cout << hero2.first << " :  " << hero2.second << endl;
    
    //数据结构set 无重复的排序数组
    //set不提供下标索引 -> 需要迭代器遍历和find查找 和字典一样
    set<string> hash_set;
    hash_set.insert("genji");
    hash_set.insert("Hanzo");
    hash_set.insert("Mei");
    set<int> s;
    set<int>::iterator setIt;
    for(int i = 10; i > 0; i--)
    {
        s.insert(i);
    }
    cout <<"【Set】: ";
    for(setIt = s.begin(); setIt != s.end(); setIt++)
    {
        cout << *setIt << "-";
    }
    cout << endl;
    if(s.find(1) != s.end())    //find返回迭代器 用*取值
    {
        cout << "Find " << *s.find(1) <<endl;
    }

    
    // vector的数字索引可以使得vector可迭代器遍历 也可以直接下标遍历 vector没有find函数 因为可以直接用数字索引 若不存在会报错
    vector<int> vec;
    for(int i = 0; i < 10; i++)
    {
        vec.push_back(i);
    }
    vector<int>::iterator vecIt;
    cout << "【Vector】: ";
    for(vecIt = vec.begin();vecIt != vec.end(); vecIt++)
    {
        cout <<  *vecIt << "-";
    }
}
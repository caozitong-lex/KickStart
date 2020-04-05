#include <iostream>
#include <string>
#include <sstream>
#include<vector>
#include<map>
#include<set>
#include<queue>
#include<stack>
using namespace std;



int main() {
    int length = 0;
    int type = 0;
    string str;
    vector<char> chars;
    char character;
    int num = 0;

    /*
    cin >> length >> type;
    cin >> str;
    while(cin >> character)
    {
        chars.push_back(character);
    }
    */
    
    length = 6;
    type = 2;
    str = "xyzxyz";
    chars.push_back('x');
    chars.push_back('y');
    
    map<char, int> charMap;
    for(int i = 0; i < chars.size(); i++)
    {
        charMap[chars[i]] = 1;
    } 
    int left = 0; 
    int right = left;
    while(right == str.size())
    {
        string temp = str.substr(left, right - left + 1);
        int flag = 0;
        for(int i = 0; i < temp.size(); i++)
        {
            if(charMap[temp[i]] != 1)
            {
                left ++;
                right = left;
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            num ++;
        }
    }
    cout << num;
    
    /*
    for(int i = 0; i < str.size(); i++)
    {
        for(int j = i; j < str.size(); j++)
        {
            int flag;
            string temp = str.substr(i, j - i + 1);
            //cout << "现在检查"<<temp<<endl;
            for(int k = 0; k < temp.size(); k++)
            {
                flag = 0;
                if(charMap[temp[k]] != 1)
                {
                    //cout << temp[k] << "不存在" << endl;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                //cout << temp << "通过！" << endl;
                num ++;
            }
        }
    }
    cout << num;
    */


}
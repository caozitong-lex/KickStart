#include<string>
#include<iostream>
#include<map>
using namespace std;


int hashFunction(string keyByStr, int hashSize)
{
    int sum = 0;
    for (int i = 0; i < keyByStr.size(); i++)
    {
        sum += sum * 31 + (keyByStr[i] - '0') ; //把'452'转化为数字452也同理 sum*10 + nums[i]-'0'
        sum =  sum % hashSize;
    }
    return sum;
}
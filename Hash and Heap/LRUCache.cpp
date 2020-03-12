#include<iostream>
#include<vector>
using namespace std;

struct KeyValue
{
    int key, value;
    KeyValue *next;
    KeyValue():key(0), value(0), next(NULL){}
    KeyValue(int temp_key, int temp_value):key(temp_key), value(temp_value), next(NULL){}
};

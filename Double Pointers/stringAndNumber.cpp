#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

class Solution
{
public:
    void transformFunc()
    {
        //测试 数字 - 字符串 自带转换函数
        string str_a = "1023";
        int int_a = 1023 ;
        cout << stoi(str_a);
        cout << to_string(int_a);
        //对于单个数字和 单个字符 可以使用 "1" - "0" -> 1 或 1 + "0" -> "1"

    }

    void stringAndChar()
    {
        //字符数组的for循环遍历
        //字符数组找到最后一位的方法是 =='\0'
        //无法用for循环 因为数组长度未知
        char str[] = "ssa sas";
        int i =  0;
        while(str[i] != '\0')
        {
            cout <<str[i];
            i++;
        }
        // 从字符数组到字符串的转换
        // 字符数组可以直接赋值给string -> 做题时遇到字符数组可以直接转化为string做
        string str2  = str;
        cout << str2 <<" "<< str2.size();
    }
    //====================================================
    // 三个函数 求数字各位数的和 把数字回文 把字符串转数字 
    // 都可以看作取出每一位数字 求和的过程 
    //取出最低位数字可以用 % 实现 移动低位可以用 / 实现 取出低位数字后和当前数字*10相加是回文 相当于从低位到高位 不*10是各位数相加 
    // 字符串取出各位数字使用string下标 移动则需要用for循环 转成数字使用 str[i] - '0'实现 从高位向低位取 *10相当于高位数字仍保持高位
    int sumOfEveryPosition(int n)
    {
        //传入一个数字 求数字各位数字的和
        int sum = 0;
        while(n != 0)
        {
            sum += n % 10; // 每次抽取(%)一位数 和当前累加值相加 移动下位数(/)
            n /= 10;
        }
        return sum;
    }

    int PlalindromeNum(int n)
    //传入一个多位数 进行回文 操作
    //对于字符串 判断回文使用双指针即可 回文操作同样双指针交换即可
    //对于数字 判断回文可以转字符串进行判断 回文操作可以转字符串双指针交换再转数字 较麻烦
    //因此数字的回文操作可以直接使用数字的回文 回文后也可以用于判断回文 （回文后和回文前比较即可）
    {
       
        int sum = 0;
        while(n != 0)   //每次抽取最低位(%) 和当前和*10后相加 移动至下一位 (/)
        {
            sum = 10 * sum + n % 10; // 先得到5 再得到54（50+4） 再得到543（540+3）
            n /= 10;    //取下一位
        }
        return sum;
    }

    int strToNum(string str)
    {
        // 传入数字的字符串形式 转换为数字
        int sum = 0;
        for(int i = 0; i < str.size(); i++) //每次抽取最高位(str[i]-'0') 和当前和*10相加 向低位移动（for循环）
        {
            //如果是其他进制 就把10改为其他数
            sum = sum * 10 + (str[i] - '0'); //先计算1 再得到12（10+2） 再得到123（120+3） ... 和翻转数字的顺序是相反 一个从高位开始 一个从低位开始 但思路一致 
        }
        return sum;
    }
    //====================================================
    
    void Palindrome2 (int num)
    //传入一个数 将其与自身回文后的数相加 若生成回文数 则返回这个数 30步外还未生成 则返回-1
    {
        
        for(int i = 0; i < 30; i++)
        {
            int inverseNum = PlalindromeNum(num); //inverse num
            int result  = inverseNum + num; //sum
            int inverseResult = PlalindromeNum(result); //get inverse
            // cout << inverseNum  << "+" << num << "=" << result<<endl;
            if(inverseResult == result) // check palindrome
            {
                cout << result << endl;
                return;
            }
            else
            {
                num = result; //update num
            }
        }
        cout << "-1" << endl;
    }

    

};

int main()
{
    Solution s;
    s.PlalindromeNum(12345);
    s.sumOfEveryPosition(12345);
    s.strToNum("12345");
    s.Palindrome2(87);
}
//https://www.jianshu.com/p/00d23ccce7db 判断一个数是否为回文数 及求一个数的回文数 先求出回文数 再和原数比较 这样一次性可以解决两个问题 
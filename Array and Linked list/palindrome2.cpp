#include <iostream>
#include <string>
// https://blog.csdn.net/weixin_34401479/article/details/93304317
using namespace std;

const int N = 30;
const int N2 = 20;

char v[N2], rv[N2], len;

// 函数功能：判断n是否为回文数
bool isPalindrome(int len, char v[])
{
    int start = 0, end = len - 1;

    while(start < end) {
        if(v[start] != v[end])
            return false;

        start++, end--;
    }

    return true;
}

// 将字符串转换为整数：按位存储到数组，低位从下标0开始存放，高位放在大下标的单元
inline int myatoi(string& s, char v[])
{
    int len = s.length();
    for(int i=len-1,j=0; i>=0; i--,j++)
        if(s[i] >= 'A')
            v[j] = s[i] - 'A' + 10;
        else
            v[j] = s[i] - '0';

    return len;
}

// 将数组v[]中的数，逆序放到数组rv[]中
inline void setRight(int len, char v[], char rv[])
{
    for(int i=0; i<len; i++)
        rv[len - 1 - i] = v[i];
}

// 两数相加
inline int add(int len, char v[], char rv[], char base)
{
    int carry = 0;
    for(int i=0; i<len; i++) {
        v[i] += rv[i] + carry;
        carry = v[i] / base;
        v[i] %= base;
    }
    if(carry > 0)
        v[len++] = carry;

    return len;
}

int main()
{
    int n, i;
    string m;

    //cin >> n >> m;
    n = 10;
    m = "19";

    len = myatoi(m, v);
    for(i=1; i<=N; i++) {
        setRight(len, v, rv);
        len = add(len, v, rv, n);

        if(isPalindrome(len, v))
            break;
    }

    if(i <= N)
        cout << "STEP=" << i << endl;
    else
        cout << "Impossible!" << endl;

    return 0;
}

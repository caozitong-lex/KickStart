#include<iostream>
#include<vector>

using namespace std;
// 建立双指针 for循环指定位移 在循环中增量位移进行移动

// 判断回文串
bool isPlalindrome(string &str)
{
    int leftPtr = 0;
    int rightPtr = str.size() -1 ;
    for(int i = 0; i < str.size()/2; i++)
    {
        if(str[leftPtr + i] != str[rightPtr - i])
        {
            return false;
        }
    }
    return true;
}
//把字符串逆置
void inverseString(string &str)
{
    int leftPtr = 0;
    int rightPtr = str.size()-1;
    
    for (int i = 0; i < str.size()/2; i++)
    {
        char temp = str[leftPtr + i];
        str[leftPtr + i] = str[rightPtr - i];
        str[rightPtr - i] = temp;
    }

}
/*常规实现字符串逆置
void inverse (string &nums)
{
    for(int i = 0; i < nums.size()/2; i++)
    {
        char temp =  nums[i];
        nums[i] = nums[nums.size()- 1 - i];
        nums[nums.size()- 1 - i] = temp;
    }
} 
*/
int main()
{
    string s1= "1234";
    //string s2 = "genji";
    //bool r = isPlalindrome(s1);
    //inverse(s1);
    cout<<s1;

    //cout << 23/10 + 23%10;
    return 0;
}
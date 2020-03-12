#include<iostream>
#include<map>
#include<vector>
using namespace std;

/*
传入一个字符串 求子串中 无重复字符的最长子串长度
暴力思路是n^2的双重for循环扫描出所有子串 

第一种思路是动态规划 和最长子串和类似 由于子串问题若直接设置为dp 很容易出现dp[i]和dp[i-1]无法转移 因此dp[i]设置为以i结尾的最长无重复子串
实现中有一些细节需要注意 首先是上一个子串的截取 其次是子串中检查重复时 若找到了 dp的更新方式 需要找到最后一个重复的元素 如 abcagh | a 那么需要找到第二个a 把agh当作当前的最长无重复子串 而不是1

第二种思路是滑动窗口 滑动窗口旨在对双重循环的优化 显然当得到abb的子串时 接下来就不用尝试 已经出现重复 且假若已经有长度为3的子串解 所有小于3个元素的子串也不用尝试
因此双指针[left, right] 维护一个满足题目要求的窗口 滑动过程中维护解即可 这是双指针滑动窗口的核心 
*/

int longestSubstringByDP(string s)
{
    vector<int> dp(s.size(), 1);
    int longest = 0;

    for(int i = 1; i < s.size(); i++)
    {
        string preSubstr = s.substr(i - dp[i - 1], dp[i - 1]);
        //cout << "上一个子串是：" << preSubstr << endl;
        if(preSubstr.find(s[i]) == preSubstr.npos)    //不用end 用npos
        {
            //cout << "不存在" << s[i] << endl;
            dp[i] = dp[i - 1] + 1;
            //cout << "长度为" << dp[i] << endl;
        }
        else
        {
            //cout << "存在" << s[i] << endl;
            dp[i] = i - s.substr(0, i - 1).find_last_of(s[i]);  //从0开始 取i - 1长的字符串 找到最后一个s[i]的索引 返回 这里必须用最后一个
            //cout << "长度为" << dp[i] << endl;
        }
        
        if(dp[i] > longest)
        {
            longest = dp[i];
        }
    }
    return longest;
}

int longestSubstringBy2Ptr(string s)
{
    int left = 0;
    int right = 0;
    int len = 1;
    string substring;
    map<char, int> charHash;
    
    while(right < s.size()) //右指针遍历完成后结束
    {
        //当前字符未出现在子串中 则记录哈希 并继续
        if(charHash.find(s[right]) == charHash.end() || charHash[s[right]] == 0)
        {
            //cout << "没有发现:" << s[right] << endl;
            charHash[s[right]] = 1;
            right ++;
            //cout << "当前子串:" << s.substr(left, right - left) << endl;
        }
        //若当前字符出现在子串中 则先一直从左向右缩减子串 直到当前字符在子串中被排除 再记录哈希 继续扫描
        else
        {
            //cout << "发现:" << s[right] << endl;
            while(charHash[s[right]] != 0)
            {
                charHash[s[left]] --;
                left ++;
                //cout << "当前子串:" << s.substr(left, right - left) << endl;
            }
            charHash[s[right]] = 1;
            right ++;
        }

        if(right - left > len)
        {
            len = right - left;
        }
        substring = s.substr(left, right - left + 1);       
    }
    return len;
}


int main()
{
    string s = "abcbadab";
    //cout << longestSubstringByDP(s);
    cout << longestSubstringBy2Ptr(s);
}

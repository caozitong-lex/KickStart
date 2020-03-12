#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>


using namespace std;
/*
To solve the problem, we have to overcome 2 difficulties.
First one is how to get the sum of every digits in number.
The key  solution is  utilizing the module and division operation  with a loop.
Concretely, module operation can get the unit digit. And division operation can help us to move on the next digit.
For example, if we want to get the unit digit of the  25. We can mode 25 by 10 so we get 5 and we divide 25 by 10  we get 2.
Second one is check the sum. Obviously when we get the sum, we have to check 2 things. 
Case 1, if the sum equals one, we get the answer.
Case 2, if the sum is not 1, if it has appeared before. If yes, we stuck in a loop, and we return false. Otherwise, we continue the operation.
So we need another data structure hash table to record the sum has appeared. 
In the implementation, I choose the set as hashtable.
This algorithm is quite fast. But it uses the space for hash table about n level linear level.
We can use the double pointers to reduce the space consumption to constant space.
Cause the law of the sum is a cycle. So we can use slow pointer and fast pointer to check the cycle. 
If two pointer meet, and they meet at 1, which means that we get the answer. Otherwise, it means that there is no 1 in the cycle of sum.
*/
class Solution 
{
public:
    bool happyNumberWithHash(int num)
    {
        set<int> numHash;

        while(num != 1) //Until find 1 
        {
            //Get the sum of every positions
            int sumOfPosition = 0;
            sumOfPosition = calculateSum(num);
            // Check the sum
            if(numHash.find(sumOfPosition) == numHash.end()) // Sum never appear
            {
                numHash.insert(sumOfPosition); //Record
                num = sumOfPosition; // Update next num
            }
            else // Sum appeared
            {
                return false;
            }
        } 
        // Find 1
        return true;
    }

    bool happyNumberWithDoublePointers(int num)
    {
        int slowPtr = num;
        int fastPtr = num;
        while(true) //每次循环都是一次移动 
        {   
            // Move ptr  
            slowPtr = calculateSum(slowPtr);
            fastPtr = calculateSum(fastPtr);
            fastPtr = calculateSum(fastPtr);
            // Find the time when they meet and break
            if(slowPtr == fastPtr)
            {
                break;
            }
        }
        // Meet at 1 -> true
        if (slowPtr == 1)
        {
            return true;
        }
        // Meet at other -> no 1 -> false
        return false;
    }

    int calculateSum(int num)
    {
        int sum = 0;
        while(num != 0)
        {
            sum += pow(num % 10, 2);
            num /= 10;
        }
        return sum;
    }
};

int main()
{
    Solution s;
    cout  << s.happyNumberWithHash(7);
}

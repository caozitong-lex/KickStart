#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

// 1 
struct TreeNode
{
    int value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): value(x), left(NULL), right(NULL){}
};

struct GraphNode
{
    int value;
    vector< GraphNode* > neighbor;
    GraphNode(int x): value(x){}
};

void binaryTreeBFS(TreeNode* root)
{
    queue<TreeNode*> btQueue;
    btQueue.push(root);
    
    while(!btQueue.empty())
    {
        TreeNode* temp = btQueue.front();
        cout << temp->value;
        btQueue.pop();

        if(temp->left != NULL)
        {
            btQueue.push(temp->left);
        }
        if(temp->right != NULL)
        {
            btQueue.push(temp->right);
        }
    }
}

void graphBFS(GraphNode* root)
{
    queue<GraphNode*> graphQueue;
    map<int, bool> graphMap;
    graphQueue.push(root);
    graphMap[root->value] = 1;

    while(!graphQueue.empty())
    {
        GraphNode* head = graphQueue.front();
        cout << head->value;
        graphQueue.pop();

        for(int i = 0; i < head -> neighbor.size(); i++)
        {
            if(!graphMap[head->neighbor[i]->value])
            {
                graphQueue.push(head->neighbor[i]);
                graphMap[head->neighbor[i]->value] = 1;
            }
        }
    }
}

void hierBFS(GraphNode* root)
{
    queue<GraphNode*> graphQueue;
    map<int, int> graphMap;
    graphQueue.push(root);
    graphMap[root->value] = 1;

    while(!graphQueue.empty())
    {
        for(int i = 0; i < graphQueue.size(); i++)
        {
            GraphNode* head = graphQueue.front();
            cout << head->value;
            graphQueue.pop();

            for(int i = 0; i < head->neighbor.size(); i++)
            {
                if(!graphMap[head->neighbor[i]->value])
                {
                    graphQueue.push(head->neighbor[i]);
                    graphMap[head->neighbor[i]->value] = 1;
                }
            }
        }
    }
}
//2
// 返回从右侧观察树的节点数组 -> 二叉树的层级遍历
// 区别是每层循环展开节点前先记录最后一个到结果中

vector<int>rightSideView(TreeNode* root)
{
    queue<TreeNode*> q;
    vector<int> r;
    q.push(root);

    while(!q.empty())
    {
        int levelSize = q.size();
        r.push_back(q.back()->value);
        for(int i = 0; i < levelSize; i++)
        {
            TreeNode* head = q.front();
            cout << head->value;
            q.pop();

            if(head->left!=NULL)
            {
                q.push(head->left);

            }
            if(head->right!=NULL)
            {
                q.push(head->right);

            }
        }
    } 
    return r;
}
//3.二叉树的序列化 空子树位置填#
//二叉树的标准遍历 区别是记录/输出操作的位置 绑定在入队时
vector<char> serialization (TreeNode* root)
{
    queue<TreeNode*> treeQueue;
    vector<char> result;

    treeQueue.push(root);
    result.push_back(root -> value + '0');
    while(!treeQueue.empty())
    {
        TreeNode* head = treeQueue.front();
        treeQueue.pop();

        if(head->left != NULL)
        {
            treeQueue.push(head->left);
            result.push_back(head->left->value + '0');
        }
        else
        {
            result.push_back('#');
        }
        if(head->right != NULL)
        {
            treeQueue.push(head->right);
            result.push_back(head->right->value + '0');
        }
        else
        {
            result.push_back('#');
        }
    }
    return result;
}

// 4. 图的最短路径 传入图节点的数量 起点和目标 找到目标值的节点 并返回该节点 
// 利用图的BFS搜索 区别是输出/记录操作改为检查
GraphNode* searchNode(int num, GraphNode* start,int target)
{
    queue< GraphNode* > graphQueue;
    map<int, bool> graphMap;
    
    graphQueue.push(start);
    graphMap[start->value] = 1;

    while(!graphQueue.empty())
    {
        GraphNode* head = graphQueue.front();
        graphQueue.pop();
        if(head -> value == target)
        {
            return head;
        }

        for(int i = 0; i < head->neighbor.size(); i++)
        {
            if(!graphMap[head->value])
            {
                graphQueue.push(head->neighbor[i]);
                graphMap[head->neighbor[i]->value] = 1;
            }
        }
    }
    return NULL;
}

//5. 单词阶梯 传入单词表 初始词 目标词 找到转化的最短步骤长度
// 利用单词表构建图 图的层级BFS解决最短路径

bool trans(string word1, string word2)
{
    int count = 0;
    for(int i = 0; i < word1.size(); i++)
    {
        if(word1[i] != word2[i])
        {
            count ++;
        }
    }
    if(count == 1)
    {
        return true;
    }
    return false;
}

map< string, vector<string> > buildGraph(vector<string> &vocab)
{
    map< string, vector<string> > vocabGraph;
    for(int i = 0; i < vocab.size(); i++)
    {
        for(int j = i + 1; j < vocab.size(); j++)
        {
            if(trans(vocab[i], vocab[j]))
            {
                vocabGraph[vocab[i]].push_back(vocab[j]);
                vocabGraph[vocab[j]].push_back(vocab[i]);
            }
        }
    }
    return vocabGraph;
}

int ladderLength(string begin, string end, vector<string> &vocab)
{
    map< string, vector<string> > vocabGraph = buildGraph(vocab);
    return 0;
}
//6 拓扑排序

//7. map set 迭代器
/*
int main()
{
    // map
    map<string , int > owMap;
    string str1 = "genji";
    string str2 = "hanzo";
    owMap[str1] = 1;
    owMap[str2] = 2;
    owMap.insert(make_pair("mercy", 3));
    cout << (owMap.find("geni") == owMap.end());
    
    map<string, int>::iterator iter;
    for(iter = owMap.begin(); iter != owMap.end(); iter++)
    {
        cout << iter-> first << endl;
    }

    set<int> s;
    s.insert(1);
    s.insert(2);
    set<int>::iterator it;
    for(it = s.begin(); it!=s.end(); it++)
    {
        cout << *it;
    }
    cout << (s.find(1) != s.end());

// 8. heap
    priority_queue<int> bigheap;
    priority_queue<int, vector<int>, greater<int> > smallheap;
    bigheap.push(0);
    return 0;


}
*/

// 9. // string and number
void transformFunc()
{
    string str1 = "1234";
    int int1 = 1234;
    cout << stoi(str1);
    cout << to_string(int1);
}
void stringAndChar()
{
    char str1[]  = "genji";
    int i = 0;
    while(str1[i] != '\0')
    {
        cout << str1[i];
        i++;
    }
    string str2 = str1;
    cout << str2;
}
int sumOfDigit(int n)
{
    int sum = 0;
    while(n)
    {
        sum = sum + n % 10;
        n /= 10;
    }
    return sum;
}

int strToNum(string str)
{
    int sum = 0;
    for(int i = 0; i < str.size(); i++)
    {
        sum = sum * 10 + str[i] - '0';
    }
    return  sum;
}

int palindrome(int n)
{
    int sum = 0;
    while(n)
    {
        sum = sum * 10 + n % 10;
        n /= 10;
    }
    return sum;
}
//10 
bool validateBracket(string brackets)
{
    stack<char> s;
    for(int i = 0; i < brackets.size(); i++)
    {
        if(brackets[i] == '('||brackets[i] == '['||brackets[i] == '{' )
        {
            s.push(brackets[i]);
            continue;
        }
        if(brackets[i] == ')')
        {
            char head = s.top();
            if(head == '(')
            {
                s.pop();
                continue;
            }
            else
            {
                return false;
            }
        }
        if(brackets[i] == ']')
        {
            char head = s.top();
            if(head == '[')
            {
                s.pop();
                continue;
            }
            else
            {
                return false;
            }
        }
        if(brackets[i] == '}')
        {
            char head = s.top();
            if(head == '{')
            {
                s.pop();
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    return !s.empty();
}
//11 happy number
int digitSum(int num)
{
    int sum = 0;
    while(!num)
    {
        sum += (num % 10) * (num % 10);
        num /= 10;
    }
    return sum;
}
bool happyNumber(int num)
{
    int temp = digitSum(num);
    set<int> s;
    //第一种写法
    while(temp != 1)
    {
        if(s.find(temp) != s.end())
        {
            return false;
        }
        s.insert(temp);
        temp = digitSum(temp);
    }
    return true;
    //第二种写法
    while(temp != 1 && s.find(temp) == s.end())
    {
        s.insert(temp);
        temp = digitSum(temp);
    }
    if(s.find(temp) != s.end())
    {
        return false;
    }
    else
    {
        return true;
    }
    //第三种写法
    while(1)
    {
        if(s.find(temp) == s.end())
        {
            return false;
        }
        if(temp == 1)
        {
            return true;
        }
        s.insert(temp);
        temp = digitSum(temp);
    }
    
    // 这里每次计算完temp需要两个判断 是否为1 或者 是否存在 
    // 若不为1 继续，为1 为真。若不存在 继续，存在 为假。
    //可以写成while(1)循环 内部两个判断 或while判断一个 内部if判断一个 
    //或while判断两个 while外两个判断 
}

bool happyNumber2P(int num)
{
    int slow = num;
    int fast = num;
    while(true) 
    {
        slow = digitSum(slow);
        fast = digitSum(fast);
        fast = digitSum(fast);

        if(slow == fast)
        {
            break;
        }
    }
    if(slow == 1)
    {
        return true;
    }
    return false;
}
// 11.哈希方程 传入字符串键值和哈希表大小 计算哈希值
int hashFunc(string key, int hashSize)
{
    int sum = 0;
    for(int i = 0; i < key.size(); i++)
    {
        sum += sum * 31 + key[i] - '0'; //相当于字符串转数字 只不过是31进制
        sum = sum % hashSize;
    }
    return sum;
}
// 12. ugly number 2 3 5
int uglyNumber(int num)
{
    priority_queue< int, vector<int>, greater<int> > small;
    set<int> s;

    int starter = 1;
    int head;
    small.push(starter);
    s.insert(starter);

    for(int i = 0; i < num; i++)
    {
        head = small.top();
        if(s.find(head * 2) == s.end())
        {
            small.push(head * 2);
        }
        if(s.find(head * 3) == s.end())
        {
            small.push(head * 2);
        }
        if(s.find(head * 5) == s.end())
        {
            small.push(head * 2);
        }
    }
    return head;
}

//13. 小岛
int directionX[] = {1, 0, -1, 0};
int directionY[] = {0, 1, 0, -1};
void spread(int x, int y, vector< vector<int> > &mark,  vector< vector<char> > &grid)
{
    queue< pair<int, int> > matrixQ;
    matrixQ.push(make_pair(x,y));
    
    while(!matrixQ.empty())
    {
        pair<int, int> head = matrixQ.front();
        mark[head.first][head.second] = 1;
        matrixQ.pop();

        for(int i = 0; i < 4; i++)
        {
            if(grid[x + directionX[i]][y + directionY[i]] == '1' && mark[x + directionX[i]][y + directionY[i]] == 0)
            {
                matrixQ.push(make_pair(x + directionX[i], y + directionY[i]));
            }
        }
    }
}
int island(vector<vector<char> > &grid)
{
    int num = 0;
    vector< vector<int> > mark;
    for(int i = 0; i < grid.size(); i++)
    {
        mark.push_back(vector<int>());
        for(int j = 0; j < grid[i].size(); j++)
        {
            mark[i].push_back(0);
        }
    }
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(mark[i][j] == 0 && grid[i][j] == '1')
            {
                spread(i, j, mark, grid);
                num++;
            }
        }
    }

    return num;
}

//14 找到第k大的数
//使用堆 需要通过if来维护堆的大小 进还是出
int findKth(vector<int> &num, int k)
{
    int kth;
    priority_queue<int, vector<int>, greater<int> > small;
    for(int i = 0; i < num.size(); i++)
    {
        if(i >= k)
        {
            if(num[i] > small.top())
            {
                small.push(num[i]);
                small.pop();
            }
        }
        small.push(num[i]);
    }
    kth = small.top();
    return kth;
} 

// 15. 反向双指针
// 判断回文串
bool isPalindrome(string &str)
{
    int left = 0;
    int right = str.size() - 1;
    for(int i = 0; i < str.size() / 2; i++)
    {
        if(str[left + i] != str[right - i])
        {
            return false;
        }
    }
    return true;
}
// 逆置字符串
void reverseString(string &str)
{
    int left = 0;
    int right = str.size() - 1;
    for(int i = 0; i < str.size() / 2; i++)
    {
        char temp;
        temp = str[left + i];
        str[left + i] = str[right - i];
        str[right - i] = temp;
    }
}
// 16. 同向双指针
//计算数组中所有窗口大小子数组和    
vector<int> windowSum(vector<int> nums, int size)
{
    int left = 0;
    int right = size - 1;
    vector<int> sums;
    for(int i = 0; i < nums.size() - size + 1; i++)
    {
        int sum;
        for(int j = left; j <= right; j++)
        {
            sum+= nums[j];
        }
        sums.push_back(sum);
    }
    return sums;
}

vector<int> windowSumBetter(vector<int> nums, int size)
{
    int left = 0;
    int right = size - 1;
    int sum = 0;
    vector<int> sums;
    for(int i = 0; i < size; i++)
    {
        sum += nums[i];
    }
    sums.push_back(sum);
    for(int i = 1; i < nums.size() - size + 1; i++)
    {
        sum = sum + nums[right + i] - nums[left + i];
        sums.push_back(sum);
    }
    return sums;
}

//把数组中的0移到末尾
void moveZero(vector<int> &nums)
{
    int left = 0;
    int right = 0;

    while(right < nums.size())
    {
        if(nums[left] == 0 && nums[right] == 0)
        {
            right ++;
        }  
        else if(nums[left] == 1 && nums[right] == 1 )
        {
            left ++;
            right ++;
        }
        else if(nums[left] == 0 && nums[right] == 1)
        {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right++;
        }
    }
}

// 给定数组 统计非重复元素的个数
int numOfNonDup(vector<int> &nums)
{
    int left = 0;
    int right = 1;
    int num = 0;
    sort(nums.begin(), nums.end());

    for(int i = 0; i < nums.size(); i++)
    {
        if(nums[left] == nums[right])
        {
            right++;
        }
        else
        {
            left ++;
            right ++;
            num ++;
        }
    }
    return num;
}

// 17. 双指针 two sum 问题

//给定数组和目标值 找到数组中两个和为目标值的数 可能有多组 数组中存在重复
vector<pair<int, int> > twosum(vector<int>nums, int target)
{
    vector<pair<int, int> >results;
    map<int, int> hash;

    for(int i = 0; i < nums.size(); i++)
    {
        hash[nums[i]] = i;
    }

    for(int i = 0; i < nums.size(); i++)
    {
        if(hash[target - nums[i]] && i < hash[target - nums[i]])
        {
            results.push_back(make_pair(nums[i], target-nums[i]));
            hash[target - nums[i]] = -1;
        }
    }
    return results;
}

// 给定了排序数组解决twosum问题 使用双指针
vector<pair<int, int> > twoSumSorted (vector<int> nums, int target)
{
    int left = 0;
    int right = nums.size() - 1;
    vector<pair<int ,int> > results;
    while(left < right)
    {
        if((nums[left] + nums[right]) > target)
        {
            while(nums[right] == nums[right - 1])
            {
                right --;
            }
            right --;
        }
        else if((nums[left] + nums[right]) < target)
        {
            while(nums[left] == nums[left + 1])
            {
                left ++;
            }
            left ++;
        }
        else
        {
            results.push_back(make_pair(nums[left], nums[right]));
            while(nums[right] == nums[right - 1])
            {
                right --;
            }
            while(nums[left] == nums[left + 1])
            {
                left ++;
            }
            right --;
            left ++;
        }
    }
    return results;
} 

// 给定一个数组 求出和为0 的三个数组 
// 双循环+哈希 排序后 循环+双指针
vector<vector<int> > threesum(vector<int> nums)
{
    vector< vector<int> >results;
    int l = 0;
    int r = nums.size() - 1;
    sort(nums.begin(), nums.end());
    

    for(int i = 0; i < nums.size(); i++)
    {
        while(l < r)
        {
            if(nums[l] + nums[r] + nums[i] > 0)
            {
                while(nums[r]==nums[r-1] || r == i)
                {
                    r--;
                }
                r--;
            }
            else if(nums[l] + nums[r] + nums[i] < 0 || l == i)
            {
                while(nums[l]==nums[l+1])
                {
                    l++;
                }
                l++;
            }
            else
            {
                vector<int> result;
                result.push_back(nums[l]);
                result.push_back(nums[r]);
                result.push_back(nums[i]);
                results.push_back(result);
                while(nums[r]==nums[r-1] || r == i)
                {
                    r--;
                }
                r--;
                while(nums[l]==nums[l+1])
                {
                    l++;
                }
                l++;
            }
        }
    }
    return results;
}
// 组成三角形的个数
int triangleCount(vector<int> nums)
{
    sort(nums.begin(), nums.end());
    int number = 0;

    for(int i = 0; i < nums.size() - 3; i++)
    {
        int l = i + 1;
        int r = nums.size() - 1;

        while(l < r)
        {
            if(nums[i] + nums[l] > nums[r])
            {
                number++;
                l++;
            }
            else
            {
                r--;
            }
        }
    }
    return number;
} 

//返回最接近目标值的两个数和
int closest(vector<int> nums, int target)
{
    sort(nums.begin(), nums.end());
    int minDist = 10000;
    int sum = 0;
    int l = 0;
    int r = nums.size() - 1;
    while(l < r)
    {
        int distance = abs(nums[l] + nums[r] - target);
        if(distance < minDist)
        {
            minDist = abs(nums[l] + nums[r] - target);
            sum = nums[l] + nums[r];
        }
        if(nums[l] + nums[r] > target)
        {
            while(nums[l] == nums[l+1])
            {
                l++;
            }
            l++;
        }
        if(nums[l] + nums[r] < target)
        {
            while(nums[r] == nums[r-1])
            {
                r++;
            }
            r++;
        }
    }
    return sum ;
}

// 18 双指针partition问题
//传入数组和分割值 把数组分割在值两边
void splitArray(vector<int> &nums, int k)
{
    int l = 0;
    int r = nums.size() - 1;
    while(l < r)
    {
        if(nums[r] < k)
        {
            int temp = nums[l];
            nums[l] = nums[r];
            nums[r] = temp;
            l ++ ;
        }
        if(nums[r] >= k)
        {
            r--;
        }
    }
}
// 给定数组含有 0 1 2 要求把0 1 2放在数组的左中右三个部分
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b= temp;

}
void partition3(vector<int> &nums)
{
    int l = 0;
    int r = nums.size() - 1;
    int m = l + 1;
    while(l < r)
    {
        if(nums[m] == 0)
        {
            swap(nums[m], nums[l]);
            l++;
        }
        else if(nums[m] == 2)
        {
            swap(nums[m], nums[r]);
            r++;
        }
        if(nums[m] == 1)
        {
            m++;
        }
        
    }
}

// 19 二分搜索
int findPosition(vector<int> nums, int target)
{
    if(nums.empty() || nums.size() == 0)
    {
        return -1;
    }
    int left = 0;
    int right = nums.size() - 1;
    while(left + 1 < right)
    {
        int mid = (left + right) / 2;
        if(nums[mid] > target)
        {
            right = mid;
        }
        else if(nums[mid] < target)
        {
            left = mid;
        }
        else
        {
            return mid;
        }
    }
    if(nums[left] == target)
    {
        return left;
    }
    return -1;
}

// 20. 逆置字符串 
struct ListNode
{
    int value;
    ListNode* next;
    ListNode(){}
    ListNode(int x): value(x) ,next(NULL){}
};

ListNode* reverse(ListNode* head)
{
    ListNode * pre = NULL;
    ListNode * next = NULL;
    while(head)
    {
        next = head -> next;
        head -> next = pre;
        pre = head;
        head = next;
    }
    return pre;
}
ListNode* reverseFromMtoN(ListNode* head, int m, int n)
{
    while(--m)
    {
        head = head -> next;
    }
    ListNode* node1 = head;
    ListNode* node2 = head->next;
    int len = n - m + 1;
    while(len --) 
    {
        head = head -> next;
    }
    ListNode* node3 = head;
    ListNode* node4 = head->next;
    head -> next = NULL;
    ListNode* temp = reverse(node2);

    node1->next = node3;
    node2->next = node4;

    return node1;
}
// 21 1维dp
int climbStairs(int n)
{
    //初始化
    vector<int> dp;
    for(int i = 0; i < n; i++)
    {
        dp.push_back(0);
    }
    //起点
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    //转移
    for(int i = 3; i < n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    } 
    //终点
    return dp[n];
}

int coinChange(vector<int> &coins, int sum)
{
    vector<int> dp;
    for(int i = 0; i < sum; i++)
    {
        dp.push_back(0);
    }

    dp[0] = 0;
    for(int i = 0; i < coins.size(); i ++ )
    {
        dp[coins[i]] = 1;
    }

    for(int i = 1; i < sum; i++)
    {
        for(int j = 0; j < coins.size(); j++)
        {
            if(i - coins[j] >= 0 && dp[i - coins[j]] != 0)
            {
                if(dp[i - coins[j]] < dp[i] || dp[i] == 0)
                {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
            
        }
    }
    return dp[sum];
}

int fibnacci(int n)
{
    vector<int> dp;
    for(int i = 0; i < n; i++)
    {
        dp.push_back(0);
    }

    dp[1] = 1;
    dp[2] = 1;
    for(int i = 3; i < n; i ++)
    {
        dp[i] = dp[i - 1] + dp[i -2];
    }
    return dp[n];
}

// 22. 坐标dp
int minPathInTri(vector<vector<int> > triangle)
{
    vector<vector<int> > dp;
    for(int i = 0; i < triangle.size(); i++)
    {
        dp.push_back(vector<int>());
        for(int j = 0; j < triangle[i].size(); j++)
        {
            dp[i].push_back(0);
        }
    }
    dp[0][0] = triangle[0][0];
    for(int i = 1; i < triangle.size(); i++)
    {
        dp[i][0] += dp[i - 1][0];
        dp[i][i] += dp[i - 1][i - 1];
    }

    for(int i = 1 ; i < triangle.size() ; i++)
    {
        for(int j = 1; j < triangle.size() - 1; j++)
        {
            dp[i][j] += min(dp[i - 1][j - 1], dp[i - 1][j]);
        }
    }
    int re = 1000;
    for(int i = 0; i < triangle.size(); i++)
    {
        if(dp[triangle.size() - 1][i] < re)
        {
            re = dp[triangle.size() - 1][i];
        }
    }
    return re;
}

int minPathInRec(vector< vector<int> > &rec)
{
    vector< vector<int> > dp;
    for(int i = 0; i < dp.size(); i++)
    {
        dp.push_back(vector<int>());
        for(int j = 0; j < dp[i].size(); j++)
        {
            dp[i].push_back(0);
        }
    }
    dp[0][0] = rec[0][0];
    for(int i = 1; i < rec.size(); i++)
    {
        dp[i][0] = dp[i - 1][0];
        dp[0][i] = dp[0][i - 1];
    }

    for(int i = 1; i < rec.size(); i++)
    {
        for(int j = 1; j < rec.size(); j++)
        {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + rec[i][j];
        }
    }
    return dp[rec.size() - 1][rec.size() - 1];
}
// 23 序列型
int maxSubarray(vector<int> &nums)
//给定数组 求最大子数组和 求子数组暴力有n^2 子序列有2^n 子集有n!
{
    vector<int> dp; //以i结尾的最大子数组和 
    for(int i = 0; i < nums.size(); i++)
    {
        dp.push_back(0);
    }
    dp[0] = nums[0];

    int re = dp[0];
    for(int i = 0; i < nums.size(); i++)
    {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        if(dp[i] > re)
        {
            re = dp[i];
        }
    }
    return re;
}

int longestSubseq(vector<int> &nums)
// 传入数组 返回最长递增子序列的长度
{
    vector<int> dp; //i为尾部的最长子序列
    for(int i = 0; i < nums.size(); i ++)
    {
        dp.push_back(0);
    }

    dp[0] = 1;
    int maxL = 0;
    for(int i = 1; i < nums.size(); i++)
    {
        
        for(int j = 1; j < i; j++)
        {
            if(nums[i] > nums[j])
            {
                if(dp[i] < dp[j] + 1)
                {
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if(maxL < dp[i])
        {
            maxL = dp[i];
        }
        
    }
    return maxL;
}

// 24 merge
vector<int> merge2sortedArray(vector<int> arr1, vector<int> arr2)
{
    int p1 = 0;
    int p2 = 0;
    vector<int> merged;

    while(p1 > arr1.size() - 1 && p2 > arr2.size() - 1)
    {
        if(arr1[p1] >= arr2[p2])
        {
            merged.push_back(arr2[p2]);
            p2++;
        }
        else
        {
            merged.push_back(arr1[p1]);
            p1++;
        }
    }

    if(p1 == arr1.size())
    {
        while(p2 > arr2.size() - 1)
        {
            merged.push_back(arr2[p2]);
            p2++;
        }
    }
    if(p2 == arr2.size())
    {
        while(p1 > arr1.size() - 1)
        {
            merged.push_back(arr1[p1]);
            p2++;
        }
    }
    return merged;
}

vector<int> mergeSort(vector<int> &arr)
{
    if(arr.size() == 1)
    {
        return arr;
    }
    int mid = (arr.size() -1)  / 2;
    vector<int> subarr1;
    vector<int> subarr2;

    for(int i = 0; i < arr.size() - 1; i++)
    {
        if(i <= mid)
        {
            subarr1.push_back(arr[i]);
        }
        else
        {
            subarr2.push_back(arr[i]);
        }
    }

    vector<int> sortedarr1 = mergeSort(subarr1);
    vector<int> sortedarr2 = mergeSort(subarr2);

    return merge2sortedArray(sortedarr1, sortedarr2);

}

vector<int> mergeKSortArray(vector<vector<int> > narr)
{
    int mid = (narr.size() - 1) / 2;
    vector< vector<int> > arrs1;
    vector< vector<int> > arrs2;
    vector<int> sortedarrs1;
    vector<int> sortedarrs2;

    for(int i = 0; i < narr.size(); i++)
    {
        if(i <= mid)
        {
            arrs1.push_back(narr[i]);
        }
        else
        {
            arrs2.push_back(narr[i]);
        }
    }

    sortedarrs1 = mergeKSortArray(arrs1);
    sortedarrs2 = mergeKSortArray(arrs2);

    return merge2sortedArray(sortedarrs1, sortedarrs2);
}

// 25. dfs template
struct treenode
{
    int value;
    treenode* l;
    treenode* r;
    treenode(int x): value(x), l(NULL), r(NULL){}
};

void simpleDFS(TreeNode* root)
{
    if(!root)
    {
        return;
    }
    cout << root->value<<endl;

    simpleDFS(root->left);
    simpleDFS(root->right);
}

// 遍历实现dfs 返回遍历结果
void recursion(vector<int> &result, TreeNode* root)
{
    if(!root)
    {
        return;
    }
    result.push_back(root->value);

    recursion(result, root->left);
    recursion(result, root->right);

}
vector<int> treeDFSbyTraversal(TreeNode* root)
{
    vector<int> result;
    recursion(result, root);
    return result;
}

//分支实现
vector<int> DFSbyDC(TreeNode* root)
{
    vector<int> lresult;
    vector<int> rresult;
    vector<int> r;

    lresult = DFSbyDC(root->left);
    rresult = DFSbyDC(root->right);

    r.push_back(root->value);
    r.insert(r.end(), lresult.begin(), lresult.end());
    r.insert(r.end(), rresult.begin(), rresult.end());

    return r;
}

// 26.求数高
//遍历实现 
void recurDepth(TreeNode* root, int &result, int level)
{
    if(root == NULL)
    {
        return;
    }
    result = max(result, level);

    recurDepth(root->left, result, level+1);
    recurDepth(root->right, result, level+1);
}
int depth(TreeNode * root)
{
    int result = 0;
    recurDepth(root, result, 0);
    return result;
}

//分治实现
int depthByDC(TreeNode * root)
{
    int result;
    if(root == NULL)
    {
        return 0;
    }
    int l = depthByDC(root -> left);
    int r = depthByDC(root -> right);

    return max(l, r) + 1;
}
// 27. 传入根节点和目标sum 找到所有根节点到叶节点路径和为sum的路径
void recSum(TreeNode* root, int target, vector<vector<int> >&results, vector<int> &result, int &sum)
{
    if(root == NULL)
    {
        if(sum == target)
        {
            results.push_back(result);
        }
    }
    result.push_back(root->value);
    sum += root->value;

    recSum(root->left, target, results, result, sum);
    recSum(root->right, target, results, result, sum);

    result.pop_back();
    sum-= root->value;

}

vector< vector<int> > pathSum(TreeNode* root, int target)
{
    vector<vector<int> >results;
    int sum = 0;
    vector<int> result;
    recSum(root, target, results, result, sum);
    return results;
}

// 28 最大均值子树
struct resultType
{
    int num;
    int sum;
    TreeNode* head;
    resultType();
    resultType(int x, int y): num(x), sum(y){}
    resultType(int x, int y, TreeNode* z): num(x), sum(y), head(z){}
};

resultType recMaxSub(TreeNode* root, resultType maxAvg)
{
    
    if(root == NULL)
    {
        return resultType(0,0);
    }
    resultType lresult = recMaxSub(root->left, maxAvg);
    resultType rresult = recMaxSub(root->right, maxAvg);
    
    double avg = (lresult.sum + rresult.sum)  / (lresult.num + rresult.num);
    if(avg > maxAvg)
    {
        maxAvg = avg;
    }
    return resultType(lresult.sum + rresult.sum, lresult.num + rresult.num) ;
    

}
TreeNode* maxSub(TreeNode* root)
{
    TreeNode* result;
    resultType maxAvg(-100, -100);
    recMaxSub(root, maxAvg);
    return maxAvg.head;
}

//29. 求子集问题
void dfsByMtree(vector<int> &nums, vector<vector<int> > &subsets, vector<int> &subset)
{
    
}
vector<vector<int> > subset(vector<int> &nums)
{
    vector<vector<int> > subsets;
    vector<int> subset;
    dfsByMtree(nums, subsets, subset);
    return subsets;
}


int main()
{
    vector<int> a;
    a.push_back(3);
    a.push_back(4);
    a.push_back(6);
    a.push_back(1);
    a.push_back(5);
    a.push_back(2);
    splitArray(a, 4);
    for(int i = 0; i < 6; i++)
    {
        cout << a[i] << endl;
    }
}

#include<iostream>
#include<vector>
using namespace std;

/*
传入两个有序数组 求出所有元素的 中位数
第一种思路是将二者归并后直接返回直接中位数 时间复杂度为两个数组的长度之和 O(m+n)
第二种思路是是第一种的改进 我们每次取出两个数组的头部元素比较 舍弃较小的 继续比较 一直比较到第(m+n)/2个元素时 就是我们需要的 而不需要全部归并 也不需要真的把归并结果存储起来 因为我们只需要找到第(m+n)/2个数即可 
从这个思路的基础上继续思考 我们希望找到归并后第k=(m+n)/2个数 那么我们不停的删除第k个数之前的数 当我们删掉前k-1个数 那么就把问题转化为找第一个数
那么 能否削减k次的步骤？
二分法可以时间复杂度优化到O(log(m+n))
这道题无法直接用模板或者ooxx 那么就思考 如何在o(1)的时间内 保留有解的部分 削除没有解的部分

我们希望删除k-1个数 找到第k个数 那么如果每次删除k/2个数 然后继续找到第 k - k/2个数 然后继续删除 (k - k/2) / 2个数 
这样就可以把时间复杂度优化为log级别
我们的策略是 比较两个数组的 第k/2个元素 比较两个元素的大小 哪个小 就把它之前的数全部删掉
逻辑是 这两组有序的k/2个数 头较小的那一组中一定不会有第k个数 
因为第k个数一定比k-1个数都要大 但头较小的那一组中 即使是最大的头部元素 也只比本组的k/2-1个元素大 放到头较大的那组中 更不可能比k/2个元素大 因为它以已经比那一组中第k/2个元素小了 所以整体看 它不可能比k-1个元素大
这就是将解空间减半的逻辑 不是很好想到 核心是 第k个数一定比k-1个数都要大 分开在两个数组中考虑 可能比自己大的元素的个数 然后加起来 看看有没有可能是解

具体实现时 虽然数组大小为奇数和 为偶数时不同 为偶数时要考虑两个数的平均 但无非是找到两个数 第k个和第k+1个 两次调用一个找数的函数即可
因此 有了这个思想 事实上我们可以用来找两个数组归并后任何次序的数
此外 注意数组索引和序号不要混用
*/

int findKthNumber (vector<int> arr1, vector<int> arr2, int targetIndex) //传入的是目标序号 不是索引 比如9个数中的第5个数
{
    int numOfTotal = arr1.size() + arr2.size();    //初始全部元素个数
    int ptr1 = 0;                                  //初始数组起始点                       
    int ptr2 = 0;
    int tryOfArr1;
    int tryOfArr2; 
    int numOfAbandon = targetIndex - 1;         //总共要丢弃的数字的个数 比如查找第7个数 则要丢弃6个数
    while(numOfAbandon)
    {
        cout << "当前待丢弃数量为：" << numOfAbandon << endl;
        int currentAbandon = (numOfAbandon + 1) / 2;    //此次比较要丢弃数字的数量 总共要丢弃6个 则此次丢弃3个 总共要丢弃7个 则此次丢弃4个
        //找到各数组的arr[k/2] 丢弃6个数 比较arr[3] 丢弃7个数 比较arr[4] 
        //考虑特殊情况 当k/2超出数组长度
        if(numOfAbandon / 2 >= arr1.size())    
        {
            tryOfArr1 = arr1[arr1.size() - 1];
            cout << "越界，arr1选取最后一个数进行比较：" << tryOfArr1 << endl;
        }
        else
        {
            tryOfArr1 = arr1[ptr1 + currentAbandon];
            cout << "arr1选取第" << currentAbandon + 1 << "个数进行比较：" << tryOfArr1 << endl;
        }
        if(numOfAbandon / 2 >= arr2.size())
        {
            tryOfArr2 = arr2[arr2.size() - 1];
            cout << "越界，arr2选取最后一个数进行比较：" << tryOfArr2 << endl;
        }
        else
        {
            tryOfArr2 = arr2[ptr2 + currentAbandon];
            cout << "arr2选取第" << (numOfAbandon + 1) / 2 + 1 << "个数进行比较：" << tryOfArr2 << endl;

        }
        // 比较arr[k/2] 进行解空间的衰减
        // 目标丢弃6个数 则比较arr[3] 每次丢弃3个数 arr[0,1,2] 丢弃7个数则比较arr[4] 每次丢弃4个数（这些数里最多也就比6个数大）然后数组起点设为arr[4]
        if(tryOfArr1 >= tryOfArr2)
        {
            ptr2 += currentAbandon;   //数组起点加上丢弃的数 表明舍弃3个数
            cout << "这一次比较 arr2舍弃了" << (numOfAbandon + 1) / 2 << "个数" << endl;
        }
        else
        {
            ptr1 += currentAbandon;
            cout << "这一次比较 arr1舍弃了" << (numOfAbandon + 1) / 2 << "个数" << endl;

        }
        numOfAbandon -= currentAbandon;   //更新总共要丢弃的数
    }
    //若numOfAbandon = 0 表明没有要丢弃的数 则直接比较首元素 丢弃了k-1个数 当前最小的数就是第k个数
    if(arr1[ptr1] > arr2[ptr2])
    {
        return arr2[ptr2];
    }
    return arr1[ptr1];
}

int findMedian(vector<int> arr1, vector<int> arr2)
{
    
    int totalNumber = arr1.size() + arr2.size();
    cout << "元素总个数为：" << totalNumber << endl;
    if(totalNumber % 2 == 0)
    {
        return (findKthNumber(arr1, arr2, totalNumber / 2) + findKthNumber(arr1, arr2, totalNumber / 2 + 1)) / 2;
    }
    else
    {
        return findKthNumber(arr1, arr2, (totalNumber + 1) / 2);
    }
}

int main()
{
    int t1[] = {1,2,3,4};
    int t2[] = {5,6,7};
    vector<int> arr1(t1, t1 + 4);
    vector<int> arr2(t2, t2 + 3);
    cout << findKthNumber(arr1, arr2, 5);
}
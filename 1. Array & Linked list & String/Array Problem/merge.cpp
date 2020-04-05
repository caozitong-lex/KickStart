#include<vector>
#include<iostream>
#include<queue>
using namespace std;

// 重载输出运算符 对vector使用
ostream& operator<<(ostream &os, vector<int> &vec)
{
    for(int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] <<" ";
    }
    return os;
}

//传入两个有序数组 合并它们使得合并数组仍然有序 
//无法原地合并 需要另外创建数组 因此传入不需要传引用 新建数组合并后也不需要返回引用 直接返回即可
vector<int> merge2SortedArray (vector<int> array1, vector<int> array2)
{
    vector<int> mergedArray;
    int ptr1 = 0; //注意 int a, b = 0; 只有b初始化为0 a是被随机赋值的
    int ptr2 = 0;

    while(ptr1 < array1.size() && ptr2 < array2.size())
    {
        
        if(array1[ptr1] < array2[ptr2])
        {
            mergedArray.push_back(array1[ptr1]);
            ptr1++;
        }
        else
        {
            mergedArray.push_back(array2[ptr2]);
            ptr2++;
        }
    }
    // 循环结束表明有一个数组被抽取完 另一个数组还剩余
    // 此时ptr还都保持在循环结束的状态 继续循环即可
    for(int i = ptr1; i < array1.size(); i++)
    {
        mergedArray.push_back(array1[i]);
    }
    for(int i = ptr2; i < array2.size(); i++)
    {
        mergedArray.push_back(array2[i]);
    }
    return mergedArray;
} 
//非原地排序 
vector<int> mergeSort (vector<int> &unsortedArray)
// 归并排序 分治法 分解成元问题后合并解
// 把数组分成两个子数组进行排序
// 前序分解 中序遍历 后序合并解
// 其实在合并解的过程中 有很多种合并方式 见k路归并 往往在两两归并的nklogk中 和连续归并的nk^2中选择 
// 两两归并的优势在于合并轮数少 logk次 但每次参与合并的元素多 nk个 而连续归并的合并轮数多 k次 每次参与合并的元素少 平均是nk/2
// 显然轮数的优化是数量级的优化 k -> logk 而参与合并的元素的优化是线性的 nk和 nk/2
{
    //元问题的解
    if(unsortedArray.size() == 1)
    {
        return unsortedArray;
    }
    //构造局部笔记本
    vector<int> sortedArray;
    int seperatePoint = unsortedArray.size() / 2;
    vector<int> subArray1;
    vector<int> subArray2;

    for(int i = 0; i < seperatePoint; i++)
    {
        subArray1.push_back(unsortedArray[i]);
    }
    for(int i = seperatePoint; i < unsortedArray.size(); i++)
    {
        subArray2.push_back(unsortedArray[i]);
    }
    //递归收集子问题的解
    vector<int> sortedSubArray1 = mergeSort(subArray1);
    vector<int> sortedSubArray2 = mergeSort(subArray2);
    //合并子问题的解
    return merge2SortedArray(sortedSubArray1, sortedSubArray2);
}

vector<int> mergeKSortedArray(vector< vector<int> > &kArrays)
//k个排序数组/链表进行归并
// 1. K个数组 平均数组长度为n 每次比较头部取出最小 也就是每次找到最小值需要logk的时间（堆的求最小值时间为1 求完最小值需要pop旧点push新点 时间复杂度为logk）取出kn个节点总共是nklogk
// 2. 把K个数组的kn个数全部合并直接排序 需要 kn + nklogkn的时间
// 3. 两两合并数组 以数组为单位进行归并 需要合并logk次 每次参与合并的元素总数始终是全部元素个 也就是kn 因此最终时间复杂度为knlogk
// 4. 1和2合并 12和3合并...  12..k-1和k合并 合并 k-1次  每次参与合并元素个数为2n,  3n,  ...4n 平均是kn/2个 时间复杂度为 nk^2
// 13是最快的两种 k个数组合并时使用3思路实现 本质上3就是归并排序 只不过归并排序是对n个元素 分解-合并 k路归并是对k个数组 分解-合并 
// 归并排序是为了把数组分解成单个元素 然后把n个元素两两合并  k路归并是把k个数组分解为单个数组 再把k个有序数组两两合并 有序数组的角色和单个元素的角色是相同的
// 对于k个数组问题使用1方法较麻烦 需要重写堆节点类 除了节点值 还有节点所在数组的序号 因为需要记录每个数组的游标 比较最小值后 需要知道最小节点来自于哪个数组https://blog.csdn.net/u012328476/article/details/52522900
{
    // 和归并排序相同 只不过把归并排序中的单个元素 看做 k路归并中的一个有序数组 
    // 分解到单个有序数组 则直接返回
    if(kArrays.size() == 1)
    {
        return kArrays[0];
    }
    // 声明局部笔记本
    vector<int> mergedArray;
    // 把原问题分解
    vector< vector<int> >subArrays1;
    vector< vector<int> >subArrays2;
    int seperatePoint = kArrays.size() / 2;
    // 构造子问题
    for(int i = 0; i < seperatePoint; i++)
    {
        subArrays1.push_back(kArrays[i]);
    } 
    for(int i = seperatePoint; i < kArrays.size(); i++)
    {
        subArrays2.push_back(kArrays[i]);
    }
    //收集子问题的解
    vector<int> sortedSubArray1 = mergeKSortedArray(subArrays1);
    vector<int> sortedSubArray2 = mergeKSortedArray(subArrays2);
    //cout << sortedSubArray1<<endl;
    //cout << sortedSubArray2<<endl;
    //合并解
    return merge2SortedArray(sortedSubArray1, sortedSubArray2);
    
}


int main()
{
    vector<int> arr1, arr2, arr3;
    arr1.push_back(1);
    arr1.push_back(3);
    arr2.push_back(2);    
    arr2.push_back(5);
    arr3.push_back(1);
    arr3.push_back(9);
    vector< vector<int> > k;
    k.push_back(arr1);
    k.push_back(arr2);
    k.push_back(arr3); 
    vector<int> r;
    r = mergeKSortedArray(k);
    for(int i = 0; i < r.size(); i++)
    {
        cout << r[i];
    }
}
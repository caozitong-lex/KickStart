#include<iostream>
#include<stack>
#include<queue>
using namespace std;

/*
简单计算器：输入一个合法的数学表达式字符串 包括加减括号 返回计算器所计算的值
基本思路 是设计两个栈 数字栈和操作符号栈 当有两个数字+一个符号时 即可出栈进行计算 将结果接着放入数字栈中
难点是流程的实现 以及多种情况的考虑 设计较为巧妙 尤其是 遇到左括号改变标记 右括号直接计算 加减号改变标记 数字后判断计算 几个时机非常关键 半背诵
n个数字组成的算式 无论符号怎么使用 一定 经过了n-1次计算 因此每一次计算都是数字的缩减 重要的是计算的时机 理论上除了第一个数 之后遇到每一个数都会发生运算 比如 1 + 2 + 3 遇到2时一定存在计算（得到3） 遇到3时一定还是存在计算（得到6） 
所以每次检查到一个数都会判断是否计算 而(阻止的计算 会在)弥补回来 这样的机制确保了n-1次计算
实现方式是有限自动机 遍历字符串每一个字符 每个字符下都有操作符号状态或数字状态 
每检测到一个新的字符 根据内容进行操作或状态转换

*/
void operate(stack<char> &operators, stack<int> &numbers)
{
    // corner case : 只有一个操作数时
    if(numbers.size() < 2)  
    {
        return;
    }
    //取出两个操作数和操作符
    char oper = operators.top();
    operators.pop();
    int num1 = numbers.top();
    numbers.pop();
    int num2 = numbers.top();
    numbers.pop();
    //进行 计算
    if(oper == '+')
    {
        numbers.push(num1 + num2);
    }
    else
    {
        numbers.push(num2 - num1);
    }
}

int calculator(string s)
{
    //三个状态常量
    const int BEGIN_STATE = 0;
    const int NUMBER_STATE = 1;
    const int OPERATION_STATE = 2;
    //两个辅助栈
    stack<char> operators;
    stack<int> numbers;
    //辅助变量初始化 
    int stateID = BEGIN_STATE;  //初始状态
    int flag = 0;               //可计算标志
    int number = 0;             //字符串转数字

    for(int i = 0; i < s.size(); i++)   //扫描字符串遍历每个字符 根据字符内容进行操作/状态转换
    {
        switch (stateID)                //根据当前状态进行操作
        {
        case BEGIN_STATE:
            if(s[i] >= '0' && s[i] <=  '9') //若扫描到数字
            {
                stateID = NUMBER_STATE;     //进入数字状态
                i --;                       //退回i 重新扫描 使得进入数字状态后重新取得该数字
            }
            else
            {
                stateID = OPERATION_STATE;  //进入操作符状态
                i --;
            }
            break;
        
        case NUMBER_STATE:
            if(s[i] >= '0' && s[i] <=  '9') //若扫描到数字 则进行字符串转数字操作 
            {
                number = 10 * number + (s[i] - '0');    
            }
            else                            //若终于扫描到符号 
            {
                numbers.push(number);       //首先把转化好的数字压入数字栈
                if(flag == 1)               //根据运算标记判断能否运算
                {
                    operate(operators, numbers);
                }
                number = 0;                 //重置 等待下一个数字
                stateID = OPERATION_STATE;  //由于数字已经结束 则进入操作符号状态 并退回i
                i --;
            }
            break;
        
        case OPERATION_STATE:
            if(s[i] == '+' || s[i] == '-')  // 若扫描到加减号
            {
                operators.push(s[i]);       // 加入符号栈
                flag = 1;                   // 加减号的出现表示一旦有下一个操作数就可以计算 
            }
            else if(s[i] == '(')
            {
                flag = 0;                   //阻隔计算 比如 1 + (2 ... 此时不能计算
            }
            else if(s[i] == ')')            // 扫描到) 启动计算 表明括号部分完毕 可以直接计算
            {
                operate(operators, numbers);// 这个设计非常巧妙 因为每次遇到(就阻止了一次计算 而所有数字的总计算次数是相同的 n个数字组成的算式 无论符号怎么使用 一定 经过了n-1次计算 因此(阻止的计算 在)时要补偿回来 
            }
            else                            // 扫描到数字   
            {
                stateID = NUMBER_STATE;     // 表明符号部分完毕    
                i --;                       // 退回 使得数字状态可以重新读取
            }
            break;
        }
    }
    if(number != 0)      //若字符串末尾形如  + 31 那么扫描到1时 没有下个符号告知数字结束 因此需要自行结束数字并计算 相当于扫描到了符号
    {
        numbers.push(number);
        operate(operators, numbers);
    }
    if(numbers.empty()) //数字栈中为空 表明无计算结果
    {
        return 0;
    }
    return numbers.top();       //理应数字栈中最后只剩下最后计算结果
}

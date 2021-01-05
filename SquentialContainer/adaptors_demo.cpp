#include<stack>
#include<queue>
#include<iostream>
// stack 和 queue 默认基于 deque 实现
// priority_queue 默认基于 vector 上实现, priority 要求随机访问能力
using namespace std;
int main(){
    stack<int> S; // 栈可基于vector，deque，list实现，默认deque
    /*
    s.pop()
    s.push()
    s.emplace()
    s.top()
    */
    queue<int> Q; // 队列可基于vector，deque，list实现，默认deque
    /*
    s.pop()
    s.push()
    s.emplace()
    s.front()
    s.back()
    */
    priority_queue<int> PQ; // 优先队列可基于vector，deque实现，默认vector
    /*
    s.pop()
    s.push()
    s.emplace()
    s.top() // 返回优先级最高的元素,默认使用<运算符确认优先级
    */
    PQ.push(5);
    PQ.push(1);
    PQ.push(3);
    PQ.push(6);
    PQ.push(7);
    cout << PQ.top() << endl;
    PQ.pop();
    cout << PQ.top() << endl;
    PQ.pop();
    cout << PQ.top() << endl;
    return 0;
}
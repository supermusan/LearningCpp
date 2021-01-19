// 通常，使用deque是最好的选择
#include<deque>
#include<list>
#include<string>
#include<iostream>
// 可变大小数组，支持快速随机访问，尾插很快，其他地方插入可能很慢
using namespace std;
ostream &printDeqInt(ostream &os, const deque<int> &deq){
    if(deq.empty()){
        os << "Empty Deque.";
        return os;
    }
    for(auto item:deq)
        os << item << " ";
    return os;
}
int main(){
    // 构造函数
    deque<int> deq1;
    deq1.push_back(1); //尾插
    deq1.push_back(2);
    printDeqInt(cout, deq1) << endl;
    deque<int> deq2(deq1);
    printDeqInt(cout, deq2) << endl;
    deque<int> deq3(deq1.begin(), --deq1.end());
    printDeqInt(cout, deq3) << endl;
    deque<int> deq4{4,3,2,1};
    printDeqInt(cout, deq4) << endl;
    deque<int> deq5 = deq4;
    printDeqInt(cout, deq5) << endl;
    deque<int> deq6(5,1);
    printDeqInt(cout, deq6) << endl;

    // 容器大小
    cout << deq4.size() << " " << deq4.max_size() << endl;


    // 添加元素
    deque<int> deq{1,2,3,4};
    deq.push_back(5);
    deq.push_front(0);
    deq.insert(deq.insert(deq.insert(deq.begin(),{0,0}),-1), deq1.begin(), deq1.end()); //返回一个迭代器指向插入的元素
    printDeqInt(cout, deq) << endl;
    
    // 访问元素
    /*
    c.back()
    c.front()
    c[n]
    c.at(n) 若越界会抛出异常
    返回的都是引用
    */
    deq.front() = 111;
    // 若用auto,且需要改变元素,要显示定义为引用
    auto &v = deq.back();
    v = 999; //改变元素
    auto v2 = deq.back();
    v2 = 9999; //不改变元素
    printDeqInt(cout, deq) << endl;
    try{
        deq.at(100);
    }
    catch(exception& e){
        cout << e.what() << endl;
    }

    // 删除元素
    /*
    c.pop_back()
    c.erase(p)
    c.erase(b,e)
    c.clear()
    */
    deq.pop_front();
    printDeqInt(cout, deq) << endl;
    deq.pop_back();
    printDeqInt(cout, deq) << endl;
    deq.erase(deq.begin(), deq.begin()+2);
    printDeqInt(cout, deq) << endl;    
    deq.erase(--deq.end());
    printDeqInt(cout, deq) << endl;
    deq.clear();
    printDeqInt(cout, deq) << endl;

    return 0;
}


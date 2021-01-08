#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<typeinfo>
using namespace std;
/*
静态内存
+ 局部static对象，
+ 类static数据成员
+ 定义在任何函数之外的变量
栈内存
+ 定义在函数内的非static对象
堆
+ 存储动态分配的对象
*/
int main(){
    /*
    初始化总结：
    shared_ptr:
    + 初始化为空指针
    + make_shared()
    + (new )
    + (p)
    unique_ptr
    + (new)
    + (p)
    */
    /*
    shared_ptr 和 unique_ptr 都支持的操作
    shared_ptr<T> sp;
    unique_ptr<T> up; // 初始化空智能指针，指向类型为T的对象
    p 用作条件判断，若指向一个对象则为true
    *p 解引用
    p->mem
    p.get() 返回p中保存的指针
    swap(p, q)
    p.swap(q) //交换p、q中的指针
    */
    /*
    shared_ptr都有操作
    make_shared<T> (args)
    shared_ptr<T>p (q) 递增q的引用计数
    p=q 递减p的引用计数，递增q的引用计数
    p.unique() 若 p.use_count()==1，返回true
    p.use_count() 与p共享对象的智能指针数
    */
    shared_ptr<int> p1 = make_shared<int>(42);
    shared_ptr<string> p2 = make_shared<string>(5,'a');
    shared_ptr<int> p3 = make_shared<int>();
    cout << *p1 << " " << *p2 << " "<< *p3 << endl;

    auto p = make_shared<int>(42);
    cout << p.use_count() << endl;
    auto q(p);
    cout << p.use_count() << " " << q.use_count() << endl;
    *q = 12;
    cout << *p << p.use_count() << endl;
    auto r = make_shared<int>(10);
    p = r;
    cout << p.use_count() << " " << q.use_count() << " " << r.use_count() << endl;

    // 程序使用动态内存的原因
    /*
    + 程序不知道自己需要使用多少对象
    + 程序不知道所需对象的准确类型
    + 程序需要在多个对象间共享数据
    */
    // 一个共享数据的例子 见 exp1_shared_ptr.cpp

    // 直接管理内存 new delete
    
    // shared_ptr 和 new 混合使用
    // 可以使用直接初始化的方式来用new初始化一个智能指针
    shared_ptr<int> p4(new int(42));
    // shared_ptr<int> p4 = new int(42); 错误！！！
    /*
    定义和改变 shared_ptr 的其他方法
    shared_ptr<T> p(q) q指向new分配的内存
    shared_ptr<T> p(u) p从unique_ptr u那里接管了所有权；将u置为空
    shared_ptr<T> p(q, d) p接管内置指针q指向的对象的所有权，d为可调用对象，代替delete
    shared_ptr<T> p(q2, d) p是shared_ptr p2的拷贝，用d代替delete
    p.reset() 
    p.reset(q)
    p.reset(q, d) 把p指向q，否则置为空
    */

    // 不要混用普通指针和只能指针，一旦用一个智能指针接管一个普通指针指向的内存，就不要再用普通指针访问该内存了
    // 不要用get初始化另一个智能指针或为智能指针赋值，get返回一个内置指针

    // 智能指针与异常
    // 异常发生后，离开作用域，智能指针可自动释放

    // 一个 shared_ptr 被销毁时，默认对管理的指针进行 delete 操作。可以自定义删除器来代替delete操作
    /*
    shared_ptr<sometype> p(&c, deleter);
    如果使用智能指针管理的资源不是new分配的内存，要传递给他一个删除器
    */
    
    // unique_ptr
    // 必须采用直接初始化
    // unique_ptr 拥有它指向的对象，因此unique_ptr不支持普通的拷贝或赋值操作
    /*
    u = nullptr 释放u指向的对象，将u置为空
    u.release() u放弃对指针的控制权，返回指针，并将u置为空
    u.reset()
    u.reset(q)
    u.reset(nullptr)
    */
    unique_ptr<string> up1(new string("test"));
    unique_ptr<string> up2(up1.release());
    unique_ptr<string> up3(new string("test2"));
    cout  << *up2 << " " << *up3 << endl;
    up2.reset(up3.release());
    cout << *up2 << endl;

    // weak_ptr
    // 将 weak_ptr 绑定到一个 shared_ptr 上，不会改变shared_ptr的引用计数
    /*
    weak_ptr<T> w
    weak_ptr<T> w(sp)
    w = p
    w.reset()
    w.use_count() 共享对象的shared_ptr数量
    w.expired() 若 w.use_count()为0，返回true
    w.lock() 若 w.expired 为true，返回一个空 shared_ptr，否则返回一个指向w对象的shared_ptr
    */
    // 利用 weak_ptr做核查指针类，见exp1_shared_ptr.cpp
    


    
    return 0;
}

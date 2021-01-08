// 大多数应用应该使用标准库容器而不是动态分配的数组
#include<iostream>
#include<string>
#include<memory>
#include<vector>
using namespace std;
int main(){
    // new 分配一个int数组，会得到一个元素类型的指针，不能使用下标运算符
    int *pia = new int[42];
    delete [] pia; // 释放数组
    int *pia2 = new int[5]{0,2,3,4,5};
    delete [] pia2;

    // 利用 unique_ptr 管理 new 动态分配的数组，可以使用下标运算符; shared_ptr不支持
    unique_ptr<int[]> up(new int[10]);
    up.release(); //自动调用delete[]销毁其指针
    /*
    unique_ptr<T[]> u  u指向一个动态分配的数组
    unique_ptr<T[]> u(p)  内置指针p指向一个动态分配的数组
    u[i]
    */

    // allocator 类
    /*
    将内存分配和对象构造组合在一起会导致不必要的浪费
    new int [n]
    初始化了n个int
    + 可能用不到这么多
    + 被赋值了两次——初始化+赋予新值
    
    allocator 将内存分配和对象构造分离开
    */
    size_t n =10;
    allocator<string> alloc; // 可以分配string的allocator对象
    auto const p = alloc.allocate(n); // 分配n个未初始化的string
    /*
    allocator<T> a
    a.allocate(n)
    a.deallocate(p, n) 释放从T*指针p中开始的内存，这块内存保存了n个类型为T的对象；p必须是一个先前由allocator返回的指针，且n必须为p创建时所要求的大小。调用deallocate之前，用户必须对每个在这块内存中创建的对象调用destroy
    a.construct(p, args) p是一个类型为T*的指针，只想一块原始内存；用来在p指向的内存中构造一个对象
    a.destroy(p) 对p指向的对象执行析构函数
    */
    auto q = p; //怕只想最后构造的元素之后的位置
    alloc.construct(q++,10,'a');
    alloc.construct(q++);
    alloc.construct(q++,"hi");
    cout << *p << endl;
    while(q!=p){
        alloc.destroy(--q);
    }
    alloc.deallocate(p, n);

    // 填充和拷贝未初始化内存的算法
    /*
    uninitialized_copy(b,e,b2) 从[b,e)拷贝元素到b2指定的为构造的原始内存中
    uninitialized_copy_n(b,n,b2)
    uninitialized_fill(b,e,t)
    uninitialized_fill_n(b,n,t)
    */
    vector<string> vec{"This","is","a","sentence."};
    string *p1 = alloc.allocate(2*vec.size());
    string *q1 = uninitialized_copy(vec.begin(), vec.end(), p1);
    auto q2 = uninitialized_fill_n(q1, vec.size(), "#");
    while (p1!=q2)
    {
        cout << *--q2 << " ";
    }
    
    return 0;
}
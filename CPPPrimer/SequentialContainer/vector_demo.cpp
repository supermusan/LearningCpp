// 通常，使用vector是最好的选择
#include<vector>
#include<string>
#include<list>
#include<iostream>
// 可变大小数组，支持快速随机访问，尾插很快，其他地方插入可能很慢
using namespace std;
ostream &printVecInt(ostream &os, const vector<int> &vec){
    if(vec.empty()){
        os << "Empty Vector.";
        return os;
    }
    for(auto item:vec)
        os << item << " ";
    return os;
}
ostream &printListString(ostream &os, const list<string> &li){
    for(auto item:li)
        os << item << " ";
    return os;
}
int main(){
    // 构造函数
    vector<int> vec1;
    vec1.push_back(1); //尾插
    vec1.push_back(2);
    printVecInt(cout, vec1) << endl;
    vector<int> vec2(vec1);
    printVecInt(cout, vec2) << endl;
    vector<int> vec3(vec1.begin(), --vec1.end());
    printVecInt(cout, vec3) << endl;
    vector<int> vec4{4,3,2,1};
    printVecInt(cout, vec4) << endl;
    vector<int> vec5 = vec4;
    printVecInt(cout, vec5) << endl;
    vector<int> vec6(5,1);
    printVecInt(cout, vec6) << endl;

    // 除array外，swap操作并不交换元素本身，只交换两个容器内部的数据结构，不会进行拷贝、添加、删除操作，速度很快
    swap(vec4[1], vec4[2]);
    printVecInt(cout, vec4) << endl;
    vec1.swap(vec4);
    printVecInt(cout, vec4) << endl;

    // 容器大小
    cout << vec4.size() << " " << vec4.max_size() << endl;

    // 相同类型的容器可以使用赋值操作，不同类型但相容的使用assign
    list<string> names;
    vector<const char*> oldstyle{"abc","ab","c"};
    // names = oldstyle; 错误
    names.assign(oldstyle.cbegin(), oldstyle.cend());
    printListString(cout, names) << endl;

    // 添加元素
    vector<int> vec{1,2,3,4};
    vec.push_back(5);
    vec.insert(vec.insert(vec.insert(vec.begin(),{0,0}),-1), vec1.begin(), vec1.end()); //返回一个迭代器指向插入的元素
    printVecInt(cout, vec) << endl;
    
    // 访问元素
    /*
    c.back()
    c.front()
    c[n]
    c.at(n) 若越界会抛出异常
    返回的都是引用
    */
    vec.front() = 111;
    // 若用auto,且需要改变元素,要显示定义为引用
    auto &v = vec.back();
    v = 999; //改变元素
    auto v2 = vec.back();
    v2 = 9999; //不改变元素
    printVecInt(cout, vec) << endl;
    try{
        vec.at(100);
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
    vec.pop_back();
    printVecInt(cout, vec) << endl;
    vec.erase(vec.begin(), vec.begin()+2);
    printVecInt(cout, vec) << endl;    
    vec.erase(--vec.end());
    printVecInt(cout, vec) << endl;
    vec.clear();
    printVecInt(cout, vec) << endl;

    // Vector对象是如何增长的
    /*
    管理容量的成员函数
    c.shrink_to_fit() 将capacity()减小为size()相同大小
    c.capacity() c可以保存多少元素
    c.reserve(n) 分配至少能容乃n个元素的内存空间
    */
    cout << vec4.size() << endl;
    cout << vec4.capacity() << endl;
    vec4.reserve(100);
    cout << vec4.capacity() << endl;
    vec4.shrink_to_fit();
    cout << vec4.capacity() << endl;
    return 0;
}


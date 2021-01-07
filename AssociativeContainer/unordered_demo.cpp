#include<iostream>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include"myprints.h"
typedef struct teleRecord
{
    size_t id;
    string name;
}TR;
size_t hasher(const TR &tr){
    //return tr.id;
    return hash<string>()(tr.name);
}
bool eqOp(const TR &tr1, const TR &tr2){
    return tr1.name==tr2.name;
}

// 有序容器使用比较运算符来组织元素，无序容器则用哈希函数和==运算符
int main(){
    // 无序元素在存储上组织为一组桶，每个桶保存零个或多个元素
    /*
    桶接口
    c.bucket_count() 正在使用的桶数
    c.max_bucket_count() 容器最多能容纳的桶数
    c.bucket_size(n) 第n个桶中有多少元素
    c.bucket(k) 关键字为k的在哪个桶中
    桶迭代
    哈希策略
    c.load_factor() 每个桶的平均元素数量
    c.max_load_factor() c试图维护的平均桶大小
    c.rehash(n) 重组元素，使得bucket_count >= n
    c.reserve(n) 重组存储，使得c可以保存n个元素且不必rehash
    */
    
    // 可自定义无序容器的相等运算符和hash值生成函数
    TR tr_test1, tr_test2, tr_test3;
    tr_test1.id = 100;
    tr_test1.name = "Wang";
    tr_test2.id = 10;
    tr_test2.name = "Wan";
    tr_test3.id = 101;
    tr_test3.name = "Wang";
    unordered_set<TR, decltype(hasher)*, decltype(eqOp)*> us1(100, &hasher, &eqOp);
    cout << us1.size() << endl;
    us1.insert(tr_test1);
    us1.insert(tr_test2);
    us1.insert(tr_test3);
    cout << us1.size() << endl;

    unordered_multiset<TR, decltype(hasher)*, decltype(eqOp)*> ums1(100, &hasher, &eqOp);
    cout << ums1.size() << endl;
    ums1.insert(tr_test1);
    ums1.insert(tr_test2);
    ums1.insert(tr_test3);
    cout << ums1.size() << endl;
    auto range_pair = ums1.equal_range(tr_test1);
    for(auto iter=range_pair.first; iter!=range_pair.second;++iter){
        cout << iter->id << " " << iter->name << endl;
    }
    
    
    return 0;
}
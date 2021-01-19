#include"myprints.h"
#include<typeinfo>
#include<utility> // pair类型定义
using namespace std;

int main(){
    // 定义与初始化
    map<string, size_t> map1;
    print(cout, map1) << endl;
    map<string, size_t> map2{{"aaa",1},{"bbb",2},{"ccc",3}};
    print(cout, map2) << endl;

    vector<int> vec{1,2,3,4,5,5,4,3,2,1};
    set<int> st1(vec.begin(), vec.end());
    multiset<int> mst1(vec.begin(), vec.end());
    print(cout, st1) << endl;
    print(cout, mst1) << endl;

    // 关键字类型，需要提供一个比较运算符来确定关键字顺序，默认用 < ,<用不了的需要自己定义
    vector<string> vecs1{"This", "is", "a", "sentence."};
    vector<string> vecs2{"This", "is", "another", "sentence,", "haha!"};
    vector<string> vecs3{"sentence,"};
    vector<string> vecs4{"a", "sentence"};
    // 声明时传入指向比较函数的指针，用decltype得到函数类型，加*表示指针
    set<vector<string>, decltype(compare)*> vsset(&compare);
    vsset.insert(vecs1);
    vsset.insert(vecs2);
    vsset.insert(vecs3);
    vsset.insert(vecs4);
    print(cout, vsset);

    // pair 类型
    /*
    pair<T1,T2> p;
    pair<T1,T2> p(v1, v2);
    pair<T1,T2> p = {v1, v2};
    make_pair(v1, v2); 返回一个用v1 v2初始化的pari,pair类型从v1和v2推断出来
    p.first
    p.second
    p1==p2 <==> p1.first==p2.first && p1.second==p2.second
    */
    auto p1 = make_pair(1, string("one"));
    cout << typeid(p1.first).name() << " " << typeid(p1.second).name() << " "<< typeid(p1).name() << endl;

    // 关联容器操作
    /*
    关联容器定义以下类型
    key_type
    mapped_type
    value_type for map--pair<const key_type, mapped_type>
    */
    
    // 解引用一个关联容器迭代器，会得到一个类型为 value_type 的引用
    // set 的迭代器是 const 的
    // insert 操作
    /*
    c.insert(v)
    c.emplace(args) // 返回一个迭代器，指向具有指定关键字的元素，以及一个指示插入是否成功的bool值
    c.insert(b, e)
    c.insert(il)
    c.insert(p, v) 类似于 c.insert(v),从p位置开始搜索新元素应该存放的位置，返回一个迭代器，指向具有给定关键字的元素
    */
    
    map<string, size_t> mp1{{"aaa",1},{"bbb",2},{"ccc",3}};
    auto ret1 = mp1.insert({"ddd",4});
    pair<map<string, size_t>::iterator, bool> ret2 = mp1.insert({"eee",5});
    cout << ret1.first->first << " " << (*ret1.first).second  << " " << ret1.second << endl;
    cout << ret2.first->first << " " << (*ret2.first).second  << " " << ret1.second << endl;

    // 删除元素
    /*
    c.erase(k) 删除关键字为k的元素
    c.erase(p) 删除p指向的原色
    c.erase(b,e) 删除b e之间的元素
    */
    mp1.erase("aaa");
    print(cout, mp1) << endl;
    mp1.erase(mp1.begin());
    print(cout, mp1) << endl;
    mp1.erase(mp1.begin(), mp1.end());
    print(cout, mp1) << endl;

    // map 的下标操作，不能对multimap进行下标操作
    /*
    一个不存在的关键字进行下标操作，会添加一个具有才关键字的元素
    c.at(k) 带参数检查
    */
    mp1 = {{"aaa",1},{"bbb",2},{"ccc",3}};
    cout << mp1["aaa"] << " " << mp1["ddd"] << endl;
    print(cout, mp1) << endl;
    try{
        cout << mp1.at("eee") << endl;
    }
    catch(exception& e){
        cout << e.what() << endl;
    }
    print(cout, mp1) << endl;

    // 访问元素，想只读的访问元素时，不应当用下标运算，因为下标运算会写入新元素；也不应当用于 const 的容器
    /*
    c.find(k) // 返回指向第一个关键字为k的迭代器，若k不在容器中，返回尾后迭代器
    c.count(k)
    c.lower_bound(k) // 返回一个迭代器，指向第一个关键字不小于k的元素，不适用于无序容器
    c.upper_bound(k) // 返回一个迭代器，指向第一个关键字大于k的元素，不适用于无序容器
    c.equal_range(k) // 返回一个pair，表示关键字等于k的元素的范围。若k不存在，两个成员均为c.end()，也可用于无序容器
    */
    const multimap<string, string> telemap{{"Wang", "1001"},
                                     {"Hu", "1241"}, 
                                     {"Liu", "4153"},
                                     {"Zhang", "asdfa"},
                                     {"Hu", "1241231"}, 
                                     {"Liu", "415s23"}, 
                                     {"Liu", "4153sad"}};
    // 目标 查找 key:Liu 的所有 value
    /*方案一：利用find()和count()，找到第一个后迭代器顺序查找*/
    size_t num_Liu = telemap.count("Liu");
    auto fst_iter = telemap.find("Liu");
    for(size_t num=0; num!=num_Liu; ++num){
        cout << fst_iter->second << " ";
        ++fst_iter;
    }
    cout << endl;
    /*方案二：利用lower_bound()和upper_bound()找到边界*/
    for(auto iter=telemap.lower_bound("Liu");iter!=telemap.upper_bound("Liu");++iter){
        cout << iter->second << " ";
    }
    cout << endl;
    /*方案三：利用equal_range()找到范围*/
    auto range_pair = telemap.equal_range("Liu");
    for(auto iter=range_pair.first;iter!=range_pair.second;++iter){
        cout << iter->second << " ";
    }
    cout << endl;


    return 0;
}

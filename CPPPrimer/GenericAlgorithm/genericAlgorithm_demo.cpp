#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<typeinfo>
// 泛型算法适用于大多数容器，通过操作容器的迭代器来完成相关操作
// 经常需要传入谓词参数，谓词是可调用的对象，返回bool类型
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
ostream &printVecString(ostream &os, const vector<string> &vec){
    if(vec.empty()){
        os << "Empty Vector.";
        return os;
    }
    for(auto item:vec)
        os << item << " ";
    return os;
}
bool isShorter(const string &str1, const string &str2){
    return str1.size() < str2.size();
}
int main(){
    // 只读算法
    /* 
    find(b,e,val)
    */
    string str("This is a test sentence.");
    auto result = find(str.cbegin(), str.cend(), 't');
    cout << typeid(result).name() << " " << *result << endl;
    /*
    accumulate(b,e,init_value)
    */
    vector<int> veci{1,2,3,4,3,2,1};
    vector<string> vecs{"This"," ","is"," ","ahahah"};
    cout << accumulate(veci.cbegin(), veci.cend(), 0) << endl;
    cout << accumulate(vecs.cbegin(), vecs.cend(), string("[START]")) << endl;

    // 写容器元素算法
    /*
    fill(b, e, val) 将b,e范围之间的元素重置为val
    fill_n(first, n, val) [first, first+n) 用 val 填充, first 开始的序列至少要包含n个元素，fill_n不会开辟新空间填充元素
    */
    fill(veci.begin(), veci.begin()+veci.size()/2, 10);
    printVecInt(cout, veci) << endl;
    fill_n(veci.begin(), 2, 100);
    printVecInt(cout, veci) << endl;

    // back_inserter 插入迭代器
    /*
    back_inserter(container)
    */
    auto it = back_inserter(veci);
    *it = 1000;
    printVecInt(cout, veci) << " " << typeid(it).name() << endl;
    *it = 1001;
    printVecInt(cout, veci) << " " << typeid(it).name() << endl;
    // 插入迭代器可以保证算法有足够元素空间来容纳输入数据，对比fill_n()的最后一个例子
    fill_n(it, 5, -1);
    printVecInt(cout, veci) << " " << typeid(it).name() << endl;

    // 其他写元素算法
    /*
    copy(b1, e1, s2) 把[b1, e1)内容拷贝到s2
    replace(b,e,oldv,newv)
    replace_copy(b,e,copy_iter,oldv,newv) 不替换原值，将调整后的序列保存在新位置(copy_iter[keyong back_inserter(vec)])
    */

    // 重排容器元素算法
    // 消除重复元素
    /*
    sort()
    unique() // unique()不能实际删除元素，因为算法使用迭代器而不能真正进行容器操作，所以会将将重复元素排在末尾，需要我们调用容器的erase()方法进行删除;使用unique前先保证序列有序
    */
    vector<string> vecs_for_unique{"the","quick","red","fox","jumps","over","the","slow","red","turtle"};
    printVecString(cout, vecs_for_unique) << endl;
    unique(vecs_for_unique.begin(), vecs_for_unique.end());
    printVecString(cout, vecs_for_unique) << endl;
    sort(vecs_for_unique.begin(), vecs_for_unique.end());
    printVecString(cout, vecs_for_unique) << endl;
    auto end_unique = unique(vecs_for_unique.begin(), vecs_for_unique.end());
    printVecString(cout, vecs_for_unique) << endl;
    vecs_for_unique.erase(end_unique, vecs_for_unique.end());
    printVecString(cout, vecs_for_unique) << endl;

    // 定制操作,向算法传递函数,参考 lambda_demo.cpp && bind_demo.cpp
    vector<string> words{"This","is","a","word","list","hahahahahah!"};
    printVecString(cout, words) << endl;
    stable_sort(words.begin(), words.end());
    printVecString(cout, words) << endl;
    stable_sort(words.begin(), words.end(), 
                [] (const string &str1, const string &str2)->bool{return str1.size()<str2.size();});
    printVecString(cout, words) << endl;
    words = {"This","is","a","word","list","hahahahahah!"};
    stable_sort(words.begin(), words.end(), isShorter);
    printVecString(cout, words) << endl;
    
    return 0;
}
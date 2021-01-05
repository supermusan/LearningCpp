#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<typeinfo>
using namespace std;
ostream &printVecString(ostream &os, const vector<string> &vec){
    if(vec.empty()){
        os << "Empty Vector.";
        return os;
    }
    for(auto item:vec)
        os << item << " ";
    return os;
}
int main(){
    // 谓词是一个可调用表达式，其返回结果是一个能用做条件的值
    // lambda是一种可调用对象，可以将其理解为一个未命名的内联函数
    /*
    [capture list] (parameter list) -> return type {function body}
    必须永远包含 捕获列表和函数体
    */
    auto f = [] {return 42;};
    cout << f() << endl;
    
    vector<string> words{"This","is","a","word","list","hahahahahah!"};
    printVecString(cout, words) << endl;
    stable_sort(words.begin(), words.end());
    printVecString(cout, words) << endl;
    stable_sort(words.begin(), words.end(), 
                [] (const string &str1, const string &str2)->bool{return str1.size()<str2.size();});
    printVecString(cout, words) << endl;
    stable_sort(words.begin(), words.end(), 
                [] (const string &str1, const string &str2)->bool{return str1.size()>str2.size();});
    printVecString(cout, words) << endl;
    
    words.clear();
    words = {"This","is","a","word","list","hahahahahah!"};
    printVecString(cout, words) << endl;
    // 使用捕获列表访问局部变量信息,用find_if找到第一个长度小于2的字符
    size_t sz = 2;
    auto it = find_if(words.begin(), words.end(), [sz](const string &str)->bool{return str.size()<sz;});
    cout << *it << " " << typeid(it).name() << endl;
    // for_each 算法，接受一个可调用对象，对范围内的每个元素调用此对象
    for_each(words.begin(), words.end(), [] (const string &str){cout<<str<<" ";});
    cout << endl;

    //lambda 捕获列表可选值捕获/引用捕获，lambda在创建时进行捕获，值捕获则捕获一个拷贝，之后更改被捕获值的原变量对捕获值不造成影响
    int val1=42, val2=42;
    auto f2 = [val1] {return val1;};
    val1 = 10;
    cout << f2() << endl;
    auto f3 = [&val2] {return val2;};
    val2 = 10;
    cout << f3() << endl;
    /*
    隐式捕获，根据表达式体内的变量确认捕获列表
    [=]()->bool{body};
    [&]()->bool{body};
    = 值捕获; & 引用捕获
    */

    // 可变lambda,加上mutable，可以改变一个被捕获的变量的值
    size_t v1=42;
    auto f11 = [v1] () mutable {return ++v1;};
    v1 = 0;
    cout << f11() << " " << v1 <<endl;
    
    size_t v2=42;
    auto f22 = [&v2] {return ++v2;};
    v2 = 0;
    cout << f22() << " " << v2 <<endl; 
    
    return 0;
}
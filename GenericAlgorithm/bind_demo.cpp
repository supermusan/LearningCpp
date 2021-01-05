#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<typeinfo>
#include<functional> // bind()的头文件
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
bool check_size(const string &str, size_t _sz){
    return str.size() < _sz;
}
int main(){
    // 如果lambda的捕获列表为空，可直接用函数代替他。若多次作为谓词使用，函数会更好
    // 用 bind 函数可以解决传参额外问题
    /*
    auto newCallable = bind(callable, arg_list)
    调用 newCallable 时,newCallable会调用callable,并传给他arg_list中的参数
    */
    vector<string> words = {"This","is","a","word","list","hahahahahah!"};
    printVecString(cout, words) << endl;
    // 使用捕获列表访问局部变量信息,用find_if找到第一个长度小于2的字符
    size_t sz = 2;
    // lambda 形式
    auto it = find_if(words.begin(), words.end(), [sz](const string &str)->bool{return str.size()<sz;});
    cout << *it << " " << typeid(it).name() << endl;
    //auto check2 = bind(check_size, _1, sz);
    using namespace std::placeholders; //std::placeholders::_1占位符
    auto it2 = find_if(words.begin(), words.end(), bind(check_size, _1, sz));
    cout << *it2 << " " << typeid(it2).name() << endl;
    /*
    默认情况下，bind()的非占位符是拷贝，若不想拷贝需要调用 ref()函数，例如 ref(cout) [cout 不能拷贝]，在头文件 functional 中
    */

    return 0;
}
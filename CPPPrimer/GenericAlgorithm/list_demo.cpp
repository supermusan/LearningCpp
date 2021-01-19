#include<list>
#include<iostream>
#include<string>
#include<algorithm>
#include<typeinfo>
using namespace std;
ostream &printListString(ostream &os, const list<string> &li){
    if(li.empty())
        os << "Empty List.";
    for(auto item:li)
        os << item << " ";
    return os;
}
int main(){
    // list,forward_list不能随机访问，而sort等一些算法需要随机访问迭代器，所以要用list forward_list 独有的成员函数算法
    /*
    lst.merge(lst2)
    lst.merge(lst2, comp) // lst lst2 必须有序,默认使用<作为比较运算符
    lst.remove(val)
    lst.remove_if(pred) // 调用 erase 删除 ==val 的元素 或使得一元谓词为真的元素
    lst.reverse() // 反转
    lst.sort()
    lst.sort(comp)
    lst.unique()
    lst.unique(pred)
    */
    list<string> lst1{"this","is","a","test","sentence","hahahaha!"};
    list<string> lst2{"hahahaha!","xixi"};
    lst1.sort();
    printListString(cout, lst1) << endl;
    lst2.sort();
    printListString(cout, lst2) << endl;
    lst1.merge(lst2);
    printListString(cout, lst1) << endl;
    printListString(cout, lst2) << endl;

    lst1 = {"this","is","a","test","sentence","hahahaha!"};
    lst2 = {"hahahaha!","xixi"};
    lst1.sort([] (const string &str1, const string &str2) {return str1.size()<str2.size();});
    printListString(cout, lst1) << endl;
    lst2.sort([] (const string &str1, const string &str2) {return str1.size()<str2.size();});
    printListString(cout, lst2) << endl;
    lst1.merge(lst2,[] (const string &str1, const string &str2) {return str1.size()<str2.size();});
    list<string> lst3 = lst1;
    printListString(cout, lst1) << endl;
    printListString(cout, lst2) << endl;

    lst1.remove(string("a"));
    printListString(cout, lst1) << endl;
    char del_c1 = 'h', del_c2 = 'x';
    // string.find() 若未找到 返回 string::npos
    lst1.remove_if([del_c1] (const string &str)->bool {return str.find(del_c1)!=string::npos;});
    printListString(cout, lst1) << endl;
    lst1.remove_if([del_c2] (const string &str)->bool {return (find(str.begin(), str.end(), del_c2))!=str.end();});
    printListString(cout, lst1) << endl;

    printListString(cout, lst3) << endl;
    lst3.unique();
    printListString(cout, lst3) << endl;
    lst3.unique([](const string &str1, const string &str2) {return str1.size()==str2.size();});
    printListString(cout, lst3) << endl;

    // splice
    /*
    list: lst.splice()
    forward_list: flst.splice_after()
    */
    lst1 = {"this","is","a","test","sentence","hahahaha!"};
    lst2 = {"hahahaha!","xixi"};
    lst1.splice(++lst1.begin(), lst2);
    printListString(cout, lst1) << endl;
    printListString(cout, lst2) << endl;

    lst1 = {"this","is","a","test","sentence","hahahaha!"};
    lst2 = {"hahahaha!","xixi"};
    lst1.splice(++lst1.begin(), lst2, ++lst2.begin());
    printListString(cout, lst1) << endl;
    printListString(cout, lst2) << endl;

    lst1 = {"this","is","a","test","sentence","hahahaha!"};
    lst2 = {"hahahaha!","xixi"};
    lst1.splice(++lst1.begin(), lst2, lst2.begin(), ++lst2.begin());
    printListString(cout, lst1) << endl;
    printListString(cout, lst2) << endl;

    return 0;
}
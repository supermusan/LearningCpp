#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
using namespace std;
ostream &print(ostream &os, const map<string, size_t> &mp){
    if(mp.empty()){
        os << "Empty Map.";
        return os;
    }
    for(auto item:mp)
        os << item.first << "#" << item.second << " ";
    return os;
}
ostream &print(ostream &os, const map<string, string> &mp){
    if(mp.empty()){
        os << "Empty Map.";
        return os;
    }
    for(auto item:mp)
        os << item.first << "#" << item.second << " ";
    return os;
}
ostream &print(ostream &os, const set<int> &st){
    if(st.empty()){
        os << "Empty Sep.";
        return os;
    }
    for(auto item:st)
        os << item << " ";
    return os;
}
ostream &print(ostream &os, const multiset<int> &st){
    if(st.empty()){
        os << "Empty Sep.";
        return os;
    }
    for(auto item:st)
        os << item << " ";
    return os;
}
ostream &print(ostream &os, const vector<string> &li){
    for(auto item:li)
        os << item << " ";
    return os;
}
bool compare(const vector<string> &vs1, const vector<string> &vs2){
    return vs1.size() < vs2.size();
}
ostream &print(ostream &os, const set<vector<string>, decltype(compare)*> &st){
    if(st.empty()){
        os << "Empty Sep.";
        return os;
    }
    for(auto item:st)
        print(os, item) << endl;
    return os;
}
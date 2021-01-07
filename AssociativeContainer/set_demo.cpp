#include<iostream>
#include<set>
#include<vector>
#include<string>
using namespace std;
ostream &printSetInt(ostream &os, const set<int> &st){
    if(st.empty()){
        os << "Empty Map.";
        return os;
    }
    for(auto item:st)
        os << item << " ";
    return os;
}
ostream &printSetInt(ostream &os, const multiset<int> &st){
    if(st.empty()){
        os << "Empty Map.";
        return os;
    }
    for(auto item:st)
        os << item << " ";
    return os;
}
int main(){
    vector<int> vec{1,2,3,4,5,5,4,3,2,1};
    set<int> st1(vec.begin(), vec.end());
    multiset<int> mst1(vec.begin(), vec.end());
    printSetInt(cout, st1) << endl;
    printSetInt(cout, mst1) << endl;

    return 0;
}

#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include"myprints.h"
using namespace std;
/*
给定一个strng，转换为另一个string。转换规则保存在rules.txt中，words.txt保存待转换的单词，转换结果输出到results.txt中
*/
map<string, string> getDict(istream &is){
    map<string, string> dict;
    //string str;
    string key;
    string value;
    //size_t pos;
    while(is>>key && getline(is, value)){
        dict[key] = value.substr(1); //跳过先导空格
    }
    /*
    while(getline(is, str))
    {
        pos = str.find(" ");
        dict[str.substr(0, pos)] = str.substr(pos+1);
    }
    */
    return dict;
}
string transform(const string &_word, const map<string, string> &rule){
    string res_word;
    auto it =  rule.find(_word);
    res_word = it!=rule.end()? it->second : _word;
    return res_word;
}
void word_transform(istream &input, ostream & output, const map<string, string> &rule){
    string line;
    while (getline(input, line))
    {
        istringstream instring(line);
        string word;
        while(instring >> word){
            output << transform(word, rule) << " ";
        }
        output << endl;
    }
}
int main(){
    ifstream wordsf("words.txt");
    ifstream rulesf("rules.txt");
    ofstream resultf("result.txt");
    const map<string, string> map_dict = getDict(rulesf);
    print(cout, map_dict) << endl;
    word_transform(wordsf, resultf, map_dict);


    return 0;
}
#include<iostream>
#include"TextQuery.h"
/*
允许用户在一个给定文件中查询单词，查询结果是单词在文件中出现的次数及其所在行的列表，行会按照升序输出
*/

int main(int argc, char* argv[]){
    if(argc<2){
        cout << "Enter filename please." << endl;
        return 0;
    }
    const string filename(argv[1]);
    runQueries(filename);
    return 0 ;
}
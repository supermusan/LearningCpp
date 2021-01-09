#include<vector>
#include<string>
#include<map>
#include<set>
#include<memory>
#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
class QueryResult;
class TextQuery{
    public:
        TextQuery(const string &);
        QueryResult query(const string &) const;
    private:
        shared_ptr<vector<string>> file;
        map<string, shared_ptr<set<size_t>>> wm; 
};

class QueryResult{
    friend QueryResult TextQuery::query(const string &word) const;
    public:
        QueryResult();
        void print() const;
    private:
        shared_ptr<set<size_t>> res_lino;
        shared_ptr<vector<string>> file;
};

TextQuery::TextQuery(const string &filename): file(new vector<string>){
    cout << "Reading file: " << filename << endl;
    ifstream input(filename);
    string templine;
    size_t line_id = 0;
    while(getline(input, templine))
    {
        file->push_back(templine);
        istringstream iss(templine);
        string word;
        while(iss >> word){
            auto &setptr = wm[word];
            if(!setptr)
                setptr = make_shared<set<size_t>>();
            setptr->insert(line_id);
        }
        ++line_id;
    }
    cout << "Read successfully: " << filename << endl;
}

QueryResult TextQuery::query(const string &word) const{
    cout << "searching '"  << word << "'..." << endl;
    QueryResult result;
    auto find_iter = wm.find(word);
    result.file = file;
    if(find_iter!=wm.end()){
        result.res_lino = find_iter->second;
    }
    cout << "search '"  << word << "' successfully." << endl;
    return result;
}

QueryResult::QueryResult(): res_lino(make_shared<set<size_t>>()), file(new vector<string>){}

void QueryResult::print() const{
    cout << "element occurs " << res_lino->size() << " times" << endl;
    for(auto line_no:*res_lino){
        cout << "\t(line" << " " << line_no+1 << ") " << file->at(line_no) << endl;
    }
    cout << endl;
}

void runQueries(const string &filename){
    TextQuery tq(filename);
    while(true){
        cout << "enter word to look for, or q to quit: ";
        string s;
        if(!(cin >>s) || s=="q") break;
        tq.query(s).print();
    }
}
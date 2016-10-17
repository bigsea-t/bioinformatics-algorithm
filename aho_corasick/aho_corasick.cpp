/*
 *
 * Copyright(c) 2016 Taikai Takeda <297.1951@gmail.com> All rights reserved.
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class TNode {
public:
    char c;
    vector<TNode> cnodes;
    bool isEnd;


    TNode(char _c) : c(_c), cnodes(), isEnd(false) {};
    void addWord(const string & s);
    vector<string> get_all_string();
private:
    vector<TNode>::iterator find_child(char c);
};

vector<TNode>::iterator TNode::find_child(char c){
    auto cmp = [c](const TNode & n){return c == n.c;};
    return find_if(cnodes.begin(), cnodes.end(), cmp);
}

void TNode::addWord(const string & s){
    if (s.size() == 0){
        isEnd = true;
        return;
    }

    auto cnode = find_child(s[0]);

    if (cnode == cnodes.end()){
        cnodes.emplace_back(s[0]);
        cnode = cnodes.end() - 1 ;
    }

    cnode->addWord(s.substr(1, s.size()-1));
}

vector<string> TNode::get_all_string(){
    vector<string> vs;

    if (cnodes.size() == 0){
        vs.push_back("");
        return vs;
    }

    for (auto & n: cnodes){
        auto vs_child = n.get_all_string();
        for(auto & s_child: vs_child){
            string s(1, n.c);
            s += s_child;
            vs.push_back(s);
        }
        if (isEnd){
            string s = "";
            vs.push_back(s);
        }
    }

    return vs;
}


int main()
{
    int n_keys;
    cin >> n_keys;
    string text;
    vector<string>  keys(n_keys);

    cin >> text;

    for (int i = 0; i < n_keys; i++) {
        cin >> keys[i];
    }

    cout << text << endl;

    for (auto & s: keys) {
        cout << s << endl;
    }

    TNode root('\0');

    for (auto & s: keys){
        root.addWord(s);
    }

    cout << "== trie ==" << endl;

    vector<string> trie_keys = root.get_all_string();

    for (auto & s: trie_keys){
        cout << s << endl;
    }


    return 0;
}

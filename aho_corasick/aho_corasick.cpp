/*
 *
 * Copyright(c) 2016 Taikai Takeda <297.1951@gmail.com> All rights reserved.
 *
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

class TNode {
public:
    TNode(char _c) : c(_c), cnodes(), isEnd(false) ,depth(0) {};
    TNode(char _c, int _d) : c(_c), cnodes(), isEnd(false) ,depth(_d) {};
    void addWord(const string & s);
    vector<string> get_all_string();
    void make_fail_func();
    vector<pair<int, int> > exact_match(const string & text);

private:
    char c;
    vector<TNode> cnodes; // it would be better to hold pointers to TNode
    int depth; // zero at root
    bool isEnd;
    TNode * fail;

    TNode * find_child(char c);
};

TNode * TNode::find_child(char c){
    auto cmp = [c](const TNode & n){return c == n.c;};
    auto itr = find_if(cnodes.begin(), cnodes.end(), cmp);
    if (itr == cnodes.end())
        return NULL;
    else
        return &*itr;
}

void TNode::addWord(const string & s){
    if (s.size() == 0){
        isEnd = true;
        return;
    }

    auto cnode = find_child(s[0]);

    if (cnode == NULL){
        cnodes.emplace_back(s[0], this->depth+1);
        cnode = &(cnodes[cnodes.size() - 1]);
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

void TNode::make_fail_func(){
    TNode * root = this;

    root->fail = root;

    queue<TNode *> q;
    for (auto &u : root->cnodes){
        u.fail = root;
        q.push(&u);
    }

    while(! q.empty()){
        TNode * v = q.front(); q.pop();

        for (auto & u: v->cnodes){
            q.push(&u);

            TNode *s = v->fail;
            TNode *g;

            while(true){
                g = s->find_child(u.c);

                if(g != NULL || s == root)
                    break;

                s = s->fail;
            }

            if (g == NULL)
                u.fail = root;
            else
                u.fail = g;
        }
    }
}

vector<pair<int, int> > TNode::exact_match(const string & text)
{
    vector<pair<int, int> > ranges;
    TNode * pa = this, * root = this;

    for (int i = 0; i < text.size(); i++) {
        while(true){
            TNode * ch = pa->find_child(text[i]);

            if (ch == NULL){
                pa = pa->fail;
                if (pa == root)
                    break;
            } else {
                pa = ch;
                break;
            }
        }
        TNode * n = pa;
        while(n != root){
            if (n->isEnd) {
                ranges.emplace_back(i-n->depth+1, i+1);
            }
            n = n->fail;
        }
    }
    return ranges;
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

    TNode root('\0');

    for (auto & s: keys){
        root.addWord(s);
    }

    root.make_fail_func();

    auto ranges = root.exact_match(text);

    sort(ranges.begin(), ranges.end());

    for (auto r: ranges){
        cout << r.first << " " << r.second << endl;
    }

    return 0;
}

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

class SuffixArray {
public:
    SuffixArray(const string & text) : text(text), sa(text.size() + 1){
        build();
    };
    vector<pair<int, int> > exact_match(const string & pat);
private:
    void build();
    string text;
    vector<int> sa;
};

void SuffixArray::build() {
    int N = text.size();
    vector<int> rank(N+1);
    vector<int> tmp(N+1);

    for (int i = 0; i <= N; i++) {
        sa[i] = i;
    }

    // initial rank is char code
    for (int i = 0; i < N; i++)
        rank[i] = text[i];

    // -1 represents rank of empty string
    rank[N] = -1;

    for (int k = 1; k <= N; k*=2) {
        auto cmp = [rank, k, N](int i, int j){
            if(rank[i] != rank[j])
                return rank[i] < rank[j];
            else {
                auto cal_rank = [=](int a){ return a+k <= N ? rank[a+k] : -1; };
                return cal_rank(i) < cal_rank(j);
            }
        };

        sort(sa.begin(), sa.end(), cmp);

        for (int i = 0; i <= N; i++)
            tmp[sa[i]] = tmp[sa[i-1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        rank = tmp;
    }

}

vector<pair<int, int> > SuffixArray::exact_match(const string & pat) {
    int lo = 0, hi = text.size();

    while ((hi - lo) > 1) {
        int md = (lo + hi)  /2;

        if (text.compare(sa[md], pat.size(), pat) < 0)
            lo = md;
        else
            hi = md;
    }

    int s = hi;
    vector<pair<int, int> > ranges;

    while(text.compare(sa[s], pat.size(), pat) ==  0){
        ranges.emplace_back(sa[s], sa[s] + pat.size());
        s++;
    }

    return ranges;
}

int main() {
    string text;
    string pat;

    cin >> text;
    cin >> pat;

    auto sa = SuffixArray(text);

    auto ranges = sa.exact_match(pat);
    sort(ranges.begin(), ranges.end());

    if (ranges.size() == 0)
        cout << "NULL" << endl;
    else {
        for (auto r: ranges){
            cout << r.first << " " << r.second << endl;
        }
    }

    return 0;
}

/*
 *
 * Copyright(c) 2016 Taikai Takeda <297.1951@gmail.com> All rights reserved.
 *
 */

#include <iostream>
#include <vector>
using namespace std;

vector<int> calculate_h(const vector<char> & pat)
{
    vector<int> h(pat.size(), -1);

    int i = -1;
    int j = 0;

    while (j < pat.size() - 1) {
        while (i >= 0 && pat[i] != pat[j])
            i = h[i];
        i++, j++;
        if (pat[i] == pat[j])
            h[j] = h[i];
        else
            h[j] = i;
    }
    return h;
}

vector<pair<int, int> > kmp(const vector<char> & text, const vector<char> & pat)
{

    vector<pair<int, int> > ranges;

    vector<int> h = calculate_h(pat);

    int i = 0, j = 0;

    while(i < pat.size() && j < text.size()){
        while(i >= 0 && pat[i] != text[j])
            i = h[i];

        i++, j++;
        if(i >= pat.size()){
            ranges.emplace_back(j - pat.size(), j);
            i = 0;
        }

    }

    return ranges;
}

int main()
{
    // n, m
    int len_text, len_pat;

    cin >> len_text >> len_pat;

    // t, p
    vector<char> text(len_text), pat(len_pat);

    for (int i = 0; i < len_text; i++) {
        cin >> text[i];
    }

    for (int i = 0; i < len_pat; i++) {
        cin >> pat[i];
    }

    vector<pair<int, int> > ranges = kmp(text, pat);

    for (auto r : ranges){
        cout << r.first << ' ' << r.second << endl;
    }


    return 0;
}

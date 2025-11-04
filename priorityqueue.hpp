#pragma once
#include <vector>
#include <string>

class PriorityQueue {
    private:

    vector<pair<int,string>> arr;

    int size() const { return (int)arr.size() - 1; }
    bool empty() const { return size() == 0; }

    void up(int idx) {
        while (idx > 1) {
            int par = idx / 2;
            if (arr[idx].first > arr[par].first || (arr[idx].first == arr[par].first && arr[idx].second < arr[par].second)) {
                swap(arr[idx], arr[par]);
                idx = par;
            }
            else break;
        }
    }

    void down(int idx) {
        int n = size();
        while (true) {
            int l = idx * 2, r = l + 1;
            if (l > n) break;
            int best = l;
            if (r <= n && (arr[r].first > arr[l].first || (arr[r].first == arr[l].first && arr[r].second < arr[l].second))) best = r;
            if (arr[best].first > arr[idx].first || (arr[best].first == arr[idx].first && arr[best].second < arr[idx].second)) {
                swap(arr[best], arr[idx]);
                idx = best;
            } 
            else break;
        }
    }

    void push(const pair<int,string> &p) { 
        arr.push_back(p);
        up(size());
    }

    pair<int,string> pop() {
        int n = size();
        pair<int,string> removed = arr[1];
        if (n == 1) {
            arr.pop_back();
            return removed;
        }
        arr[1] = arr.back();
        arr.pop_back();
        down(1);
        return removed;
    }

    public:
    PriorityQueue() { arr.push_back({0, ""}); }
    
    vector<pair<int,string>> heapsort(const vector<pair<int,string>> &vec) {
        vector<pair<int,string>> result;
        for (const auto &p : vec) push(p);
        while (!empty()) result.push_back(pop());
        return result;
    }
};
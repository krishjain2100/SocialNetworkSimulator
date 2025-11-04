#include "utils.hpp"
#include <algorithm>

using namespace std;

int global_time = 0;

vector<string> split(const string& s) {
    vector<string> parts;
    size_t first_space = s.find(' ');
    if (first_space == string::npos) { parts.push_back(s); return parts; }
    parts.push_back(s.substr(0, first_space));
    size_t second_space = s.find(' ', first_space + 1);
    if (second_space == string::npos) { 
        parts.push_back(s.substr(first_space + 1)); 
        return parts;
    }
    parts.push_back(s.substr(first_space + 1, second_space - (first_space + 1)));
    parts.push_back(s.substr(second_space + 1));
    return parts;
}

string to_lowercase(string s) {
    transform(s.begin(), s.end(), s.begin(), [](char c) { return tolower(c); });
    return s;
}

int time_now() {
    return global_time++;
}

bool tie_breaker(const pair<int,string> &a, const pair<int,string> &b){
    if(a.first != b.first) return a.first > b.first; 
    return a.second < b.second;
}
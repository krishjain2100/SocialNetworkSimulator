#pragma once
#include <string>
#include <vector>
#include <ctime>
using namespace std;

vector<string> split(const string& s);
string to_lowercase(string s);
std::time_t time_now();
bool tie_breaker(const pair<int,string> &a, const pair<int,string> &b);
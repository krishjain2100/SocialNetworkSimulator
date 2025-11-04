#pragma once
#include <string>
#include <vector>
using namespace std;

vector<string> split(const string& s);
string to_lowercase(string s);
int time_now();
bool tie_breaker(const pair<int,string> &a, const pair<int,string> &b);
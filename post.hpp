#pragma once
#include <string>
#include <vector>
#include <ctime>
using namespace std;
struct Post {
    string content;
    time_t time;
    Post* left;
    Post* right;
    int height;
    Post(const string& s, time_t t);
};

struct PostsAVL {
    Post* root;
    int count;

    PostsAVL();
    
    Post* insertHelper(const string& content, time_t time, Post* node);
    void insert(const string& content, time_t time);
    void inorder(int N, vector <string> &user_posts) const;
};
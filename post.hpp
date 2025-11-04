#pragma once
#include <string>
#include <vector>
using namespace std;

struct Post {
    string content;
    int time;
    Post* left;
    Post* right;
    int height;
    Post(const string& s, int t);
};

struct PostsAVL {
    Post* root;
    int count;

    PostsAVL();

    Post* insertHelper(const string& content, int time, Post* node);
    void insert(const string& content, int time);
    void inorder(int N, vector <string> &user_posts) const;
};
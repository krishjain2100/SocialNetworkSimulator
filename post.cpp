#include "post.hpp"
#include "avl_utils.hpp"
#include <stack>
#include <algorithm>
using namespace std;

Post::Post(const string& s, int t) {
    content = s;
    time = t;
    left = right = nullptr;
    height = 1;
}

PostsAVL::PostsAVL() { 
    root = nullptr; 
    count = 0; 
}

Post* PostsAVL::insertHelper(const string& content, int time, Post* node) {
    if(!node) { count++; return new Post(content, time); }
    if(time > node->time) node->left = insertHelper(content, time, node->left);
    else  node->right = insertHelper(content, time, node->right);
    return balance(node);
}

void PostsAVL::insert(const string& content, int time) { 
    root = insertHelper(content, time, root);
}

void PostsAVL::inorder(int N, vector <string> &user_posts) const {
    int req = N;
    if(req == -1) req = count;
    req = min(req, count);
    stack<Post*> st;
    Post* cur = root;
    if (req <= 0) return;
    while ((cur != nullptr || !st.empty()) && req > 0) {
        while (cur != nullptr) { st.push(cur); cur = cur->left;}
        cur = st.top(); 
        st.pop();
        user_posts.push_back(cur->content);
        req--;
        cur = cur->right;
    }
}
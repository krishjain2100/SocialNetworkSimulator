#pragma once
#include <algorithm>
using namespace std;

template <typename T> 
int height(T* node) {
    if(!node) return 0;
    return node->height;
} 

template <typename T>  
int getBalance(T* node) {
    if (!node) return 0;
    return height<T>(node->left) - height<T>(node->right);
}

template <typename T> 
T* rightrotate(T* u) {
    T* x = u->left;
    T* y = x->right;
    x->right = u;
    u->left = y;
    u->height = max(height<T>(u->left), height<T>(u->right))+1;
    x->height = max(height<T>(x->left), height<T>(x->right))+1;
    return x;
}

template <typename T> 
T* leftrotate(T* u) {
    T* x = u->right;
    T* y = x->left;
    x->left = u;
    u->right = y;
    u->height = max(height<T>(u->left), height<T>(u->right))+1;
    x->height = max(height<T>(x->left), height<T>(x->right))+1;
    return x;
}

template <typename T> 
T* balance(T* node) {
    if(!node) return nullptr;
    node->height = max(height(node->left), height(node->right))+1;
    int balance = getBalance<T>(node);
    if(balance > 1 && getBalance<T>(node->left) >= 0) return rightrotate<T>(node);
    else if (balance < -1 && getBalance<T>(node->right) <=0) return leftrotate<T>(node);
    else if (balance > 1 && getBalance<T>(node->left) < 0) { node->left = leftrotate<T>(node->left); return rightrotate<T>(node); }
    else if (balance < -1 && getBalance<T>(node->right) > 0) { node->right = rightrotate<T>(node->right); return leftrotate<T>(node); }
    return node;
}
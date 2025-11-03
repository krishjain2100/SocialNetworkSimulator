#pragma once
#include <string>
#include "post.hpp" 
using namespace std;

struct FriendsAVL;

struct User {
    string name;
    PostsAVL posts;
    FriendsAVL* friends;   
    User (const string& s);
    ~User(); 
};
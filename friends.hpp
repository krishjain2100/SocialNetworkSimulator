#pragma once
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include "user.hpp" 
using namespace std; 
struct FriendsAVL {
    struct FriendNode {
        User* user; 
        FriendNode* left;
        FriendNode* right;
        int height;
        FriendNode(User* u);
    };

    FriendNode* root;
    FriendsAVL();

    FriendNode* insertHelper(User* u, FriendNode* node, bool &success);
    bool insert(User* u);
    void inorder(FriendNode* node, vector <string> &friends) const;
    void fillfriends(vector <string> &friends) const;
    void filldist1(unordered_map<User*,int> &dist1, FriendNode* node);
    void filldist2(unordered_map<User*,int> &dist2, FriendNode* node);
    bool fillq(queue<User*> &q, unordered_map<User*,int> &mp, int d, FriendNode* node, User* target);
};
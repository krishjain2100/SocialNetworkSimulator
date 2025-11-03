#include "friends.hpp"
#include "avl_utils.hpp"
using namespace std;

FriendsAVL::FriendNode::FriendNode(User* u){
    user = u;
    height = 1;
    left = right = nullptr;
}

FriendsAVL::FriendsAVL() {  root = nullptr; }
 
FriendsAVL::FriendNode* FriendsAVL::insertHelper(User* u, FriendNode* node, bool &success) {
    if(!node) { success = true; return new FriendNode(u); }
    if(u->name < node->user->name) node->left = insertHelper(u, node->left, success);
    else if (u->name > node->user->name) node->right = insertHelper(u, node->right, success);
    else return node; 
    return balance(node);
}

bool FriendsAVL::insert(User* u) {
    bool success = false;
    root = insertHelper(u, root, success); 
    return success;
}

void FriendsAVL::inorder(FriendNode* node, vector <string> &friends) const {
    if(!node) return;
    inorder(node->left, friends);
    friends.push_back(node->user->name);
    inorder(node->right, friends);
}

void FriendsAVL::fillfriends(vector <string> &friends) const { 
    inorder(root, friends); 
}

void FriendsAVL::filldist1(unordered_map<User*,int> &dist1, FriendNode* node) {
    if(!node) return;
    dist1[node->user] = 1;
    filldist1(dist1, node->left);
    filldist1(dist1, node->right);
}

void FriendsAVL::filldist2(unordered_map<User*,int> &dist2, FriendNode* node) {
    if(!node) return;
    dist2[node->user]++;
    filldist2(dist2, node->left);
    filldist2(dist2, node->right);
}

bool FriendsAVL::fillq(queue<User*> &q, unordered_map<User*,int> &mp, int d, FriendNode* node, User* target) {
    if(!node) return false;
    if(mp.find(node->user) == mp.end()) {
        mp[node->user] = d + 1;
        if(node->user == target) return true; 
        q.push(node->user);
    }
    if(fillq(q, mp, d, node->left, target)) return true;
    return fillq(q, mp, d, node->right, target);
}
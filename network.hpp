#pragma once
#include <string>
#include <unordered_map>
#include "user.hpp"
using namespace std;

class Network {
private:
    unordered_map<string, User*> node_map;

public:
    Network();
    ~Network(); 
    void AddUser(const string& username);
    void AddFriend(const string& user1, const string& user2);
    void ListFriends(const string& username) const;
    void SuggestFriends(const string& username, int N);
    void DegreesOfSeparation(const string& user1, const string& user2);
    void AddPost(const string& username, const string& content);
    void OutputPosts(const string& username, int N) const;

    bool interface();
};
#include "network.hpp"
#include "friends.hpp" 
#include "utils.hpp"
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>

using namespace std; 

Network::Network() {}

Network::~Network() {
    for(auto &pair : node_map) { delete pair.second; }
}

void Network::AddUser(const string& username) {
    string safe_username = to_lowercase(username);
    if(node_map.find(safe_username) != node_map.end()) {
        cout << "Error: " << safe_username << " already exists" << endl;
        return;
    }
    User* newUser = new User(safe_username);
    node_map[safe_username] = newUser;
    cout << "Added User " << safe_username << endl;
}

void Network::AddFriend(const string& user1, const string& user2) {
    string safe_user1 = to_lowercase(user1);
    string safe_user2 = to_lowercase(user2);
    if(node_map.find(safe_user1) == node_map.end() || node_map.find(safe_user2) == node_map.end()) {
        cout << "Error: Atleast one of the users does not exist on this network" << endl;
        return;
    }
    User* node1 = node_map[safe_user1];
    User* node2 = node_map[safe_user2];
    if(node1 == node2) { cout << "Error: Cannot friend self" << endl; return; }
    
    if(node1->friends->insert(node2)) {
        cout << "Friendship added between " << safe_user1 << " and " << safe_user2 << endl;
        node2->friends->insert(node1); 
    }
    else cout << "Error: " << safe_user1 << " and " << safe_user2 << " are already friends" << endl;
}

void Network::ListFriends(const string& username) const {
    string safe_username = to_lowercase(username);
    if(node_map.find(safe_username) == node_map.end()) { 
        cout << "Error: " << safe_username << " does not exist on this network" << endl; 
        return; 
    }
    vector <string> friends;
    node_map.at(safe_username)->friends->fillfriends(friends);
    if(friends.empty()) { 
        cout << safe_username << " has no friends" << endl; 
        return;
    }
    cout << "Friends of " << safe_username << ":" << endl;
    for(auto &f : friends) cout << f << endl;
}

void Network::SuggestFriends(const string& username, int N) {
    if(N <= 0) { cout << "Error: Please enter a valid number" << endl; return; }
    string safe_username = to_lowercase(username);
    if(node_map.find(safe_username) == node_map.end()) { 
        cout << "Error: " << safe_username << " does not exist on this network" << endl; 
        return; 
    }
    User* node = node_map[safe_username];
    unordered_map<User*,int> dist1, dist2;
    node->friends->filldist1(dist1, node->friends->root);
    for(auto &p : dist1) {
        User* friendUser = p.first;
        friendUser->friends->filldist2(dist2, friendUser->friends->root);
    }
    dist2.erase(node);
    for(auto &p : dist1) dist2.erase(p.first);
    vector<pair<int,string>> v;
    for(auto &p : dist2) v.push_back({p.second, p.first->name});
    sort(v.begin(), v.end(), tie_breaker);
    if(v.empty()) { cout << "No friend suggestions available" << endl; return; }
    cout << "Top " << min((int)v.size(), N) << " recommended friends for " << safe_username << ":" << endl;
    for(int i=0; i < (int)v.size() && i < N; i++) {
        cout << v[i].second << " (" << v[i].first << (v[i].first > 1 ? " mutuals)" : " mutual)")<< endl;
    }
}

void Network::DegreesOfSeparation(const string& user1, const string& user2) {
    string safe_user1 = to_lowercase(user1);
    string safe_user2 = to_lowercase(user2);
    if(node_map.find(safe_user1) == node_map.end() or node_map.find(safe_user2) == node_map.end()) { 
        cout << "Error: Atleast one of the users does not exist on this network" << endl; 
        return; 
    }
    User* node1 = node_map[safe_user1];
    User* node2 = node_map[safe_user2];
    if(node1 == node2) { 
        cout << "Distance between " << safe_user1 << " and " << safe_user2 << " is 0" << endl; 
        return; 
    }
    unordered_map<User*, int> mp; 
    queue<User*> q;
    mp[node1] = 0;
    q.push(node1);
    bool found = false;
    while(!q.empty() && !found) {
        User* cur = q.front(); 
        q.pop();
        found = cur->friends->fillq(q, mp, mp[cur], cur->friends->root, node2);
    }
    cout << "Distance between " << safe_user1 << " and " << safe_user2 << " is ";
    if(mp.find(node2) == mp.end()) cout << -1 << endl;
    else cout << mp[node2] << endl;
}

void Network::AddPost(const string& username, const string& content) {
    string safe_username = to_lowercase(username);
    if(node_map.find(safe_username) == node_map.end()) { 
        cout << "Error: " << safe_username << " does not exist on this network" << endl; 
        return; 
    }
    node_map[safe_username]->posts.insert(content, time_now());
    cout << "Post added for " << safe_username << endl;
}

void Network::OutputPosts(const string& username, int N) const {
    if(N <= 0 and N != -1) { cout << "Error: Please enter a valid number" << endl; return; }
    string safe_username = to_lowercase(username);
    if(node_map.find(safe_username) == node_map.end()) {
        cout << "Error: " << safe_username << " does not exist on this network" << endl;
        return;
    }
    vector <string> user_posts;
    node_map.at(safe_username)->posts.inorder(N, user_posts); 
    if(user_posts.empty()) { 
        cout << safe_username << " has no posts" << endl; 
        return;
    }
    cout << "Showing " << user_posts.size() << " posts for " << safe_username << ":" << endl;
    for(auto &p : user_posts) cout << p << endl;
}

bool Network::interface() {
    string input_line;
    cout << "> ";
    if(!getline(cin, input_line)) return false;
    if (input_line == "END") return false;
    if (input_line.empty()) return true;
    vector<string> input_split = split(input_line);
    if (input_split.empty()) return true;
    string command = input_split[0];
    try {
        if (command == "ADD_USER" && input_split.size() > 1) AddUser(input_split[1]);
        else if (command == "ADD_FRIEND" && input_split.size() > 2) AddFriend(input_split[1], input_split[2]);
        else if (command == "LIST_FRIENDS" && input_split.size() > 1) ListFriends(input_split[1]);
        else if (command == "SUGGEST_FRIENDS" && input_split.size() > 2) SuggestFriends(input_split[1], stoi(input_split[2]));
        else if (command == "DEGREES_OF_SEPARATION" && input_split.size() > 2) DegreesOfSeparation(input_split[1], input_split[2]);
        else if (command == "ADD_POST" && input_split.size() > 2) AddPost(input_split[1], input_split[2]);
        else if (command == "OUTPUT_POSTS" && input_split.size() > 2) OutputPosts(input_split[1], stoi(input_split[2]));
        else cout << "Error: Invalid command or insufficient arguments." << endl;
    }
    catch (invalid_argument& e) { cout << "Error: Please enter a valid number" << endl; }
    catch (exception& e) { cout << "Error processing command: " << e.what() << endl; }
    return true;
}
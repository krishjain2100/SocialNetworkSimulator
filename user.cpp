#include "user.hpp"
#include "friends.hpp" 
using namespace std; 

User::User(const string& s) { name = s; friends = new FriendsAVL(); }
User::~User() {  delete friends; }
# SocialNet Simulator

This is a command-line C++ application that simulates the core functionalities of a basic social network. It allows for user creation, forming friendships, making posts, and performing network analysis like friend suggestions and calculating degrees of separation.

The project is built using C++ (C++14 or newer) and standard libraries, with a focus on efficient, modular, and maintainable data structures to manage relationships and content.

## Features

* **User Management**: Add new users to the network.
* **Friendship Graph**: Create mutual friendships (an undirected graph).
* **Friend Lists**: List all friends of a specific user (sorted alphabetically).
* **Posting**: Users can create posts, which are timestamped and stored.
* **Post Feed**: View the most recent posts from any user.
* **Friend Suggestions**: Get a ranked list of "friends of friends" (potential new friends) based on the number of mutual friends.
* **Degrees of Separation**: Calculate the shortest path (distance) between any two users in the network using Breadth-First Search (BFS).

## Core Data Structures

This simulation uses several key data structures, defined across multiple files, to ensure efficient operations:

1.  **Network Graph (`network.hpp` / `network.cpp`)**: The main `Network` class uses an **`unordered_map<string, User*>`**. This provides O(1) average-time lookup for any user by their username.

2.  **Friends List (`friends.hpp` / `friends.cpp`)**: Each `User` object has a pointer to a `FriendsAVL` object, which is a **self-balancing AVL Tree**.
    * **Why an AVL Tree?** It stores pointers to `User` objects, sorted by username. This automatically keeps a user's friend list in alphabetical order and guarantees O(log F) time complexity for adding friends and O(F) for iterating (where F is the number of friends).

3.  **Post Feed (`post.hpp` / `post.cpp`)**: Each `User` has a `PostsAVL` object, another **self-balancing AVL Tree**.
    * **Why an AVL Tree?** It stores `Post` objects, sorted by their `global_time` timestamp.
    * This structure ensures that inserting a new post is always O(log P) (where P is the number of posts).
    * Retrieving the **N most recent posts** is an O(N + log P) operation by performing a partial in-order traversal, which is much more efficient than sorting all posts.

4.  **Generic AVL Logic (`avl_utils.hpp`)**: All templated, generic AVL tree functions (like `balance`, `leftrotate`, `rightrotate`) are centralized in this header file for reuse by both `FriendsAVL` and `PostsAVL`.

## Project Structure

The project is broken into logical components for clarity and maintainability:

* `main.cpp`: The main entry point. Creates the `Network` object and runs the command-line interface.
* `network.hpp` / `network.cpp`: Defines the main `Network` class, which manages all users and application logic (e.g., `AddUser`, `SuggestFriends`).
* `user.hpp` / `user.cpp`: Defines the `User` struct, which acts as a node in the graph.
* `friends.hpp` / `friends.cpp`: Defines the `FriendsAVL` class for managing a user's friend list.
* `post.hpp` / `post.cpp`: Defines the `Post` struct and the `PostsAVL` class for managing a user's posts.
* `utils.hpp` / `utils.cpp`: Contains helper functions like `split`, `to_lowercase`, and `time_now`.
* `avl_utils.hpp`: Contains the generic, templated AVL tree balancing and rotation logic.
* `compile.sh`: For compiling and executing **all** the cpp files.

## Available Commands

The simulator accepts the following commands from the standard input:

* `ADD_USER <username>`
    * Adds a new user to the network.

* `ADD_FRIEND <user1> <user2>`
    * Creates a mutual friendship between `user1` and `user2`.

* `LIST_FRIENDS <username>`
    * Prints an alphabetized list of all friends of `username`.

* `SUGGEST_FRIENDS <username> <N>`
    * Recommends the top `N` users for `username` to friend. Suggestions are based on "friends of friends" and are ranked by the number of mutual friends.

* `DEGREES_OF_SEPARATION <user1> <user2>`
    * Calculates and prints the shortest path (number of friend links) between `user1` and `user2`.

* `ADD_POST <username> <content>`
    * Adds a new post with the specified `content` for `username`. The content can include spaces.

* `OUTPUT_POSTS <username> <N>`
    * Prints the `N` most recent posts made by `username` in reverse chronological order.

* `END`
    * Exits the program.

## Edge Case Handling

The application includes robust checks for common edge cases and invalid input:

* **Command Parser**:
    * Handles invalid command names (e.g., `REMOVE_USER`) with an error message.
    * Handles commands with insufficient arguments (e.g., `ADD_USER`) with an error message.
    * Uses a `try-catch` block to handle non-numeric input for `N` (e.g., `SUGGEST_FRIENDS Alice five`), preventing a crash.

* **User & Friend Management**:
    * `ADD_USER`: Prevents adding a user that already exists ("User already exists").
    * `ADD_FRIEND`:
        * Prevents friending non-existent users ("Atleast one of the users does not exist").
        * Prevents a user from friending themself ("Cannot friend self").
        * Prevents re-friending an existing friend ("alice and bob are already friends").

* **Network Analysis**:
    * `LIST_FRIENDS`:
        * Handles requests for non-existent users ("User does not exist").
        * Correctly prints a message for a valid user with no friends ("... has no friends").
    * `SUGGEST_FRIENDS`:
        * Handles requests for non-existent users ("User does not exist").
        * Correctly prints "No friend suggestions available" if there are no friends-of-friends.
    * `DEGREES_OF_SEPARATION`:
        * Handles requests involving non-existent users ("Atleast one of the users does not exist").
        * Correctly returns `0` when calculating the distance from a user to themself efficiently.
        * Correctly returns `-1` if there is no path between the two users (they are in disconnected components of the graph).

* **Post Management**:
    * `ADD_POST`: Handles requests for non-existent users ("User does not exist").
    * `OUTPUT_POSTS`:
        * Handles requests for non-existent users ("User does not exist").
        * Correctly prints a message for a valid user who has not made any posts ("... has no posts").

# How to Compile and Run

## 1. Make the scripts executable (one-time)
```bash
chmod +x compile.sh compile_io.sh
```

## 2. Compile & run (terminal)
```bash
./compile.sh
```
This script compiles the project (uses `-std=c++23`) and runs the produced `socialnet` binary directly in the terminal.

## 3. Compile & run (with input/output files)
```bash
./compile_io.sh
```
This script compiles the project and runs `socialnet` with `input.txt` as stdin and `output.txt` as stdout.


#include "network.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << "Program Started: Type 'END' to finish." << endl;
    Network net;
    while (true) {
        if (!net.interface()) break;
    }
    cout << "Program End" << endl;
    return 0;
}
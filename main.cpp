#include <iostream>
#include "parser.h"

int main() {
    // eww
    std::string p1, p2;
    std::cin >> p1;
    std::cin >> p2;

    // ugly casting
    const char* path1 = p1.c_str();
    const char* path2 = p2.c_str();

    parse(path1, path2);
    return 0;
}

// i hate you klez <3
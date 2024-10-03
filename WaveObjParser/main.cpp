#include <iostream>
#include "parser.h"
#include "colors.h"

bool withLine = false;

void begin() {
    // eww
    std::string p1, p2;
    std::cout << "[>] Path to the obj file: ";
    std::cin >> p1;
    std::cout << "[>] Path to save: ";
    std::cin >> p2;
    std::cout << "[>] Connect vertexes? (1 for yes, 0 for no): ";
    int a = 0;
    std::cin >> a;
    if (a > 1 || a < 0) {
        withLine = false;
    }
    else {
        withLine = a == 1 ? true : false;
    }


    // ugly casting
    const char* path1 = p1.c_str();
    const char* path2 = p2.c_str();

    parse(path1, path2);
}

int main() {
    rgbClamp col;
    // 0 : 1
    col = { 1, 0, 0 };
    setupBlock(col);
    return 0;
}
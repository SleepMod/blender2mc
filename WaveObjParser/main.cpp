#include <Windows.h>
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
    std::cout << "[>] Connect vertexes? (1 for yes, 0 for no): " << std::endl;

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

    std::string block = "minecraft:red_concrete";
    std::string air = "minecraft:air";

    // modifiers and constants
    const float kAngleRotation = 15.0f;
    float newAngle = 0.0f;
    int ky = 0, kz = 0;

    int x = 400, y = 36, z = -31;

    // 408 36 -31
    while (true) {

        // hearts go here
        convertObject(path1, path2, 0.0, newAngle, 0.0, x, y + ky, z, 2.0, block, "replace"); // block
        Sleep(1500); // this sleep needs to be always here

        // removers and updaters
        convertObject(path1, path2, 0.0, newAngle, 0.0, x, y + ky, z, 2.0, air, "replace"); // air
        Sleep(2000); // same for this one
        
        // sum the constant for the new angle 15 degrees for the yaw axis
        newAngle += kAngleRotation;
        ky++, kz++;
        std::cout << "\nZ angle = " << newAngle << "\nDisplaying new obj.\n";
        if (y >= 200) {
            y = 200;
        }
    }
}

int main() {
    begin();
}

// DEBUG STUFF
/*
    Coordinates:
    h1 = 251 83 -248
    h2 = 215 89 -253
    h3 = 304 91 -248
*/

/*
    -100 20 915
*/

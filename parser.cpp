#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip> // why pcs are so weird

/*
    I legit have no idea, but blender sorts its vertices
    as it wants, so a proper vertex union A->B cannot be
    properly performed, though the algorith i wrote is
    correct, for now i have no idea how to solve it.
*/

struct vec3d {
    float x, y, z;
};

void processLine(const std::string& line, std::vector<vec3d>& vertices) {
    if (line.rfind("v ", 0) == 0) {
        std::istringstream iss(line.substr(2));
        vec3d vertex;
        if (iss >> vertex.x >> vertex.y >> vertex.z) {
            vertices.push_back(vertex);
        }
    }
}

void doLine(vec3d v1, vec3d v2, std::ofstream& fw, int gap) {
    for (int i = 0; i <= gap; i++) {
        float t = (float)i / gap;
        float dx = v1.x + (v2.x - v1.x) * t;
        float dy = v1.y + (v2.y - v1.y) * t;
        float dz = v1.z + (v2.z - v1.z) * t;
        fw << std::fixed << std::setprecision(2); // i dont like this tbh, but couldn't figure anything
        fw << "particle minecraft:dust 0 1 0 1 ^" << dx << " ^" << dy + 5 << " ^" << dz << " 0 0 0 0 1 force @a" << "\n";
    }
}

void parse(const char* path1, const char* path2) {
    std::ifstream fr(path1);
    if (!fr.is_open()) {
        return;
    }

    std::vector<vec3d> vertices;
    std::string line;

    while (std::getline(fr, line)) {
        processLine(line, vertices);
    }

    fr.close();

    std::ofstream fw(path2);
    if (!fw.is_open()) {
        return;
    }

    int amp = 3;
    int gap = 25;

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        const vec3d& pvx1 = vertices[i];
        const vec3d& pvx2 = vertices[i + 1];
        doLine(
            { pvx1.x * amp, pvx1.y * amp, pvx1.z * amp },
            { pvx2.x * amp, pvx2.y * amp, pvx2.z * amp },
            fw, 
            gap
        );
    }

    fw.close();
}
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip> // why pcs are so weird
#include <cmath>

constexpr float toRadians(float deg) {
    return deg * 3.14159265358 / 180.0f;
}

struct vec3d {
    float x, y, z;
};

vec3d rotateVertex(const vec3d& vertex, float angleX, float angleY, float angleZ) {
    float radX = toRadians(angleX);
    float radY = toRadians(angleY);
    float radZ = toRadians(angleZ);

    // eje x
    float cosX = cos(radX), sinX = sin(radX);
    vec3d rotatedX = {
        vertex.x,
        vertex.y * cosX - vertex.z * sinX,
        vertex.y * sinX + vertex.z * cosX
    };

    // eje y
    float cosY = cos(radY), sinY = sin(radY);
    vec3d rotatedY = {
        rotatedX.x * cosY + rotatedX.z * sinY,
        rotatedX.y,
        -rotatedX.x * sinY + rotatedX.z * cosY
    };

    // eje z
    float cosZ = cos(radZ), sinZ = sin(radZ);
    vec3d rotatedZ = {
        rotatedY.x * cosZ - rotatedY.y * sinZ,
        rotatedY.x * sinZ + rotatedY.y * cosZ,
        rotatedY.z
    };

    return rotatedZ;
}

std::string setupString(std::string s1, std::string s2) {
    return s1 + " " + s2;
}

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
        fw << "setblock ^" << (int)dx << " ^" << (int)dy + 20 << " ^" << (int)dz << " minecraft:red_concrete replace\n";
    }
}

void doDots(vec3d vx, int kx, int ky, int kz, std::ofstream& fw, std::string block, std::string modifier) {
    fw << "setblock " << kx + (int)vx.x << " " << ky + (int)vx.y << " " << kz + (int)vx.z << " " << block << " " << modifier << "\n";
}

void convertObject(const char* path1, const char* path2, float angleX, float angleY, float angleZ, int x, int y, int z, float amplitude, std::string block, std::string modifier) {
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

    int gap = 25;

    extern bool withLine;

    int a = vertices.size();
    //printf("Vertices to process = %d", a);

    for (size_t i = 0; i < vertices.size() - 1; ++i) {
        vec3d pvx1 = rotateVertex(vertices[i], angleX, angleY, angleZ);
        vec3d pvx2 = rotateVertex(vertices[i + 1], angleX, angleY, angleZ);

        // escala
        pvx1 = { pvx1.x * amplitude, pvx1.y * amplitude, pvx1.z * amplitude };
        pvx2 = { pvx2.x * amplitude, pvx2.y * amplitude, pvx2.z * amplitude };

        if (withLine) {
            doLine(pvx1, pvx2, fw, gap);
        }
        else {
            doDots(pvx1, x, y, z, fw, block, modifier);
        }
    }

    fw.close();
}

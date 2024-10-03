#pragma once
#include <string>
#include <vector>
struct vec3d;

void processLine(const std::string& line, std::vector<vec3d>& vertices);
void parse(const char* path1, const char* path2);
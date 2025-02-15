#pragma once
#include <string>
#include <vector>
struct vec3d;

void processLine(const std::string& line, std::vector<vec3d>& vertices);
void convertObject(
	const char* path1,
	const char* path2,
	float angleX,
	float angleY,
	float angleZ,
	int x,
	int y,
	int z,
	float amplitude,
	std::string block,
	std::string modifier
);
std::string setupString(std::string s1, std::string s2);

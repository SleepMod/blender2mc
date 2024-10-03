// list of the 16 concrete blocks
const char* data[16] = {
	"pink_concrete", "magenta_concrete", "purple_concrete",	"blue_concrete",
	"light_blue_concrete", "cyan_concrete",	"green_concrete", "lime_concrete",
	"yellow_concrete", "orange_concrete", "red_concrete", "brown_concrete",
	"black_concrete", "gray_concrete", "light_gray_concrete", "white_concrete"
};

// extracted | approximated rgb value for each block
const int colArray[16] = {
	0xB0506B, 0x91287B,	0x581B7E, 0x282976, 
	0x2078A3, 0x146970,	0x3F4D1C, 0x4D8913,
	0xBA840F, 0xB84C00,	0x7D1B19, 0x55341A,
	0x06080B, 0x313232,	0x6D6A5C, 0xB1B0A6,
};

// rgb struct
struct rgbClamp {
	float r, g, b;
};

// function to ensure that cannot be above white = 0xFFFFFF
float clamp(float v, float min, float max) {
	float k = v < min ? min : v;
	return k > max ? max : k;
}

// mtl gives us the colors in the ratio of 0 : 1
// we converting it to hex to later approximation
int reinterColor(rgbClamp channels) {
    channels.r = clamp(channels.r * 255, 0.0f, 255.0f);
    channels.g = clamp(channels.g * 255, 0.0f, 255.0f);
    channels.b = clamp(channels.b * 255, 0.0f, 255.0f);
    return ((int(channels.r) << 16) + (int(channels.g) << 8) + int(channels.b));
}

// we need now to calculate the euclidian distance formula between the two colors
// which later will be used

#include <math.h> // for sqrt and pow

float colorDistance(int color1, int color2) {
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;

	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;

	// euclidean distance formula in RGB space
	return sqrt(pow(r1 - r2, 2) + pow(g1 - g2, 2) + pow(b1 - b2, 2));
}

// with the function above, we are now able to get the closest blockID
int getBlockId(int targetColor, const int colArray[], int arrSize) {
	int closestIndex = 0;
	float first = colorDistance(targetColor, colArray[0]); // first values
	for (int i = 1; i < arrSize; i++) {
		float dist = colorDistance(targetColor, colArray[i]);
		if (dist < first) {
			first = dist;
			closestIndex = i;
		}
	}
	
	return closestIndex;
}

#include <iostream>

void setupBlock(rgbClamp color) {
	int tcolor = reinterColor(color);
	int closestBlock = getBlockId(tcolor, colArray, 16);
	printf("[/] Debug, closest block is: %s\n", data[closestBlock]);
}
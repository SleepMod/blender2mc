extern char* data[16];
extern int colArray[16];

// rgb struct
struct rgbClamp {
	float r, g, b;
};

float clamp(float v, float min, float max);
int reinterColor(rgbClamp channels);
float colorDistance(int color1, int color2);
int getBlockId(int targetColor, const int colArray[], int arrSize);
void setupBlock(rgbClamp color);
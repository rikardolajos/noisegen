#include "value.h"

#include <math.h>

static float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

static float noise(int x, int y)
{
	float d = 12.9898 * x + 78.233 * y;
	float s = sin(d) * 43758.5453;
	return s - (int)s;
}

static float smooth_noise(int x, int y)
{
	float corners = (noise(x - 1, y - 1) + noise(x + 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y + 1)) / 16;
	float sides = (noise(x - 1, y) + noise(x + 1, y) + noise(x, y - 1) + noise(x, y + 1)) / 8;
	float center = noise(x, y) / 4;
	return corners + sides + center;
}

static float value_noise(float x, float y)
{
	int ix = int(x);
	int iy = int(y);
	float fx = x - ix;
	float fy = y - iy;

	float v1 = smooth_noise(ix, iy);
	float v2 = smooth_noise(ix + 1, iy);
	float v3 = smooth_noise(ix, iy + 1);
	float v4 = smooth_noise(ix + 1, iy + 1);

	float i1 = lerp(v1, v2, fx);
	float i2 = lerp(v3, v4, fx);

	return lerp(i1, i2, fy);
}
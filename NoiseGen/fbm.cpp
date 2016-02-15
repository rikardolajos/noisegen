#include "fbm.h"

#include "value.h"
#include "perlin.h"

#include <math.h>

/* Fractional Brownian motion for different noises */
float fbm_value(float x, float y, int octaves, float frequency, float lacunarity, float amplitude, float gain)
{
	float value = 0.0;
	float max_value = 0.0;

	for (int i = 0; i < octaves; i++) {
		value += value_noise(x * frequency, y * frequency) * amplitude;
		max_value += amplitude;
		frequency *= lacunarity;
		amplitude *= gain;
	}

	return value / max_value;
}

float fbm_perlin(float x, float y, float z, int octaves, int period)
{
	float value = 0.0;
	int n = octaves - 1;
	float max_value = 0.0;
	for (int i = 0; i <= octaves; i++) {
		float freq = pow(2.0, i);
		float amp = pow(0.5, i);
		value += amp * perlin_noise(x * freq, y * freq, z * freq, period * freq);
		max_value += amp;
	}

	return value / max_value;
}
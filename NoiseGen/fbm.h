#ifndef FBM_H
#define FBM_H

float fbm_value(float x, float y, int octaves, float frequency, float lacunarity, float amplitude, float gain);
float fbm_perlin(float x, float y, float z, int octaves, int period);
float fbm_worley(float x, float y, float z, int octaves, int period);

#endif
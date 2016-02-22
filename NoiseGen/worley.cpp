#include "worley.h"

#include <math.h>

int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

int hash(int x, int y, int z)
{
	return (int)((sin((x + 13) * (y + 57) * (z + 89) * 11351.0) + 1.0) * 0.5 * 256);
}

// https://aftbit.com/cell-noise-2/
float worley_noise(float x, float y, float z, int period)
{
	//x = x > period ? x - period : x;
	//y = y > period ? y - period : y;
	//z = z > period ? z - period : z;

	/* Determine which cube the evaluation point is in */
	int xi = (int)floor(x);
	int yi = (int)floor(y);
	int zi = (int)floor(z);

	int current_cube_x, current_cube_y, current_cube_z;
	float shortest_distance = 1000.0f;

	/* Loop over the neightbors */
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				
				current_cube_x = xi + i;
				current_cube_y = yi + j;
				current_cube_z = zi + k;

				int hash_code = hash(mod(current_cube_x, period), mod(current_cube_y, period), mod(current_cube_z, period));

				///* Determine how many feature points this cube has (1-2) */
				//int points = hash_code % 2 + 1;

				///* Look for the shortest distance from evaluation point to feature point */
				//for (int p = 2; p <= points + 1; p++) {
				int p = 2;
					float feature_x = (float)current_cube_x + (float)(mod(p * hash_code * 5783, 256)) / 256.0;
					float feature_y = (float)current_cube_y + (float)(mod(p * hash_code * 9419, 256)) / 256.0;
					float feature_z = (float)current_cube_z + (float)(mod(p * hash_code * 2753, 256)) / 256.0;

					float distance = sqrtf((feature_x - x) * (feature_x - x) + (feature_y - y) * (feature_y - y) + (feature_z - z) * (feature_z - z));
					if (distance < shortest_distance) {
						shortest_distance = distance;
					//}
				}
			}
		}
	}

	/* The inverse of the shortest distance normalized with the theoretical maximum */
	float inv = 1.0f - shortest_distance;

	if (inv < 0.0) {
		inv = 0.0;
	}

	/* Change from 0 - 1 to -1 - 1*/
	return inv * 2.0f - 1.0f;
}
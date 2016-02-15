#include "worley.h"

#include <math.h>

int hash(int x, int y, int z)
{
	return (int)((sin((x + 13) * (y + 57) * (z + 89) * 11351.0) + 1.0) * 256);
}

// https://aftbit.com/cell-noise-2/
float worley_noise(float x, float y, float z)
{
	/* Determine which cube the evaluation point is in */
	int xi = (int)floor(x);
	int yi = (int)floor(y);
	int zi = (int)floor(z);

	int current_cube_x, current_cube_y, current_cube_z;
	float shortest_distance = 1000.0f;
	int period = 64;

	/* Loop over the neightbors */
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {

				current_cube_x = xi + i;
				current_cube_y = yi + j;
				current_cube_z = zi + k;

				int hash_code = hash(current_cube_x % period, current_cube_y % period, current_cube_z % period);

				/* Determine how many feature points this cube has (1-5) */
				int points = hash_code % 5 + 1;

				/* Look for the shortest distance from evaluation point to feature point */
				for (int p = 2; p <= points + 1; p++) {
					float feature_x = (float)xi + (float)hash(p % period, p*p % period, p*p*p % period) / 256;
					float feature_y = (float)yi + (float)hash(p*p % period, p*p*p % period, p % period) / 256;
					float feature_z = (float)zi + (float)hash(p*p*p % period, p % period, p*p % period) / 256;

					float distance = sqrtf((feature_x - x) * (feature_x - x) + (feature_y - y) * (feature_y - y) + (feature_z - z) * (feature_z - z));
					if (distance < shortest_distance) {
						shortest_distance = distance;
					}
				}
			}
		}
	}

	/* Return the shortest distance */
	return shortest_distance;
}
#include "fbm.h"
#include "worley.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define FILENAME "worley.ex5"

#define THREE_D 1

#define WIDTH 128
#define HEIGHT 128

#if THREE_D
#define DEPTH 128
#endif

/* Main function */
int main(int argc, char** argv)
{

#if THREE_D

	FILE* fp;

	fp = fopen(FILENAME, "w");
	if (fp == NULL) {
		return -1;
	}

	/* Print header */
	fprintf(fp, "%d %d %d\n", WIDTH, HEIGHT, DEPTH);

	/* Print image */
	for (int d = 0; d < DEPTH; d++) {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {

				float freq = 1.0 / 32.0;

				float x = (float)j * freq;
				float y = (float)i * freq;
				float z = (float)d * freq;

				//int r = (int)((fbm_perlin(x, y, z, 1, (int)(128 * freq)) * 0.5 + 0.5) * 255);
				//int g = (int)((fbm_perlin(x, y, z, 2, (int)(128 * freq)) * 0.5 + 0.5) * 255);
				//int b = (int)((fbm_perlin(x, y, z, 5, (int)(128 * freq)) * 0.5 + 0.5) * 255);
				//int a = (int)((fbm_perlin(x, y, z, 8, (int)(128 * freq)) * 0.5 + 0.5) * 255);

				//int r = x * 0xff;
				//int g = y * 0xff;
				//int b = z * 0xff;
				//int a = 0xff;

				int r = (int)(worley_noise(x, y, z) * 255);
				int g = 0;
				int b = 0;
				int a = 0;

				uint32_t pixel = 0;

				pixel |= r << 24;
				pixel |= g << 16;
				pixel |= b <<  8;
				pixel |= a <<  0;

				fprintf(fp, "%u ", pixel);
			}
			fprintf(fp, "\n");
		}
	}
	

#else

	FILE* fp;

	fp = fopen(FILENAME, "w");
	if (fp == NULL) {
		return -1;
	}

	/* Print header */
	fprintf(fp, "%d %d\n", WIDTH, HEIGHT);

	/* Print image */
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {

			int noise1 = (int)((fbm_value(i, j, 2, 0.5, 2.0, 1.0, 0.5) * 0.5 + 1.0) * 255);
			int noise2 = (int)((fbm_value(i, j, 3, 10.0, 2.0, 1.0, 0.5) * 0.5 + 1.0) * 255);
			int noise3 = (int)((fbm_value(i, j, 6, 50.0, 2.0, 1.0, 0.5) * 0.5 + 1.0) * 255);
			int noise4 = 0;

			uint32_t pixel = 0;

			pixel |= noise1 << 24;
			pixel |= noise2 << 16;
			pixel |= noise3 << 8;
			pixel |= noise4 << 0;

			fprintf(fp, "%u ", pixel);
		}
		fprintf(fp, "\n");
	}


#endif

	return 0;
}
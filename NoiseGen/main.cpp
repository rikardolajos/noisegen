#include "fbm.h"
#include "worley.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define FILENAME "3D_texture_1.ex5"

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

				float freq1 = 1.0 / 8.0;
				float freq2 = 1.0 / 16.0;
				float freq3 = 1.0 / 32.0;

				float x1 = (float)j * freq1;
				float y1 = (float)i * freq1;
				float z1 = (float)d * freq1;

				float x2 = (float)j * freq2;
				float y2 = (float)i * freq2;
				float z2 = (float)d * freq2;

				float x3 = (float)j * freq3;
				float y3 = (float)i * freq3;
				float z3 = (float)d * freq3;

				float p = fbm_perlin(x2, y2, z2, 5, (int)(128 * freq2));
				float w = fbm_worley(x3, y3, z3, 5, (int)(128 * freq3));

				int r = (int)(((0.4 * p + 0.6 * w) * 0.5 + 0.5) * 255);
				int g = (int)((w * 0.5 + 0.5) * 255);
				int b = (int)((fbm_worley(x2, y2, z2, 5, (int)(128 * freq2)) * 0.5 + 0.5) * 255);
				int a = (int)((fbm_worley(x1, y1, z1, 5, (int)(128 * freq1)) * 0.5 + 0.5) * 255);

				uint32_t pixel = 0;

				pixel |= r << 24;
				pixel |= g << 16;
				pixel |= b <<  8;
				pixel |= a <<  0;

				fprintf(fp, "%u ", pixel);
				
			}
			fprintf(fp, "\n");
		}
		printf("\b\b\b\b\b\b%3.1f %%", 100 * (float)d / (float)DEPTH);
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
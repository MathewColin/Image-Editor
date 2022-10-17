// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

/*
	"img_mrg" is a structure which remembers the dimension of the matrix, the
selected zone (x1, y1, x2, y2) and the maximum value of a pixel (for P2, P3,
P5 and P6).
	"image" represents the matrix of pixel.
	"type" represents the type of picture: P1, P2, P3, P4, P5 or P6.
	"in" represents the input file.
	This function reads the type, the dimensions of the picture, the maximum
value and the pixels' values.
*/
void load_operation(margins *img_mrg, pixel **image, char *type, FILE *in)
{
	img_mrg->x1 = 0; // initialization of the selected area
	img_mrg->x2 = img_mrg->m;
	img_mrg->y1 = 0;
	img_mrg->y2 = img_mrg->n;
	if (strcmp(type, "P1") == 0) { // P1 type - text
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				fscanf(in, "%lf", &image[i][j].r);
				image[i][j].g = image[i][j].r;
				image[i][j].b = image[i][j].r;
			}
	}
	if (strcmp(type, "P2") == 0) { // P2 type - grayscale, text
		fscanf(in, "%lf", &img_mrg->maxvalue);
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				fscanf(in, "%lf", &image[i][j].r);
				image[i][j].g = image[i][j].r;
				image[i][j].b = image[i][j].r;
			}
	}
	if (strcmp(type, "P3") == 0) { // P3 type
		fscanf(in, "%lf", &img_mrg->maxvalue);
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				double red, green, blue;
				fscanf(in, "%lf%lf%lf", &red, &green, &blue);
				image[i][j].r = red; // read each colours value
				image[i][j].g = green;
				image[i][j].b = blue;
			}
	}
	if (strcmp(type, "P4") == 0) { // P4 type - binary
		char enter;
		fread(&enter, 1, 1, in); // read the leftover enter
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				fread(&image[i][j].r, sizeof(unsigned char), 1, in);
				image[i][j].g = image[i][j].r;
				image[i][j].b = image[i][j].r;
			}
	}
	if (strcmp(type, "P5") == 0) { // P5 type - grayscale, binary
		fscanf(in, "%lf", &img_mrg->maxvalue);
		char enter;
		fread(&enter, 1, 1, in); // read the leftover enter
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				unsigned char c;
				fread(&c, 1, 1, in);
				image[i][j].r = (double)c;
				image[i][j].g = image[i][j].r;
				image[i][j].b = image[i][j].r;
			}
	}
	if (strcmp(type, "P6") == 0) { // P6 type, binary
		fscanf(in, "%lf", &img_mrg->maxvalue);
		char enter;
		fread(&enter, 1, 1, in);
		for (int i = 0; i < img_mrg->n; i++)
			for (int j = 0; j < img_mrg->m; j++) {
				unsigned char c;
				fread(&c, 1, 1, in);
				image[i][j].r = (double)c;
				fread(&c, 1, 1, in);
				image[i][j].g = (double)c;
				fread(&c, 1, 1, in);
				image[i][j].b = (double)c;
			}
	}
	fclose(in);
}

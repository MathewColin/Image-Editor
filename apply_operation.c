// Copyright 2021-2022 Ceausu Matei Calin - 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

/*
	x represents a real number.
	maxvalue represents the maximum value possible of x. Since we are talking
about pixels is 255.
	This function returns 0 if x is smaller than zero, maxvalue if x is bigger
than maxvalue and x if x is between 0 and maxvalue.
*/
double clamp(double x, double maxvalue)
{
	if (x < 0)
		x = 0;
	else
		if (x > maxvalue)
			x = maxvalue;
	return x;
}

/*
	"image" represents the image and img_mrg remembers the dimensions of the
selected area, the dimensions of the matrix and the maximum possible value.
	This function applies the edge effect on the selected area. For each pixel
we apply the operation described by the kernel:
	-1 -1 -1
	-1  8 -1
	-1 -1 -1
	If the pixel is on the edge of the image, it's value remains unchanged.
*/
void edge_effect(pixel ***image, margins img_mrg)
{
	pixel **nimg = matrix_allocation(img_mrg.n, img_mrg.m);
	for (int i = 0; i < img_mrg.n; i++)
		for (int j = 0; j < img_mrg.m; j++) {
			if (i == 0 || j == 0 || i == img_mrg.n - 1 || j == img_mrg.m - 1) {
				pixelattribution(&nimg[i][j], &(*image)[i][j]);
			} else {
				if (i >= img_mrg.y1 && i < img_mrg.y2 &&
					j >= img_mrg.x1 && j < img_mrg.x2) {
					nimg[i][j].r = -1 * (*image)[i - 1][j - 1].r;
					nimg[i][j].r += -1 * (*image)[i - 1][j].r;
					nimg[i][j].r += -1 * (*image)[i - 1][j + 1].r;
					nimg[i][j].r += -1 * (*image)[i][j - 1].r;
					nimg[i][j].r += 8 * (*image)[i][j].r;
					nimg[i][j].r += -1 * (*image)[i][j + 1].r;
					nimg[i][j].r += -1 * (*image)[i + 1][j - 1].r;
					nimg[i][j].r += -1 * (*image)[i + 1][j].r;
					nimg[i][j].r += -1 * (*image)[i + 1][j + 1].r;
					nimg[i][j].r = clamp(nimg[i][j].r, img_mrg.maxvalue);
					nimg[i][j].b = -1 * (*image)[i - 1][j - 1].b;
					nimg[i][j].b += -1 * (*image)[i - 1][j].b;
					nimg[i][j].b += -1 * (*image)[i - 1][j + 1].b;
					nimg[i][j].b += -1 * (*image)[i][j - 1].b;
					nimg[i][j].b += 8 * (*image)[i][j].b;
					nimg[i][j].b += -1 * (*image)[i][j + 1].b;
					nimg[i][j].b += -1 * (*image)[i + 1][j - 1].b;
					nimg[i][j].b += -1 * (*image)[i + 1][j].b;
					nimg[i][j].b += -1 * (*image)[i + 1][j + 1].b;
					nimg[i][j].b = clamp(nimg[i][j].b, img_mrg.maxvalue);
					nimg[i][j].g = -1 * (*image)[i - 1][j - 1].g;
					nimg[i][j].g += -1 * (*image)[i - 1][j].g;
					nimg[i][j].g += -1 * (*image)[i - 1][j + 1].g;
					nimg[i][j].g += -1 * (*image)[i][j - 1].g;
					nimg[i][j].g += 8 * (*image)[i][j].g;
					nimg[i][j].g += -1 * (*image)[i][j + 1].g;
					nimg[i][j].g += -1 * (*image)[i + 1][j - 1].g;
					nimg[i][j].g += -1 * (*image)[i + 1][j].g;
					nimg[i][j].g += -1 * (*image)[i + 1][j + 1].g;
					nimg[i][j].g = clamp(nimg[i][j].g, img_mrg.maxvalue);
				} else {
					pixelattribution(&nimg[i][j], &(*image)[i][j]);
				}
			}
		}
	free_matrix_pixel(*image, img_mrg.n);
	*image = nimg;
}

/*
	"image" represents the image and img_mrg remembers the dimensions of the
selected area, the dimensions of the matrix and the maximum possible value.
	This function applies the sharpen effect on the selected area. For each
pixel we apply the operation described by the kernel:
	 0  -1  0
	-1   5 -1
	 0  -1  0
	If the pixel is on the edge of the image, it's value remains unchanged.
*/
void sharpen_effect(pixel ***image, margins img_mrg)
{
	pixel **nimg = matrix_allocation(img_mrg.n, img_mrg.m);
	for (int i = 0; i < img_mrg.n; i++)
		for (int j = 0; j < img_mrg.m; j++) {
			if (i == 0 || j == 0 || i == img_mrg.n - 1 || j == img_mrg.m - 1) {
				pixelattribution(&nimg[i][j], &(*image)[i][j]);
			} else {
				if (i >= img_mrg.y1 && i < img_mrg.y2 &&
					j >= img_mrg.x1 && j < img_mrg.x2) {
					nimg[i][j].r = -1 * (*image)[i - 1][j].r;
					nimg[i][j].r += -1 * (*image)[i][j - 1].r;
					nimg[i][j].r += 5 * (*image)[i][j].r;
					nimg[i][j].r += -1 * (*image)[i][j + 1].r;
					nimg[i][j].r += -1 * (*image)[i + 1][j].r;
					nimg[i][j].r = clamp(nimg[i][j].r, img_mrg.maxvalue);
					nimg[i][j].b = -1 * (*image)[i - 1][j].b;
					nimg[i][j].b += -1 * (*image)[i][j - 1].b;
					nimg[i][j].b += 5 * (*image)[i][j].b;
					nimg[i][j].b += -1 * (*image)[i][j + 1].b;
					nimg[i][j].b += -1 * (*image)[i + 1][j].b;
					nimg[i][j].b = clamp(nimg[i][j].b, img_mrg.maxvalue);
					nimg[i][j].g = -1 * (*image)[i - 1][j].g;
					nimg[i][j].g += -1 * (*image)[i][j - 1].g;
					nimg[i][j].g += 5 * (*image)[i][j].g;
					nimg[i][j].g += -1 * (*image)[i][j + 1].g;
					nimg[i][j].g += -1 * (*image)[i + 1][j].g;
					nimg[i][j].g = clamp(nimg[i][j].g, img_mrg.maxvalue);
				} else {
					pixelattribution(&nimg[i][j], &(*image)[i][j]);
				}
			}
		}
	free_matrix_pixel(*image, img_mrg.n);
	*image = nimg;
}

/*
	"image" represents the image and img_mrg remembers the dimensions of the
selected area, the dimensions of the matrix and the maximum possible value.
	This function applies the blur effect on the selected area. For each pixel
we apply the operation described by the kernel:
	  1 1 1
1/9 *  1 1 1
	  1 1 1
	If the pixel is on the edge of the image, it's value remains unchanged.
*/
void blur_effect(pixel ***image, margins img_mrg)
{
	pixel **nimg = matrix_allocation(img_mrg.n, img_mrg.m);
	for (int i = 0; i < img_mrg.n; i++)
		for (int j = 0; j < img_mrg.m; j++) {
			if (i == 0 || j == 0 || i == img_mrg.n - 1 || j == img_mrg.m - 1) {
				pixelattribution(&nimg[i][j], &(*image)[i][j]);
			} else {
				if (i >= img_mrg.y1 && i < img_mrg.y2 &&
					j >= img_mrg.x1 && j < img_mrg.x2) {
					nimg[i][j].r = (*image)[i - 1][j - 1].r;
					nimg[i][j].r += (*image)[i - 1][j].r;
					nimg[i][j].r += (*image)[i - 1][j + 1].r;
					nimg[i][j].r += (*image)[i][j - 1].r;
					nimg[i][j].r += (*image)[i][j].r;
					nimg[i][j].r += (*image)[i][j + 1].r;
					nimg[i][j].r += (*image)[i + 1][j - 1].r;
					nimg[i][j].r += (*image)[i + 1][j].r;
					nimg[i][j].r += (*image)[i + 1][j + 1].r;
					nimg[i][j].r /= 9.0;
					nimg[i][j].r = clamp(nimg[i][j].r, img_mrg.maxvalue);
					nimg[i][j].b = (*image)[i - 1][j - 1].b;
					nimg[i][j].b += (*image)[i - 1][j].b;
					nimg[i][j].b += (*image)[i - 1][j + 1].b;
					nimg[i][j].b += (*image)[i][j - 1].b;
					nimg[i][j].b += (*image)[i][j].b;
					nimg[i][j].b += (*image)[i][j + 1].b;
					nimg[i][j].b += (*image)[i + 1][j - 1].b;
					nimg[i][j].b += (*image)[i + 1][j].b;
					nimg[i][j].b += (*image)[i + 1][j + 1].b;
					nimg[i][j].b /= 9.0;
					nimg[i][j].b = clamp(nimg[i][j].b, img_mrg.maxvalue);
					nimg[i][j].g = (*image)[i - 1][j - 1].g;
					nimg[i][j].g += (*image)[i - 1][j].g;
					nimg[i][j].g += (*image)[i - 1][j + 1].g;
					nimg[i][j].g += (*image)[i][j - 1].g;
					nimg[i][j].g += (*image)[i][j].g;
					nimg[i][j].g += (*image)[i][j + 1].g;
					nimg[i][j].g += (*image)[i + 1][j - 1].g;
					nimg[i][j].g += (*image)[i + 1][j].g;
					nimg[i][j].g += (*image)[i + 1][j + 1].g;
					nimg[i][j].g /= 9.0;
					nimg[i][j].g = clamp(nimg[i][j].g, img_mrg.maxvalue);
				} else {
					pixelattribution(&nimg[i][j], &(*image)[i][j]);
				}
			}
		}
	free_matrix_pixel(*image, img_mrg.n);
	*image = nimg;
}

/*
	"image" represents the image and img_mrg remembers the dimensions of the
selected area, the dimensions of the matrix and the maximum possible value.
	This function applies the gaussian blur effect on the selected area.
For each pixel we apply the operation described by the kernel:
	   1 2 1
1/16 *  2 4 2
	   1 2 1
	If the pixel is on the edge of the image, it's value remains unchanged.
*/
void gaussblur_effect(pixel ***image, margins img_mrg)
{
	pixel **nimg = matrix_allocation(img_mrg.n, img_mrg.m);
	for (int i = 0; i < img_mrg.n; i++)
		for (int j = 0; j < img_mrg.m; j++) {
			if (i == 0 || j == 0 || i == img_mrg.n - 1 || j == img_mrg.m - 1) {
				pixelattribution(&nimg[i][j], &(*image)[i][j]);
			} else  {
				if (i >= img_mrg.y1 && i < img_mrg.y2 &&
					j >= img_mrg.x1 && j < img_mrg.x2) {
					nimg[i][j].r = 0.0625 * (*image)[i - 1][j - 1].r;
					nimg[i][j].r += 0.125 * (*image)[i - 1][j].r;
					nimg[i][j].r += 0.0625 * (*image)[i - 1][j + 1].r;
					nimg[i][j].r += 0.125 * (*image)[i][j - 1].r;
					nimg[i][j].r += 0.25 * (*image)[i][j].r;
					nimg[i][j].r += 0.125 * (*image)[i][j + 1].r;
					nimg[i][j].r += 0.0625 * (*image)[i + 1][j - 1].r;
					nimg[i][j].r += 0.125 * (*image)[i + 1][j].r;
					nimg[i][j].r += 0.0625 * (*image)[i + 1][j + 1].r;
					nimg[i][j].r = clamp(nimg[i][j].r, img_mrg.maxvalue);
					nimg[i][j].b = 0.0625 * (*image)[i - 1][j - 1].b;
					nimg[i][j].b += 0.125 * (*image)[i - 1][j].b;
					nimg[i][j].b += 0.0625 * (*image)[i - 1][j + 1].b;
					nimg[i][j].b += 0.125 * (*image)[i][j - 1].b;
					nimg[i][j].b += 0.25 * (*image)[i][j].b;
					nimg[i][j].b += 0.125 * (*image)[i][j + 1].b;
					nimg[i][j].b += 0.0625 * (*image)[i + 1][j - 1].b;
					nimg[i][j].b += 0.125 * (*image)[i + 1][j].b;
					nimg[i][j].b += 0.0625 * (*image)[i + 1][j + 1].b;
					nimg[i][j].b = clamp(nimg[i][j].b, img_mrg.maxvalue);
					nimg[i][j].g = 0.0625 * (*image)[i - 1][j - 1].g;
					nimg[i][j].g += 0.125 * (*image)[i - 1][j].g;
					nimg[i][j].g += 0.0625 * (*image)[i - 1][j + 1].g;
					nimg[i][j].g += 0.125 * (*image)[i][j - 1].g;
					nimg[i][j].g += 0.25 * (*image)[i][j].g;
					nimg[i][j].g += 0.125 * (*image)[i][j + 1].g;
					nimg[i][j].g += 0.0625 * (*image)[i + 1][j - 1].g;
					nimg[i][j].g += 0.125 * (*image)[i + 1][j].g;
					nimg[i][j].g += 0.0625 * (*image)[i + 1][j + 1].g;
					nimg[i][j].g = clamp(nimg[i][j].g, img_mrg.maxvalue);
				} else {
					pixelattribution(&nimg[i][j], &(*image)[i][j]);
				}
			}
		}
	free_matrix_pixel(*image, img_mrg.n);
	*image = nimg;
}

/*
	"image" represents the matrix of pixels, "img_mrg" remembers the
dimensions of the image, the selected area and the maximum value of a
pixel and "type" represents the type of image (P1, P2, P3, P4, P5 or P6).
	This function is used when the user inputs APPLY command and reads the
effect character by character.
	If the user inputs just "APPLY" then that is an invalid command.
	It also checks if the effect introduced is valid.
*/
void apply_operation(pixel ***image, margins img_mrg, char *type)
{
	char *option = chararray_allocation(OPERATION_LENGTH);
	char c = ' ';
	int len = 0;
	while (c != '\n') {
		scanf("%c", &c);
		option[len] = c;
		len++;
	}
	option[len] = '\0';
	if (strcmp(option, "\n") == 0) {
		printf("Invalid command\n");
		free(option);
		return;
	}
	char **possible = (char **)malloc(4 * sizeof(char *));
	if (!possible)
		mem_error();
	for (int i = 0; i < 4; i++)
		possible[i] = chararray_allocation(OPERATION_LENGTH);
	strcpy(possible[0], " EDGE\n");
	strcpy(possible[1], " SHARPEN\n");
	strcpy(possible[2], " BLUR\n");
	strcpy(possible[3], " GAUSSIAN_BLUR\n");
	int recognized = 0;
	for (int i = 0; i < 4; i++)
		if (strcmp(possible[i], option) == 0)
			recognized = 1;
	if (recognized == 0) {
		printf("APPLY parameter invalid\n");
		free(option);
		free_matrix(possible, 4);
		return;
	}
	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0) {
		printf("Easy, Charlie Chaplin\n");
		free(option);
		free_matrix(possible, 4);
		return;
	}
	if (strcmp(option, possible[0]) == 0) {
		edge_effect(image, img_mrg);
		printf("APPLY EDGE done\n");
	}
	if (strcmp(option, possible[1]) == 0) {
		sharpen_effect(image, img_mrg);
		printf("APPLY SHARPEN done\n");
	}
	if (strcmp(option, possible[2]) == 0) {
		blur_effect(image, img_mrg);
		printf("APPLY BLUR done\n");
	}
	if (strcmp(option, possible[3]) == 0) {
		gaussblur_effect(image, img_mrg);
		printf("APPLY GAUSSIAN_BLUR done\n");
	}
	free(option);
	free_matrix(possible, 4);
}

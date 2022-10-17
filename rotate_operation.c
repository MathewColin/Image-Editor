// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

/*
	"img_mrg" remembers the dimensions of the matrix (n, m), the selected area
x1, y1, x2, y2 and the maximum values of a pixel.
	This function checks if the selected area corresponds to the whole image.
This happens when x1 = 0, x2 = n, y1 = 0 and y2 = m.
	The function returns 1 if the whole image is selected, or it returns 0
otherwise.
*/
int full_image(margins *img_mrg)
{
	if (img_mrg->x1 != 0)
		return 0;
	if (img_mrg->x2 != img_mrg->m)
		return 0;
	if (img_mrg->y1 != 0)
		return 0;
	if (img_mrg->y2 != img_mrg->n)
		return 0;
	return 1;
}

/*
	"x" represents an angle and this function check if that value represents
a valid angle. In our case if it's value is +90, -90, +180, -180, +270, -270,
+360, -360 or 0 degrees.
	The function returns 1 if the angle is valid, 0 otherwise.
*/
int valid_angle(int x)
{
	if (x < 0)
		x = -x;
	if (x == 90 || x == 180 || x == 270 || x == 360 || x == 0)
		return 1;
	return 0;
}

/*
	"img_mrg" remembers the dimensions of the matrix, the selected area and
the maximum value of a pixel.
	"image" represents the matrix of pixels.
	This function rotates a certain part of the whole matrix counterclockwise.
Whoever that part that has to be rotated needs to be a square.
*/
void rotate_90_counterclockwise(margins *img_mrg, pixel **image)
{
	int l = img_mrg->x2 - img_mrg->x1;
	pixel **aux = matrix_allocation(l, l);
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++) {
			int aux1 = i + img_mrg->y1;
			int aux2 = j + img_mrg->x1;
			pixelattribution(&aux[l - j - 1][i], &image[aux1][aux2]);
		}
	for (int i = 0; i < l; i++)
		for (int j = 0; j < l; j++) {
			int aux1 = i + img_mrg->y1;
			int aux2 = j + img_mrg->x1;
			pixelattribution(&image[aux1][aux2], &aux[i][j]);
		}
	free_matrix_pixel(aux, l);
}

/*
	"img_mrg" remembers the dimensions of the matrix, the selected area and
the maximum value of a pixel.
	"image" represents the matrix of pixels.
	This function rotates the entire matrix counterclockwise.
*/
void rotate_fullimg_90_counterclockwise(margins *img_mrg, pixel ***image)
{
	pixel **new_image = matrix_allocation(img_mrg->m, img_mrg->n);
	for (int i = 0; i < img_mrg->n ; i++)
		for (int j = 0; j < img_mrg->m; j++) {
			int aux1 = img_mrg->m - j - 1;
			pixelattribution(&new_image[aux1][i], &(*image)[i][j]);
		}
	free_matrix_pixel(*image, img_mrg->n);
	*image = new_image;
	int c = img_mrg->n;
	img_mrg->n = img_mrg->m;
	img_mrg->m = c;
	c = img_mrg->x1;
	img_mrg->x1 = img_mrg->y1;
	img_mrg->y1 = c;
	c = img_mrg->x2;
	img_mrg->x2 = img_mrg->y2;
	img_mrg->y2 = c;
}

/*
	"img_mrg" remembers the dimensions of the matrix, the selected area and
the maximum value of a pixel.
	"image" represents the matrix of pixels.
	This function is used when the user inputs the ROTATE command;
	If the value of the angle is 360, -360 or 0 degrees the matrix remains
unchanged.
	If the value of the angle is 90 or -270, the selected part or the
entire matrix has to be rotated 90 degrees clockwise, which is equivalent
with three 90 degrees counterclockwise rotations.
	If the value of the angle is 180 or -180, the selected part or the entire
matrix has to be rotated 2 times with 90 degrees counterclockwise.
	If the values is -90 or 270, the selected part or the entire matrix has
to be rotated once 90 degrees counterclockwise.
*/
void rotate_operation(margins *img_mrg, pixel ***image)
{
	int value;
	scanf("%d", &value);
	if (valid_angle(value) == 0) { // check if the angle is valid
		printf("Unsupported rotation angle\n");
		return;
	}
	if (full_image(img_mrg)) { // if the entire image is selected
		if (value == 360 || value == -360 || value == 0) {
			printf("Rotated %d\n", value);
			return;
		}
		if (value == 90 || value == -270) {
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			printf("Rotated %d\n", value);
			return;
		}
		if (value == 180 || value == -180) {
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			printf("Rotated %d\n", value);
			return;
		}
		if (value == 270 || value == -90) {
			rotate_fullimg_90_counterclockwise(&(*img_mrg), image);
			printf("Rotated %d\n", value);
			return;
		}
	}
	int if_do = 0; // 1 - if the selection is a square; 0 - otherwise
	int l = img_mrg->x2 - img_mrg->x1, h = img_mrg->y2 - img_mrg->y1;
	if (l == h)
		if_do = 1;
	if (!if_do) {
		printf("The selection must be a square\n");
		return;
	}
	if (value == 360 || value == -360 || value == 0) {
		printf("Rotated %d\n", value);
		return;
	}
	if (value == 90 || value == -270) {
		rotate_90_counterclockwise(&(*img_mrg), *image);
		rotate_90_counterclockwise(&(*img_mrg), *image);
		rotate_90_counterclockwise(&(*img_mrg), *image);
		printf("Rotated %d\n", value);
		return;
	}
	if (value == 180 || value == -180) {
		rotate_90_counterclockwise(&(*img_mrg), *image);
		rotate_90_counterclockwise(&(*img_mrg), *image);
		printf("Rotated %d\n", value);
		return;
	}
	if (value == 270 || value == -90) {
		rotate_90_counterclockwise(&(*img_mrg), *image);
		printf("Rotated %d\n", value);
		return;
	}
}

// Copyright 2021-2022 Ceausu Matei Calin - 311CA
#include <stdio.h>

#include "utilities.h"

/*
	"img_mrg" remembers the dimensions of the matrix, the selected area and
the maximum value of a pixel.
	"image" represents the matrix of pixels.
	This functions reduces the image to the selected area.
*/
void crop_operation(margins *img_mrg, pixel ***image)
{
	int new_n, new_m; // new values of dimensions
	new_m = img_mrg->x2 - img_mrg->x1;
	new_n = img_mrg->y2 - img_mrg->y1;
	pixel **new_image = matrix_allocation(new_n, new_m);
	for (int i = img_mrg->y1; i < img_mrg->y2; i++)
		for (int j = img_mrg->x1; j < img_mrg->x2; j++) {
			int aux1 = i - img_mrg->y1;
			int aux2 = j - img_mrg->x1;
			// copy the values in the selected area in the new matrix
			pixelattribution(&new_image[aux1][aux2], &(*image)[i][j]);
		}
	free_matrix_pixel(*image, img_mrg->n); // free the memory allocated
	// change the selected area, the dimension and the matrix
	img_mrg->x1 = 0;
	img_mrg->y1 = 0;
	img_mrg->x2 = new_m;
	img_mrg->y2 = new_n;
	img_mrg->n = new_n;
	img_mrg->m = new_m;
	*image = new_image;
	printf("Image cropped\n");
}

// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "utilities.h"
#include "select_operation.h"
#include "rotate_operation.h"
#include "crop_operation.h"
#include "apply_operation.h"
#include "save_operation.h"
#include "load_operation.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

int main(void)
{
	FILE *in; // input file
	char *operation = NULL, *type = NULL, *filename = NULL;
	triple_chararray(&operation, &type, &filename);
	strcpy(operation, "-");
	pixel **image; // matrix of pixels
	margins img_mrg;
	short img_loaded = 0; // 1 - an image is loaded, 0 otherwise
	while (strcmp(operation, "EXIT") != 0) {
		scanf("%s", operation);
		int command_recognized = 0; // 1 - known command, 0 otherwise
		if (strcmp(operation, "LOAD") == 0) { // Load operation
			command_recognized = 1;
			if (img_loaded == 1)
				free_matrix_pixel(image, img_mrg.n);
			scanf("%s", filename);
			img_loaded = 1;
			in = fopen(filename, "rt");
			if (!in) {
				printf("Failed to load %s\n", filename);
				img_loaded = 0, img_mrg.n = 0, img_mrg.m = 0;
				get_leftovers();
			} else {
				fscanf(in, "%s", type);
				fscanf(in, "%d%d", &img_mrg.m, &img_mrg.n);
				image = matrix_allocation(img_mrg.n, img_mrg.m);
				load_operation(&img_mrg, image, type, in);
				printf("Loaded %s\n", filename);
			}
		}
		if (strcmp(operation, "SELECT") == 0) { // Select or select all
			command_recognized = 1;
			if (img_loaded == 0)
				no_image();
			else
				select_operation(&img_mrg);
		}
		if (strcmp(operation, "ROTATE") == 0) { // Rotate operation
			command_recognized = 1;
			if (img_loaded == 0)
				no_image();
			else
				rotate_operation(&img_mrg, &image);
		}
		if (strcmp(operation, "CROP") == 0) { // Crop operation
			command_recognized = 1;
			if (img_loaded == 0)
				no_image();
			else
				crop_operation(&img_mrg, &image);
		}
		if (strcmp(operation, "APPLY") == 0) { // Apply operation
			command_recognized = 1;
			if (img_loaded == 0)
				no_image();
			else
				apply_operation(&image, img_mrg, type);
		}
		if (strcmp(operation, "SAVE") == 0) { // Save operation
			command_recognized = 1;
			if (img_loaded == 0)
				no_image();
			else
				save_operation(img_mrg, image, type);
		}
		if (strcmp(operation, "EXIT") == 0) { // Exit
			command_recognized = 1;
			if (img_loaded == 0)
				printf("No image loaded\n");
		}
		if (!command_recognized) {
			printf("Invalid command\n");
			get_leftovers();
		}
	}
	if (img_mrg.n != 0)
		free_matrix_pixel(image, img_mrg.n);
	free_arrays(&operation, &type, &filename); // free allocated memory
	return 0;
}

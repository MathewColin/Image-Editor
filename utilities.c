// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

// This function is for defensive programming.
void mem_error(void)
{
	fprintf(stderr, "Could not allocate memory.\n");
	exit(-1);
}

// This function copies the values of pixel b to pixel a.
void pixelattribution(pixel *a, pixel *b)
{
	a->r = b->r;
	a->g = b->g;
	a->b = b->b;
}

// This function reads the leftover characters after an invalid command.
void get_leftovers(void)
{
	char g;
	do {
		scanf("%c", &g);
	} while (g != '\n');
}

/*
	This function allocates memory for a matrix of pixel with n lines and m
columns.
*/
pixel **matrix_allocation(int n, int m)
{
	pixel **a = (pixel **)calloc(n, sizeof(pixel *));
	if (!a) {
		fprintf(stderr, "Out of memory\n");
		exit(0);
	}
	for (int i = 0; i < n; i++) {
		a[i] = (pixel *)calloc(m, sizeof(pixel));
		if (!a[i]) {
			fprintf(stderr, "Out of memory\n");
			exit(0);
		}
	}
	return a;
}

// This function frees the allocated memory for a matrix of pixels.
void free_matrix_pixel(pixel **image, int n)
{
	for (int i = 0; i < n; i++)
		free(image[i]);
	free(image);
}

// This function frees the allocated memory for a matrix of characters.
void free_matrix(char **matrix, int n)
{
	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

// This function prints the specifc message and read the leftover characters.
void no_image(void)
{
	printf("No image loaded\n");
	get_leftovers();
}

// This function allocates memory for an array of characters.
char *chararray_allocation(int n)
{
	char *a = (char *)malloc(n * sizeof(char));
	if (!a)
		mem_error();
	return a;
}

// This function allocates memory three arrays of characters.
void triple_chararray(char **a, char **b, char **c)
{
	*a = chararray_allocation(OPERATION_LENGTH);
	*b = chararray_allocation(FILENAME_LENGTH);
	*c = chararray_allocation(FILENAME_LENGTH);
}

// This function frees the memory allocated.
void free_arrays(char **a, char **b, char **c)
{
	free(*a);
	free(*b);
	free(*c);
}

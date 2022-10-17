// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#ifndef UTILITIES_H
#define UTILITIES_H

typedef struct {
	double r, g, b;
} pixel;

typedef struct {
	int n, m;
	int x1, y1, x2, y2;
	double maxvalue;
} margins;

void mem_error(void);

void pixelattribution(pixel *a, pixel *b);

void get_leftovers(void);

pixel **matrix_allocation(int n, int m);

void free_matrix_pixel(pixel **image, int n);

void free_matrix(char **matrix, int n);

void no_image(void);

char *chararray_allocation(int n);

void triple_chararray(char **a, char **b, char **c);

void free_arrays(char **a, char **b, char **c);

#endif

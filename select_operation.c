// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50
#define COR_VA -30000 // COR_VA == CORRUPT_VALUE

/*
	x1, x2, y1, y2 represents the coordinates of the corners of the selected
area
	img_mrg remembers the dimensions of the image, the selected area and the
maximum value of a pixel.
	This function checks if the coordinated are correct.
	It returns 1 if all coordinates are correct, 0 otherwise.
*/
int check_coord(int x1, int x2, int y1, int y2, margins img_mrg)
{
	if (x1 < 0 || x1 > img_mrg.m)
		return 0;
	if ((x2 < 0 || x2 > img_mrg.m))
		return 0;
	if (x1 == x2)
		return 0;
	if (y1 < 0 || y1 > img_mrg.n)
		return 0;
	if ((y2 < 0 || y2 > img_mrg.n))
		return 0;
	if (y1 == y2)
		return 0;
	return 1;
}

/*
	This function reads the remaining coordinates of the selected area.
	The function reads character by character. If the character is space, it
moves to the next coordinate, if it is a letter, the coordinates are not
valid, and if it is '\n', the reading ends. At the end of the reading, if not
all coordinates are numbers, then the value in the coordinates will be
overwritten with a corrupt value.
*/
void get_coords(int *y1, int *x2, int *y2)
{
	char *coord = chararray_allocation(FILENAME_LENGTH);
	char *nothing = chararray_allocation(3);
	nothing[0] = ' '; // in case nothing comes after APPLY
	nothing[1] = '\n';
	nothing[2] = '\0';
	char c = '-';
	getchar();
	int over = 1, len = 0;
	int letters = 0;
	strcpy(coord, nothing);
	while (over == 1) {
		if (c == '\n')
			over = 0;
		while (c != ' ' && over) {
			scanf("%c", &c);
			if (isalpha(c))
				letters = 1;
			if (c == '\n') {
				over = 0;
			} else {
				if (c != ' ')
					coord[len++] = c;
			}
		}
		coord[len] = '\0';
		if (over == 1)
			*y1 = atoi(coord); // convert string into number
		if (c == '\n') {
			over = 0;
		} else {
			c = '\0';
			len = 0;
		}
		while (c != ' ' && over) {
			scanf("%c", &c);
			if (isalpha(c))
				letters = 1;
			if (c == '\n') {
				over = 0;
			} else {
				if (c != ' ')
					coord[len++] = c;
			}
		}
		coord[len] = '\0';
		if (over == 1)
			*x2 = atoi(coord); // convert string into number
		if (c == '\n') {
			over = 0;
		} else {
			c = '\0';
			len = 0;
		}
		while (c != ' ' && over) {
			scanf("%c", &c);
			if (isalpha(c))
				letters = 1;
			if (c == '\n') {
				over = 0;
			} else {
				if (c != ' ')
					coord[len++] = c;
			}
		}
		coord[len] = '\0';
		*y2 = atoi(coord); // convert string into number
		over = 0;
	}
	free(coord); // free allocated memory
	free(nothing);
	if (letters == 1) { // if there are letters, the coordinates are wrong
		*x2 = COR_VA;
		*y1 = COR_VA;
		*y2 = COR_VA;
	}
}

/*
	"img_mrg" remembers the dimensions of the matrix, the selected area and
the maximum value of a pixel.
	This function is used when the user inputs SELECT or SELECT ALL.
*/
void select_operation(margins *img_mrg)
{
	char *comm = (char *)calloc(FILENAME_LENGTH, sizeof(char));
	if (!comm) {
		fprintf(stderr, "Could not allocate memory.\n");
		return;
	}
	scanf("%s", comm);
	if (strcmp(comm, "ALL") == 0) {
		img_mrg->x1 = 0;
		img_mrg->y1 = 0;
		img_mrg->x2 = img_mrg->m;
		img_mrg->y2 = img_mrg->n;
		printf("Selected ALL\n");
	} else {
		int cx1, cx2 = COR_VA, cy1 = COR_VA, cy2 = COR_VA, complete;
		cx1 = atoi(comm);
		get_coords(&cy1, &cx2, &cy2);
		if (cx1 == COR_VA || cx2 == COR_VA || cy1 == COR_VA || cy2 == COR_VA)
			complete = 0;
		else
			complete = 1;
		if (complete == 0) {
			printf("Invalid command\n");
			free(comm);
			return;
		}
		if (cx1 > cx2) {
			int a = cx1;
			cx1 = cx2;
			cx2 = a;
		}
		if (cy1 > cy2) {
			int a = cy1;
			cy1 = cy2;
			cy2 = a;
		}
		if (check_coord(cx1, cx2, cy1, cy2, *img_mrg) == 0) {
			printf("Invalid set of coordinates\n");
		} else {
			img_mrg->x1 = cx1;
			img_mrg->x2 = cx2;
			img_mrg->y1 = cy1;
			img_mrg->y2 = cy2;
			printf("Selected %d %d %d %d\n", cx1, cy1, cx2, cy2);
		}
	}
	free(comm);
}

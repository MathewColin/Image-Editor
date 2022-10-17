// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utilities.h"

#define OPERATION_LENGTH 20
#define FILENAME_LENGTH 50

/*
	"out" represents the output file and "type" represents the type of image
loaded at that moment.
	This is a function that prints the type of the image when it is saved
as ascii.
*/
void print_ascii_type(char *type, FILE *out)
{
	if (strcmp(type, "P1") == 0 || strcmp(type, "P2") == 0 ||
		strcmp(type, "P3") == 0)
		fprintf(out, "%s\n", type);
	if (strcmp(type, "P4") == 0)
		fprintf(out, "%s\n", "P1");
	if (strcmp(type, "P5") == 0)
		fprintf(out, "%s\n", "P2");
	if (strcmp(type, "P6") == 0)
		fprintf(out, "%s\n", "P3");
}

/*
	"img_mrg" remembers the dimensions of the image, the selected area and
the maximum value of a pixel. "image" represents the loaded image and "type"
represents the type of the loaded image (P1, P2, P3, P4, P5, P6).
	This function reads the name of the output file and how the image will
be saved, (binary or ascii)
	Also before printing the values of the pixels, it rounds the value.
*/
void save_operation(margins img_mrg, pixel **image, char *type)
{
	char *output = chararray_allocation(FILENAME_LENGTH);
	char *save_type = chararray_allocation(FILENAME_LENGTH);
	scanf("%s", output); // read output file as a string
	char c = ' ';
	int len = 0;
	while (c != '\n') { // read save_type character by character
		scanf("%c", &c);
		save_type[len] = c;
		len++;
	}
	save_type[len] = '\0';
	FILE *out = fopen(output, "wt");
	printf("Saved %s\n", output);
	if (strcmp(save_type, " ascii\n") == 0) { // save as text
		print_ascii_type(type, out);
		fprintf(out, "%d %d\n", img_mrg.m, img_mrg.n);
		if (strcmp(type, "P2") == 0 || strcmp(type, "P3") == 0 ||
			strcmp(type, "P5") == 0 || strcmp(type, "P6") == 0)
			fprintf(out, "%.0lf\n", img_mrg.maxvalue);
		if (strcmp(type, "P1") == 0 || strcmp(type, "P2") == 0 ||
			strcmp(type, "P4") == 0 || strcmp(type, "P5") == 0)
			for (int i = 0; i < img_mrg.n; i++) {
				for (int j = 0; j < img_mrg.m; j++)
					fprintf(out, "%.0lf ", round(image[i][j].r));
				fprintf(out, "\n");
			}
		if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
			for (int i = 0; i < img_mrg.n; i++) {
				for (int j = 0; j < img_mrg.m; j++) {
					double red = round(image[i][j].r), blue, green;
					green = round(image[i][j].g);
					blue = round(image[i][j].b);
					fprintf(out, "%.0lf %.0lf %.0lf ", red, green, blue);
				}
				fprintf(out, "\n");
			}
	} else { // save as binary
		if (strcmp(type, "P4") == 0 || strcmp(type, "P5") == 0 ||
			strcmp(type, "P6") == 0)
			fprintf(out, "%s\n", type);
		if (strcmp(type, "P1") == 0)
			fprintf(out, "%s\n", "P4");
		if (strcmp(type, "P2") == 0)
			fprintf(out, "%s\n", "P5");
		if (strcmp(type, "P3") == 0)
			fprintf(out, "%s\n", "P6");
		fprintf(out, "%d %d\n", img_mrg.m, img_mrg.n);
		if (strcmp(type, "P5") == 0 || strcmp(type, "P6") == 0 ||
			strcmp(type, "P2") == 0 || strcmp(type, "P3") == 0)
			fprintf(out, "%.0lf\n", img_mrg.maxvalue);
		fclose(out);
		out = fopen(output, "ab");
		if (strcmp(type, "P4") == 0 || strcmp(type, "P5") == 0 ||
			strcmp(type, "P2") == 0 || strcmp(type, "P1") == 0)
			for (int i = 0; i < img_mrg.n; i++) {
				for (int j = 0; j < img_mrg.m; j++) {
					unsigned char aux;
					aux = (unsigned char)round(image[i][j].r);
					fwrite(&aux, sizeof(unsigned char), 1, out);
				}
			}
		if (strcmp(type, "P6") == 0 || strcmp(type, "P3") == 0)
			for (int i = 0; i < img_mrg.n; i++)
				for (int j = 0; j < img_mrg.m; j++) {
					unsigned char aux;
					aux = (unsigned char)round(image[i][j].r);
					fwrite(&aux, sizeof(unsigned char), 1, out);
					aux = (unsigned char)round(image[i][j].g);
					fwrite(&aux, sizeof(unsigned char), 1, out);
					aux = (unsigned char)round(image[i][j].b);
					fwrite(&aux, sizeof(unsigned char), 1, out);
				}
	}
	fclose(out);
	free(save_type);
	free(output);
}

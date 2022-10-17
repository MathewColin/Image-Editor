// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#ifndef APPLY_H
#define APPLY_H

double clamp(double x, double maxvalue);

void edge_effect(pixel ***image, margins img_mrg);

void sharpen_effect(pixel ***image, margins img_mrg);

void blur_effect(pixel ***image, margins img_mrg);

void gaussblur_effect(pixel ***image, margins img_mrg);

void apply_operation(pixel ***image, margins img_mrg, char *type);

#endif

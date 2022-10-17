// Copyright 2021-2022 Ceausu Matei Calin, 311CA
#ifndef ROTATE_H
#define ROTATE_H

int full_image(margins *img_mrg);

int valid_angle(int x);

void rotate_90_counterclockwise(margins *img_mrg, pixel **image);

void rotate_fullimg_90_counterclockwise(margins *img_mrg, pixel ***image);

void rotate_operation(margins *img_mrg, pixel ***image);

#endif

# Copyright 2020 Darius Neatu <neatudarius@gmail.com>

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c utilities.c select_operation.c rotate_operation.c crop_operation.c apply_operation.c save_operation.c load_operation.c -o image_editor -lm
	
clean:
	rm -f $(TARGETS)

pack:
	zip -FSr 311CA_CeausuMateiCalin_Tema3.zip README Makefile *.c *.h

.PHONY: pack clean

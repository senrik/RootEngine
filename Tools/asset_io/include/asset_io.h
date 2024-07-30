#ifndef ASSET_IO_H
#define ASSET_IO_H
#include <stdio.h>
#include <stdlib.h>
#include <ufbx.h>
#include <stb_image.h>
#include <data_struct.h>
#ifdef __cplusplus
extern "C" {
#endif


void read_textfile(rt_string*,const char *);

unsigned char* load_image(const char*, int*, int*, int*, int);
void write_binaryfile(char*, RTuint, unsigned char[]);
#ifdef __cplusplus
}
#endif
#endif
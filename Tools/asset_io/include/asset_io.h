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


rt_string read_textfile(const char *);

char* load_image(const char*, int*, int*, int*, int);
#ifdef __cplusplus
}
#endif
#endif
#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <data_types.h>
#include <stdlib.h> // used for malloc/realloc
#ifdef __cplusplus
extern "C" {
#endif

// TODO: Implement our own memory management instead of using stdlib's stuff

#define INITIAL_STRING_SIZE 128
typedef struct rt_string {
	char* data;
	RTuint length;
	RTuint size;
} rt_string;

void rt_string_init(rt_string*);
void rt_string_append(rt_string*, const rt_string*);
void rt_string_char_append(rt_string*, const char*, RTuint);
void rt_string_clear(rt_string*);
void rt_string_terminate(rt_string*);

#ifdef __cplusplus
}
#endif
#endif
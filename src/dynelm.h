#ifndef DYNELM_H
#define DYNELM_H

#include <stdint.h>

#define MAX_DIGIT_COUNT 1000

typedef uint8_t byte;
typedef uint64_t uint64;

typedef struct d_int
{
    short int size;
    byte* digits;
    byte is_signed;
} d_int;

typedef struct d_float
{
    short int decimal_size;
    short int floating_size;
    byte* decimal_digits;
    byte* floating_digits;
    byte is_signed;
} d_float;

// typedef struct d_str
// {

// } d_str;

typedef d_int dint;
typedef d_float dfloat;
// typedef d_str dstr;

d_int*      dint_init(char a[]);
d_float*    dfloat_init(char a[]);
// d_str*      dstr_init(char a[]);

char*       dint_to_str(dint* value);
char*       dfloat_to_str(dfloat* value);
// char*       dstr_to_str(dfloat* value);

void        free_dint(dint* ptr);
void        free_dfloat(dfloat* ptr);
// void        free_dstr(dstr* ptr);

#endif
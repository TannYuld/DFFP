#ifndef DYNIO_H
#define DYNIO_H
#include "dynelm.h"

#define DEFUALT_ESCAPE_SEQUENCE 22

#define CURSOR_UP "\033[A"
#define CURSOR_DOWN "\033[B"
#define CURSOR_DELETE "\033[K"
#define CURSOR_BACKSPACE "\b"

#define UP_ARROW 65
#define DOWN_ARROW 66
#define RIGHT_ARROW 67
#define LEFT_ARROW 68
#define ENTER 10

typedef enum INPUT_TYPES
{
    IT_BOOL     = 1000,
    IT_TXT_STR  = 1010,
    IT_TXT_CHR  = 1011,
    IT_NMB_INT  = 1020,
    IT_NMB_FLT  = 1021,
    IT_NBM_DGT  = 1022,
} INPUT_TYPES;

void    init_input_system();

byte    get_boolean_input();
char*   get_string_input();
char    get_char_input();
dint*   get_int_input();
dfloat* get_float_input();
byte    get_digit_input();


#endif
#include "dynelm.h"
#include "dynio.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <termios.h>
#include <unistd.h>

const char VERTICAL_ARROW_KEYS[] = {RIGHT_ARROW, LEFT_ARROW, ENTER};
const char NUMERIC_KEYS[] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};

char get_selected_key(char arr[], int size);
static void restore_mode(const struct termios *old_t);
static void set_raw_mode(struct termios *old_t);
char readky();
void remove_chr(int n);

byte get_boolean_input()
{
    char ky;
    char selected_arrow = LEFT_ARROW;
    const byte text_size = 14;
    do
    {
        printf("%sTrue%s   %sFalse%s", (selected_arrow == LEFT_ARROW) ? "(" : "", (selected_arrow == LEFT_ARROW) ? ")" : "", (selected_arrow == RIGHT_ARROW) ? "(" : "", (selected_arrow == RIGHT_ARROW) ? ")" : "");
        ky = get_selected_key(VERTICAL_ARROW_KEYS, 3);
        if(ky != ENTER)
        {
            selected_arrow = ky;
            remove_chr(text_size);
            continue;
        }else
        {
            return (selected_arrow == LEFT_ARROW) ? 1 : 0;
        }
    }while(ky != -1);
    return 0;
}

char* get_string_input()
{
    const buffer_size_offset = 10;

    int chr;
    int lenght = 0;
    int buffer_size = 1;
    char* str = (char*)malloc(sizeof(char) * (buffer_size_offset * buffer_size));

    while ((chr = getchar()) != '\n' && chr != EOF)
    {
        if(++lenght >= buffer_size_offset * buffer_size)
        {
            str = realloc(str, ++buffer_size * buffer_size_offset);
        }
        str[lenght - 1] = chr;
    }

    if(++lenght >= buffer_size_offset * buffer_size)
    {
        str = realloc(str, (buffer_size * buffer_size_offset) + 1);
    }
    str[lenght - 1] = '\0';
    
    return str;
}

char get_char_input()
{
    char chr = readky();
    return chr;
}  

dint*   get_int_input()
{
    char* str = get_string_input();
    dint* number = dint_init(str);

    free(str);
    return number;
}

dfloat* get_float_input()
{
    char* str = get_string_input();
    dfloat* number = dfloat_init(str);

    free(str);
    return number;
}

byte get_digit_input()
{
    char chr = get_selected_key(NUMERIC_KEYS, 10);

    switch(chr)
    {
        case 48: return 0;
        case 49: return 1;
        case 50: return 2;
        case 51: return 3;
        case 52: return 4;
        case 53: return 5;
        case 54: return 6;
        case 55: return 7;
        case 56: return 8;
        case 57: return 9;
        default: return -1;
    }
}



char get_selected_key(char* arr, int size)
{
    char ch;
    do
    {
        ch = readky();
        for(int i = 0; i < size; i++)
        {
            if(ch == arr[i])
            {
                return ch;
            }else if(ch == DEFUALT_ESCAPE_SEQUENCE)
            {
                return -1;
            }
        }
    }while(0==0);
    return -1;
}

char readky()
{
    struct termios old_t;
    set_raw_mode(&old_t);

    int ch = getchar();

    if (ch == 27) {
        if (getchar() == '[') {
            ch = getchar();
        }
    }

    restore_mode(&old_t);
    return ch;
}

void remove_chr(int n)
{
    for(int i = 0; i < n; i++)
    {
        printf(CURSOR_BACKSPACE);
    }
    fflush(stdout);
}

static void set_raw_mode(struct termios *old_t) 
{
    struct termios new_t;
    tcgetattr(STDIN_FILENO, old_t);
    new_t = *old_t;
    new_t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_t);
}

static void restore_mode(const struct termios *old_t) 
{
    tcsetattr(STDIN_FILENO, TCSANOW, old_t);
}

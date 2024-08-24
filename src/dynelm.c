#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "dynelm.h"

#define max(a, b) ((a) > (b) ? (a) : (b)) 

dint* dint_init(char a[])
{   
    const int str_len = strlen(a);
    if(str_len > MAX_DIGIT_COUNT)
    {
        perror("Failed to initialize dynamic integer (dynamic integer can't be greater than MAX_DIGIT_COUNT)");
        return NULL;
    }

    const byte is_signed_val = (a[0] == '-') ? 1 : 0;

    dint* number = malloc(sizeof(dint));
    number->is_signed = is_signed_val;
    number->digits = malloc(sizeof(byte) * ((is_signed_val == 1) ? str_len - 1 : str_len));
    number->size = (is_signed_val == 1) ? str_len - 1 : str_len;

    if(number == NULL || number->digits == NULL)
    {
        perror("Failed to initialize dynamic integer (can't allocate more memory)");
        free_dint(number);
        return NULL;
    }

    if(is_signed_val)
    {
        for(int i = 1; i < str_len; i++)
        {
            if(a[i] >= 48 && a[i] <= 57)
            {
                number->digits[i - 1] = a[i];
            }else
            {
                perror("Failed to initialize dynamic integer (wrong number format)");
                free_dint(number);
                return NULL;
            }
        }
    }else
    {   
        for(int i = 0; i < str_len; i++)
        {
            if(a[i] >= 48 && a[i] <= 57)
            {
                number->digits[i] = a[i];
            }else
            {
                perror("Failed to initialize dynamic integer (wrong number format)");
                free_dint(number);
                return NULL;
            }
        }
    }

    return number;
}

dfloat* dfloat_init(char a[])
{
    const int str_len = strlen(a);
    if(str_len > MAX_DIGIT_COUNT)
    {
        perror("Failed to initialize dynamic float (dynamic float (with precision) can't be greater than MAX_DIGIT_COUNT)");
        return NULL;
    }

    const byte is_signed_val = (a[0] == '-') ? 1 : 0;
    byte is_decimal = 1;

    dfloat* number = (dfloat* )malloc(sizeof(dfloat));
    number->is_signed = is_signed_val;
    number->decimal_size = 0;
    number->floating_size = 0;

    for(int i = (is_signed_val == 1) ? 1 : 0; i < str_len; i++)
    {
        if(is_decimal == 1 && a[i] == '.')
        {
            is_decimal = 0;
            continue;
        }
        if((is_decimal == 0 && a[i] == '.') || ((int)a[i] <= 47 && (int)a[i] >= 58))
        {
            perror("Failed to initialize dynamic float (wrong number format)");
            free(number);
            return NULL;
        }

        if(is_decimal == 1)
        {
            number->decimal_size++;
        }else
        {
            number->floating_size++;
        }
    }

    number->decimal_digits = malloc(sizeof(byte) * number->decimal_size);
    number->floating_digits = malloc(sizeof(byte) * number->floating_size);

    if(number->decimal_digits == NULL || number->floating_digits == NULL || number == NULL)
    {
        perror("Failed to initialize dynamic float (can't allocate more memory)");
        free_dfloat(number);
        return NULL;
    }

    int idx = 0;
    for(int i = ((is_signed_val) ? 1 : 0); i < (number->decimal_size + (is_signed_val == 1 ? 1 : 0)); i++)
    {
        if(a[i] >= 48 && a[i] <= 57)
        {
            number->decimal_digits[idx++] = a[i];
        }else
        {
            perror("Failed to initialize dynamic float (wrong number format)");
            free_dfloat(number);
            return NULL;
        }
    }

    idx = 0;
    for(int i = ((is_signed_val) ? 2 : 1) + number->decimal_size; i <= number->decimal_size + number->floating_size + (number->is_signed == 1 ? 1 : 0); i++)
    {
        if(a[i] >= 48 && a[i] <= 57)
        {
            number->floating_digits[idx++] = a[i];
        }else
        {
            perror("Failed to initialize dynamic float (wrong number format)");
            free_dfloat(number);
            return NULL;
        }
        
    }

    return number;
}

char* dint_to_str(dint* value)
{
    const int str_len = value->size + ((value->is_signed) ? 2 : 1);
    char* str = {0};
    str = (char* )malloc(sizeof(char) * str_len);
    if(str == NULL)
    {
        perror("Failed to convert dynamic integer to string (can't allocate more memory)");
        return NULL;
    }

    int start_index = 0;
    if(value->is_signed == 1)
    {
        start_index = 1;
        str[0] = '-';
    }

    for(int i = start_index; i < str_len; i++)
    {
        str[i] = *(value->digits + ((value->is_signed) ? i -1 : i));
    }

    str[str_len - 1] = '\0';

    return str;
}

char* dfloat_to_str(dfloat* value)
{   
    const int str_decimal_len = max(value->decimal_size, 1);
    const int str_float_len = value->floating_size;
    const int str_total_len = str_decimal_len + str_float_len + ((value->is_signed) ? 3 : 2);
    char* str = {0};
    str = (char* )malloc(sizeof(char) * str_total_len);

    int start_pos = 0;
    if(value->is_signed == 1)
    {
        start_pos = 1;
        str[0] = '-';
    }

    int idx = 0;
    for(int i = start_pos; i < str_decimal_len + start_pos; i++)
    {
        if(value->decimal_size == 0)
        {
            str[i] = '0';
            break;
        }
        str[i] = value->decimal_digits[(value->is_signed == 1) ? i-1 : i];
    }

    str[str_decimal_len + start_pos] = '.';
    idx = 0;
    for(int i = str_decimal_len + start_pos + 1; i < (str_decimal_len + start_pos + 1) + str_float_len; i++)
    {
        str[i] = value->floating_digits[idx++];
    }

    str[str_total_len - 1] = '\0';

    return str;
}

void free_dint(dint* ptr)
{
    free(ptr->digits);
    free(ptr);
    ptr = NULL;
}

void free_dfloat(dfloat* ptr)
{
    free(ptr->decimal_digits);
    free(ptr->floating_digits);
    free(ptr);
    ptr = NULL;
}

// void free_dstr(dstr* ptr)
// {

// }
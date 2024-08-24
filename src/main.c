#include <stdio.h>
#include "dynelm.h"
#include <stdlib.h>

int main()
{
    char str[1000];
    printf("Please enter a text: ");
    scanf("%s", str);

    dfloat* number = dfloat_init(str);
    if(number == NULL) return -1;

    printf("Number deciaml size: %i\n", number->decimal_size);
    printf("Number float size: %i\n", number->floating_size);
    printf("Number is signed: %i\n", number->is_signed);

    printf("===Number===\n");
    for(int i = 0; i < number->decimal_size; i++)
    {
        printf("%c", number->decimal_digits[i]);
    }
    printf(".");
    for(int i = 0; i < number->floating_size; i++)
    {
        printf("%c", number->floating_digits[i]);
    }
    printf("\n");

    char* ff = dfloat_to_str(number);

    printf("Number texted version is: %s,\n",ff);

    free(ff);
    free_dfloat(number);
    return 0;
}
#include "dynelm.h"
#include "dynio.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    //init_input_system();

    printf("Please enter a boolean: ");
    byte ans_bool = get_boolean_input();

    printf("\nPlease enter a string: ");
    char* ans_str = get_string_input();

    printf("\nPlease enter a char: ");
    char ans_char = get_char_input();

    printf("\nPlease enter int: ");
    dint* ans_int = get_int_input();

    printf("\nPlease enter float: ");
    dfloat* ans_float = get_float_input();

    printf("\nPlease enter a digit (0-9): ");
    byte ans_digit = get_digit_input();

    printf("\n\n\n1. %s\n", (ans_bool > 0) ? "True" : "False");
    printf("2. %s\n", ans_str);
    printf("3. %c\n", ans_char);
    printf("4. %s\n", dint_to_str(ans_int));
    printf("5. %s\n", dfloat_to_str(ans_float));
    printf("6. %i\n", ans_digit);

    free(ans_str);
    free(ans_int);
    free(ans_float);
    return 0;
}
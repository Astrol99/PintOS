#include "string.h"

int strlen(char *str)
{
    unsigned int length = 0;

    while (str[length] != '\0') // Go over string linearly until hitting null escape
        length++;
    
    return length;
}
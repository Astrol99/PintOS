#include "../drivers/output.h"
#include "../utils/string.h"

int kmain() 
{
    char test[] = "aaaaaaaaaaaaaaaaaaaa";

    write(test, strlen(test));

    return 0;
}
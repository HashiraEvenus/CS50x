#include <cs50.h>
#include <stdio.h>

int main(void)
{
    double x = get_int("x : ");
    double y = get_int("y : ");

    double z = x/y ;
    printf ( "%f\n", z);
}

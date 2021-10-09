#include <stdio.h>
#include "../get_next_line.c"

int main()
{
    int n;
    unsigned int u;
    char c;
    //char *str[5];
    char str[] = "test";
    int r; //result
    int ftr; //ft_ result
    int len;

    n = 123;
    u = 123567890;
    c = 'c';

    r = printf("%%\n");
    printf("r = %d and ftr = %d\n\n", r, ftr);
	return (0);
}

#include <stdio.h>
__attribute__((section("FOO"))) int global = 42;
__attribute__((section("BAR"))) void foo(){}
int
main(void)
{
    printf("Hello World\n");
    return 0;
}

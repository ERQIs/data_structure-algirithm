# include <stdio.h>

void hello(int p)
{
    if (p == 1){
        printf("hello, 1 !\n");
    } else {
        printf("hello there!\n");
    }
}

void driver(void (*f)(int p))
{
    f(1);
}

int main()
{
    driver(hello);
    return 0;
}
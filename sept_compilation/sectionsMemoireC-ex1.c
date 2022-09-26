/*
Les sections par ordre d'adresse croissant :

text
rodata
data
bss
tas
pile

La pile croit dans le sens des adresses decroissantes.
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t x = 32;
uint32_t y;

const char mesg_const[] = "Some text";
extern char _etext;
void f();
void g();

int main()
{
    uint32_t z;

    uint32_t *point;
    point = &x;
    printf("data \t %p\n", point);
    point = &y;
    printf("bss \t  %p\n", point);
    point = &z;
    printf("pile \t  %p\n", point);
    point = (uint32_t *)malloc(4);
    printf("tas \t %p\n", point);
    printf("rodata \t %p\n", mesg_const);
    printf("text \t %p\n", main);

    f();
}

void f()
{
    int a = 5;
    printf("premiere variable dans la pile en : %p\n", &a);
    g();
}

void g()
{
    int a = 5;
    printf("deuxieme variable dans la pile en : %p\n", &a);
}

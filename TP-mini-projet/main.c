#include <stdint.h>


int fibo(int n); //n-ieme nombre de la suite de Fibonacci

int number_in_bss;

int main(int argc, const char * argv[]) {
    number_in_bss = 2;
    return number_in_bss;
}

int fibo(int n) {
    /* Cette fonction calcule le n-ieme nombre de la suite de Fibonacci
    pour n un entier strictement positif */
    if (n < 3) {
        return 1;
    } else {
        return fibo(n-1)+fibo(n-2);
    } 
}
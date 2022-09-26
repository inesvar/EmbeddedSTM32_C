
int fibo(int n); //n-ieme nombre de la suite de Fibonacci

int main(int argc, const char * argv[]) {
    return fibo(8);
}

int fibo(int n) {
    if (n < 3) {
        return 1;
    } else {
        return fibo(n-1)+fibo(n-2);
    } 
}
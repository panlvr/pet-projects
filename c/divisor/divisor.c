#include <stdio.h>

int check(int n);
int modulo(int n, int div);
int division(int n, int div);
int even(int n);
int odd(int n, int div);

int main(void) {
    int x;
    char ch;
    int divisor = 3;
    if (scanf("%i", &x) != 1) {
        printf("n/a\n");
        return 0;
    }
    if (scanf("%c", &ch) == 1 && ch != '\n') {
        printf("n/a\n");
        return 0;
    }
    x = check(x);
    if (x == 0) {
        return 0;
    }
    x = even(x);
    if (x == 1) {
        printf("2\n");
        return 0;
    } else {
        x = odd(x, divisor);
        printf("%i\n", x);
        return 0;
    }
}

int check(int n) {
    if (n == -1 || n == 0 || n == 1) {
        printf("n/a\n");
        return 0;
    }
    if (n < -1) {
        n *= -1;
        return n;
    }
    return n;
}

int modulo(int n, int div) {
    while (n - div >= 0) {
        n -= div;
    }
    return n;
}

int division(int n, int div) {
    int cnt = 0;
    while (n - div >= 0) {
        n -= div;
        cnt++;
    }
    return cnt;
}

int even(int n) {
    while ((n & 1) == 0) {
        n >>= 1;
    }
    return n;
}

int odd(int n, int div) {
    int largest = n;
    while (div * div <= n) {
        while (modulo(n, div) == 0) {
            n = division(n, div);
            largest = div;
        }
        div += 2;
    }
    if (n > 1) {
        largest = n;
    }
    return largest;
}
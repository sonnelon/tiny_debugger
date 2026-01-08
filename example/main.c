#include <stdio.h>

static int
f (int a, int b);

int main () {
    int a = 1 + 1;
    int b = a + 1;
    int res = a + b;

    printf("%d", f(a, b));
}

static int
f (int a, int b) {
    if (a < 10) return b - a;
    return a * b;
}

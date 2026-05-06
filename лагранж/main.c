#include <stdio.h>
#include <math.h>

double lagr(double *x, double *f, double t, int n) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double mul = 1.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                mul *= (t - x[j]) / (x[i] - x[j]);
            }
        }
        result += f[i] * mul;
    }
    return result;
}

double factr(int n) {
    double a = 1.0;
    for (int i = 1; i <= n; i++) a *= i;
    return a;
}

void experiment(int n) {
    double x[n], f[n];
    
    for (int i = 0; i < n; i++) {
        x[i] = (double)i / (n - 1);
        f[i] = sin(x[i]);
    }

    double mdiff = 0.0;
    int M = 100000;
    for (int j = 0; j <= M; j++) {
        double t = (double)j / M;
        double cdiff = fabs(sin(t) - lagr(x, f, t, n));
        if (cdiff > mdiff) {
            mdiff = cdiff;
        }
    }

    double otsenka = 1.0 / (pow(2, n) * factr(n));

    printf("%ld | %le | %le\n", n, mdiff, otsenka);
}

int main() {
    int ns[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 17, 33, 65, 101};
    int amount = sizeof(ns) / sizeof(ns[0]);

    for (int i = 0; i < amount; i++) {
        experiment(ns[i]);
    }

    return 0;
}
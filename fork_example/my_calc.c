#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double sum(double a, double b) {
    return a + b;
}
double diff(double a, double b) {
    return a - b;
}
double get_res(double (*oper)(double, double), double* argumets, int len) {
    double res = 0;
    if (len > 0) {
        res = argumets[0];
        for (int i = 1; i < len; i++) {
            res = oper(res, argumets[i]);
        }
    }
    return res;
}
int main(int argc, char* argv[]) {
    int res, i = 0;
    double arguments[10];
    double (*oper)(double, double) = sum;
    while ((res = getopt(argc, argv, "a:sd")) != -1) {
        switch (res) {
            case 'a':
                arguments[i] = atof(optarg);
                i++;
                break;
            case 's':
                oper = sum;
                break;
            case 'd':
                oper = diff;
                break;
        }
    }
    printf("%lf\n", get_res(oper, arguments, i));
    exit(0);
}

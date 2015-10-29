#include <iostream>
#include <cstdlib>
#include <cmath>
#include "simpio.h"
#include "console.h"

using namespace std;

void GetCoefficients(double *a, double *b, double *c);
void SolveQuadratic(double a, double b, double c, double *x1, double *x2);
void PrintRoots(double x1, double x2);

int main()
{
    double a, b, c, r1, r2;
    double *pa, *pb, *pc, *pr1, *pr2;

    pa = &a;
    pb = &b;
    pc = &c;
    pr1 = &r1;
    pr2 = &r2;

    GetCoefficients(pa, pb, pc);
    SolveQuadratic(*pa, *pb, *pc, pr1, pr2);
    PrintRoots(*pr1, *pr2);

    return 0;
}

void GetCoefficients(double *a, double *b, double *c)
{
    *a = getReal("a:");
    *b = getReal("b:");
    *c = getReal("c:");
}

void SolveQuadratic(double a, double b, double c, double *x1, double *x2)
{
    double disc = b * b - 4 * a * c;
    double sqrt_disc = sqrt(disc);

    *x1 = (-b + sqrt_disc) / (2 * a);
    *x2 = (-b - sqrt_disc) / (2 * a);
}

void PrintRoots(double x1, double x2)
{
    cout << "Roots are " << x1 << " and " << x2 << endl;
}

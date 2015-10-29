#include <iostream>
#include <cmath>
#include "console.h"
#include "simpio.h"
#include "gwindow.h"
#include "random.h"

using namespace std;

GPoint DrawFractalCoastline(GWindow& gw, int n, GPoint pt, double r, double theta);

int main()
{
    GWindow gw;
    GPoint pt(gw.DEFAULT_WIDTH / 4, gw.DEFAULT_HEIGHT / 2);

    while(true)
    {
        int n = getInteger("Enter n");
        gw.clear();
        DrawFractalCoastline(gw, n, pt, gw.DEFAULT_WIDTH / 2, 0);
    }

    return 0;
}

GPoint DrawFractalCoastline(GWindow& gw, int n, GPoint pt, double r, double theta)
{
    if (n < 1)
    {
        return gw.drawPolarLine(pt, r, theta);
    }

    int side = (randomChance(0.5)) ? 1 : -1;

    pt = DrawFractalCoastline(gw, n-1, pt, r / 3, theta);
    pt = DrawFractalCoastline(gw, n-1, pt, r / 3, theta + (60 * side));
    pt = DrawFractalCoastline(gw, n-1, pt, r / 3, theta - (60 * side));
    return DrawFractalCoastline(gw, n-1, pt, r / 3, theta);
}

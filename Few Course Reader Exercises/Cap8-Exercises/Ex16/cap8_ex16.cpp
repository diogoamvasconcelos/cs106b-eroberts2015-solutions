#include <iostream>
#include <cmath>
#include "console.h"
#include "simpio.h"
#include "gwindow.h"
#include "random.h"

using namespace std;

double SIZE = 100;

void DrawHFractal(GWindow& gw, GPoint pt, double size, int order);

int main()
{
    GWindow gw;
    GPoint pt(gw.DEFAULT_WIDTH / 2, gw.DEFAULT_HEIGHT / 2);

    while(true)
    {
        int n = getInteger("Enter n");
        gw.clear();
        DrawHFractal(gw, pt, SIZE, n);
    }

    return 0;
}

void DrawHFractal(GWindow& gw, GPoint pt, double size, int order)
{
    //Get H corners to draw the smaller H's
    GPoint h0(pt.getX() - size / 2, pt.getY() - size / 2);
    GPoint h1(pt.getX() - size / 2, pt.getY() + size / 2);
    GPoint h2(pt.getX() + size / 2, pt.getY() - size / 2);
    GPoint h3(pt.getX() + size / 2, pt.getY() + size / 2);

    //If not the last order, create the smaller H's
    if(order > 0)
    {
          DrawHFractal(gw, h0, size / 2, order - 1);
          DrawHFractal(gw, h1, size / 2, order - 1);
          DrawHFractal(gw, h2, size / 2, order - 1);
          DrawHFractal(gw, h3, size / 2, order - 1);
    }

    //Draw the H
    GPoint h01(pt.getX() - size / 2, pt.getY());
    GPoint h23(pt.getX() + size / 2, pt.getY());

    gw.drawLine(h01, h23);
    gw.drawLine(h0, h1);
    gw.drawLine(h2, h3);
}

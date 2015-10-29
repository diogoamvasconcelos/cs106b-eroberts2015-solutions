#include <iostream>
#include "console.h"
#include "simpio.h"
#include "gwindow.h"
#include "random.h"

using namespace std;

void DrawInch(GWindow& gw, double inch_tick, double seg_start, double seg_end);

const double HALF_INCH_TICK = 0.2;
const int NUMBER_OF_SEGMENTS = 8;

int main()
{
    GWindow gw;

    gw.drawLine(0, 0, gw.DEFAULT_WIDTH, 0);
    DrawInch(gw, HALF_INCH_TICK * gw.DEFAULT_HEIGHT, 0.0, gw.DEFAULT_WIDTH);

    return 0;
}

void DrawInch(GWindow& gw, double inch_tick, double seg_start, double seg_end)
{
    if(inch_tick < (HALF_INCH_TICK * gw.DEFAULT_HEIGHT) / NUMBER_OF_SEGMENTS)
         return;

    double x_pos = (seg_start + seg_end) / 2;
    gw.drawLine(x_pos, 0, x_pos, inch_tick);

    DrawInch(gw, inch_tick / 2, seg_start, x_pos);
    DrawInch(gw, inch_tick / 2, x_pos, seg_end);
}



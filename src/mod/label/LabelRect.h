#pragma once

#include "mc/deps/input/RectangleArea.h"

namespace bps::label {

class LabelRect {

public:
    LabelRect(int x, int y, int w, int h, bool center);

    int getX();
    int getY();
    int getW();
    int getH();

    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);

    ::RectangleArea& getMcRect();

private:
    int mX;
    int mY;
    int mW;
    int mH;
    bool mCenter;

    ::RectangleArea mMcRect;

    void syncMcRect();

};

}
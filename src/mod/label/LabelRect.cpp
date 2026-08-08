#include "mod/label/LabelRect.h"
#include "ll/api/service/TargetedBedrock.h"
#include "mc/client/game/ClientInstance.h"
#include "mc/deps/core/math/Vec2.h"
#include "mc/deps/input/RectangleArea.h"    
#include "mc/deps/renderer/ViewportInfo.h"

namespace bps::label {

LabelRect::LabelRect(int x, int y, int w, int h, bool center) :
    mX(x), mY(y), mW(w), mH(h), mCenter(center),
    mMcRect(0, 0, 0, 0, false) {
    syncMcRect();
}

int LabelRect::getX() { return mX; }
int LabelRect::getY() { return mY; }
int LabelRect::getW() { return mW; }
int LabelRect::getH() { return mH; }

void LabelRect::setX(int x) { mX = x; syncMcRect(); }
void LabelRect::setY(int y) { mY = y; syncMcRect(); }
void LabelRect::setW(int w) { mW = w; syncMcRect(); }
void LabelRect::setH(int h) { mH = h; syncMcRect(); }

::RectangleArea& LabelRect::getMcRect() {
    return mMcRect;
}

void LabelRect::syncMcRect() {
    if (mCenter) {
        ClientInstance& mc = ll::service::getClientInstance();
        float scale = mc.getGuiScale();
        float cX = (mc.getViewportInfo().size->x / scale) / 2 + mX;
        float cY = (mc.getViewportInfo().size->y / scale) / 2 + mY;
        float halfW = mW / 2;
        float halfH = mH / 2;
        mMcRect.set(
            cX - halfW,
            cY - halfH,
            cX + halfW,
            cY + halfH
        );
    } else {
        mMcRect.set(
            mX,
            mY,
            mX + mW,
            mY + mH
        );
    }
}

}
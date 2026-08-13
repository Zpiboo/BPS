#pragma once

#include "mc/world/actor/Actor.h"

namespace bps::speedrun {

class SpeedrunTickListener {

public:
    static void onTick(::Actor* cameraActor);

    static int getGroundtime();
    static int getRunTicks();

private:
    static bool mWasWasOnGround;
    static bool mWasOnGround;
    static bool mIsOnGround;

    static bool mWasMoving;
    static bool mIsMoving;

    static int mGroundtime;
    static int mRunTicks;

};

}
#pragma once

#include "mc/world/actor/Actor.h"

namespace bps::speedrun {

class SpeedrunTickListener {

public:
    static void onTick(::Actor* cameraActor);

};

}
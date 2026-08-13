#include "mod/speedrun/SpeedrunTickListener.h"
#include "ll/api/service/TargetedBedrock.h"
#include "mc/client/game/ClientInstance.h"
#include "mc/client/input/ClientMoveInputHandler.h"
#include "mc/client/player/LocalPlayer.h"
#include "mc/deps/core/math/Vec2.h"
#include "mc/entity/components/MoveInputComponent.h"
#include "mc/world/actor/provider/PlayerMoveInput.h"
#include "mc/world/actor/Actor.h"

namespace bps::speedrun {

bool SpeedrunTickListener::mWasWasOnGround;
bool SpeedrunTickListener::mWasOnGround;
bool SpeedrunTickListener::mIsOnGround;

bool SpeedrunTickListener::mWasMoving;
bool SpeedrunTickListener::mIsMoving;

int SpeedrunTickListener::mGroundtime;
int SpeedrunTickListener::mRunTicks;

void SpeedrunTickListener::onTick(::Actor* cameraActor) {
    mWasWasOnGround = mWasOnGround;
    mWasOnGround = mIsOnGround;
    mIsOnGround = cameraActor->isOnGround();

    if (mIsOnGround) {
        if (mWasOnGround)
            mGroundtime++;
        else
            mGroundtime = 0;
    }

    mWasMoving = mIsMoving;

    ::Actor* localPlayer = static_cast<::Actor*>(ll::service::getClientInstance()->getLocalPlayer());
    if (cameraActor == localPlayer) {
        ClientInstance& mc = ll::service::getClientInstance();
        auto& inputComponent = *::ClientMoveInputHandler::getMoveInput(mc);

        mIsMoving = *inputComponent.mMove != Vec2::ZERO();
    } else {
        mIsMoving = false;
        mRunTicks = mGroundtime;
    }

    if (mWasOnGround) {
        if (mIsMoving) {
            if (mWasMoving)
                mRunTicks++;
            if (!mWasWasOnGround || !mWasMoving)
                mRunTicks = 0;
        } else if (mWasWasOnGround && mWasMoving) {
            mRunTicks++;
        }
    }
}

int SpeedrunTickListener::getGroundtime() {
    return mGroundtime;
}

int SpeedrunTickListener::getRunTicks() {
    return mRunTicks;
}

}
#pragma once

#include "ll/api/event/world/LevelEvent.h"
#include "mc/client/game/ClientInstance.h"

namespace bps::event {

class ClientLevelTickEndEvent final : public ll::event::LevelEvent {

public:
    constexpr explicit ClientLevelTickEndEvent(Level& level) : LevelEvent(level) {}

};

}
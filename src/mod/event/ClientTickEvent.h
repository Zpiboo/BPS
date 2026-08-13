#pragma once

#include "ll/api/event/Event.h"
#include "mc/client/game/ClientInstance.h"

namespace bps::event {

class ClientTickEvent final : public ll::event::Event {
    
public:
    enum class Phase { Start, End };

private:
    ClientInstance& mClient;
    Phase mPhase;

public:
    constexpr explicit ClientTickEvent(ClientInstance& client, Phase phase) : mClient(client), mPhase(phase) {}

    void serialize(CompoundTag&) const override;

    [[nodiscard]] ClientInstance& client() const;
    [[nodiscard]] Phase phase() const;

};

}
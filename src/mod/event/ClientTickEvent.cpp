#include "mod/event/ClientTickEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/Event.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/EventRefObjSerializer.h"
#include "ll/api/memory/Hook.h"
#include "ll/api/service/TargetedBedrock.h"
#include "mc/client/game/ClientInstance.h"
#include "mc/deps/nbt/CompoundTag.h"

namespace bps::event {

ClientInstance& ClientTickEvent::client() const {
    return mClient;
}
ClientTickEvent::Phase ClientTickEvent::phase() const {
    return mPhase;
}

void ClientTickEvent::serialize(CompoundTag& nbt) const {
    Event::serialize(nbt);
    nbt["client"] = ll::event::serializeRefObj(client());
    nbt["phase"] = CompoundTagVariant(
        std::string_view(phase() == ClientTickEvent::Phase::Start
            ? "Start"
            : "End"
        )
    );
}

LL_TYPE_INSTANCE_HOOK(ClientTickEndEventHook, HookPriority::Normal, ClientInstance, &ClientInstance::$onTick, void, int nTick, int maxTick) {
    ClientInstance& client = ll::service::getClientInstance();

    ll::event::EventBus::getInstance().publish(ClientTickEvent(client, ClientTickEvent::Phase::Start));
    origin(nTick, maxTick);
    ll::event::EventBus::getInstance().publish(ClientTickEvent(client, ClientTickEvent::Phase::End));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory();
class ClientTickEventEmitter : public ll::event::Emitter<emitterFactory, ClientTickEvent> {
    ll::memory::HookRegistrar<ClientTickEndEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory() { return std::make_unique<ClientTickEventEmitter>(); }

}
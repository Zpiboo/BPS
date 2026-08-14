#include "mod/event/ClientLevelTickEndEvent.h"
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/memory/Hook.h"
#include "mc/client/multiplayer/MultiPlayerLevel.h"
#include "mc/client/game/ClientInstance.h"

namespace bps::event {

LL_TYPE_INSTANCE_HOOK(ClientTickEndEventHook, HookPriority::Normal, MultiPlayerLevel, &MultiPlayerLevel::$_subTick, void) {
    origin();
    ll::event::EventBus::getInstance().publish(ClientLevelTickEndEvent(*this));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory();
class ClientTickEventEmitter : public ll::event::Emitter<emitterFactory, ClientLevelTickEndEvent> {
    ll::memory::HookRegistrar<ClientTickEndEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory() { return std::make_unique<ClientTickEventEmitter>(); }

}
#include "mod/BPS.h"

#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/command/ClientCommandRegisterEvent.h"
#include "ll/api/event/render/UIRenderEvent.h"
#include "ll/api/mod/RegisterHelper.h"
#include "mc/client/game/ClientInstance.h"
#include "mc/client/game/IClientInstance.h"
#include "mc/world/actor/Actor.h"
#include "mod/label/Label.h"
#include "mod/label/LabelRegistry.h"
#include <array>
#include <memory>
#include <string>

namespace bps {

BPS& BPS::getInstance() {
    static BPS instance;
    return instance;
}

bool BPS::load() {
    getSelf().getLogger().debug("Loading...");

    return true;
}

bool BPS::enable() {
    auto& logger = getSelf().getLogger();
    logger.debug("Enabling...");

    using namespace ll::event;
    auto& bus = EventBus::getInstance();

    bus.emplaceListener<command::ClientCommandRegisterEvent>(
        [](command::ClientCommandRegisterEvent&) {

            auto& command = ll::command::CommandRegistrar::getInstance(true)
                .getOrCreateCommand("bps", "Do you deserve the legacy of DinoPK Optimized? Do you have what it takes?");
            
            command.overload().execute(
                [](CommandOrigin const& origin, CommandOutput& output) {
                    auto* entity = origin.getEntity();

                    if (entity == nullptr || !entity->isPlayer()) {
                        output.error(
                            "Only players can expand their consciousness by x10,000"
                        );
                        return;
                    }

                    //auto* player = static_cast<Player*>(entity);

                    output.success("Expanded your consciousness by x10,000");
                }
            );
        }
    );

    bus.emplaceListener<render::BeforeUIRenderEvent>(
        [](render::BeforeUIRenderEvent& evt) {
            auto& ctx = evt.uiRenderContext();
            if (!ctx.mClient.isInWorldAndNotShowingAnyMenuScreens()) return;

            auto yawLabel = label::LabelRegistry::get("yaw");
            yawLabel->render(ctx);
        }
    );

    std::shared_ptr<label::Label> yawLabel = std::make_shared<label::Label>(
        "Yaw",
        [](::Actor* cameraActor) {
            return std::to_string(cameraActor->getRotation().y);
        },
        "no",
        std::array<int, 2> {0, 0},
        true
    );
    label::LabelRegistry::put("yaw", yawLabel);

    return true;
}

bool BPS::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace bps

LL_REGISTER_MOD(bps::BPS, bps::BPS::getInstance());

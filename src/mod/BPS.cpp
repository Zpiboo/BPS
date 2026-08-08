#include "mod/BPS.h"

#include "ll/api/command/CommandHandle.h"
#include "ll/api/command/CommandRegistrar.h"
#include "ll/api/event/EventBus.h"
#include "ll/api/event/command/ClientCommandRegisterEvent.h"
#include "ll/api/event/render/UIRenderEvent.h"
#include "ll/api/mod/RegisterHelper.h"
#include "mc/client/game/IClientInstance.h"
#include "mc/client/gui/CaretMeasureData.h"
#include "mc/client/gui/TextMeasureData.h"
#include "mc/deps/core/math/Color.h"
#include "mc/deps/input/RectangleArea.h"
#include "mc/server/commands/CommandFlag.h"

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
        [&logger](command::ClientCommandRegisterEvent&) {

            auto& command = ll::command::CommandRegistrar::getInstance(true)
                .getOrCreateCommand("bps", "Do you deserve the legacy of DinoPK Optimized? Do you have what it takes?");
            
            command.overload().execute(
                [&logger](CommandOrigin const& origin, CommandOutput& output) {
                    auto* entity = origin.getEntity();

                    if (entity == nullptr || !entity->isPlayer()) {
                        output.error(
                            "Only players can expand their consciousness by x10,000"
                        );
                        return;
                    }

                    auto* player = static_cast<Player*>(entity);

                    output.success("Expanded your consciousness by x10,000");
                }
            );
        }
    );

    bus.emplaceListener<render::BeforeUIRenderEvent>(
        [&logger](render::BeforeUIRenderEvent& evt) {
            auto& ctx = evt.uiRenderContext();

            auto& mc = ctx.mClient;
            if (!mc.isInWorldAndNotShowingAnyMenuScreens()) return;

            auto& font = mc.getFontHandle().getFont();
            RectangleArea rect(20, 50, 0, 0, true);
            auto& color = mce::Color::CYAN();
            auto alignment = ui::TextAlignment::Left;
            TextMeasureData textData(1, 0, true, false, true, alignment);
            CaretMeasureData caretData(0, false);

            ctx.drawText(font, rect, std::string("human is unlimited"), color, 1.0, alignment, textData, caretData);
        }
    );

    return true;
}

bool BPS::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace bps

LL_REGISTER_MOD(bps::BPS, bps::BPS::getInstance());

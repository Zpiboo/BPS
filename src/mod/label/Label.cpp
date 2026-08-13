#include "mod/label/Label.h"
#include "mc/client/game/IClientInstance.h"
#include "mc/client/gui/CaretMeasureData.h"
#include "mc/client/gui/Font.h"
#include "mc/client/gui/TextMeasureData.h"
#include "mc/client/renderer/screen/MinecraftUIRenderContext.h"
#include "mc/world/actor/Actor.h"
#include <string>

namespace bps::label {

Label::Label(
    std::string_view prefix,
    std::function<std::string(::Actor*)> valueGetter,
    std::array<int, 2> pos,
    bool center
)
    : mPrefix(prefix), mValueGetter(valueGetter),
    mRect(pos[0], pos[1], 0, 0, center) {
}

std::string Label::getValue(::Actor* cameraActor) {
    return mValueGetter(cameraActor);
}

void Label::render(MinecraftUIRenderContext& ctx) {
    auto& mc = ctx.mClient;

    ::Actor* cameraActor = mc.getCameraActor();
    std::string text = "§b" + mPrefix + ": §f" + getValue(cameraActor);

    Font& font = mc.getFontHandle().getFont();
    // TODO: update/render pipeline to update this in a proper place
    mRect.setW(font.getLineLength(text, 1, false));
    mRect.setH(font.getTextHeight(text, 1));

    auto& rect = mRect.getMcRect();
    auto& color = mce::Color::WHITE();
    auto alignment = ui::TextAlignment::Left;
    TextMeasureData textData(1, 0, true, false, true, alignment);
    CaretMeasureData caretData(0, false);

    ctx.drawText(font, rect, std::string(text), color, 1.0, alignment, textData, caretData);
}

}
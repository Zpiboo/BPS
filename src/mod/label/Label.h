#pragma once

#include "mc/client/renderer/screen/MinecraftUIRenderContext.h"
#include "mc/world/actor/Actor.h"
#include "mod/label/LabelRect.h"

namespace bps::label {

class Label {

public:
    Label(
        std::string_view prefix,
        std::function<std::string(::Actor*)> valueGetter,
        std::array<int, 2> pos,
        bool center
    );

    std::string getValue(::Actor* cameraActor);

    void render(MinecraftUIRenderContext& ctx);

private:
    std::string mPrefix;
    std::function<std::string(::Actor*)> mValueGetter;

    label::LabelRect mRect;

};

}
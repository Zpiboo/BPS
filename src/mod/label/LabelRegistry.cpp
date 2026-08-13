#include "mod/label/LabelRegistry.h"
#include "mod/label/Label.h"

namespace bps::label {

std::unordered_map<std::string, std::shared_ptr<Label>> LabelRegistry::mRegistry;

void LabelRegistry::put(const std::string& id, std::shared_ptr<Label> label) {
    mRegistry.insert_or_assign(id, label);
}

std::shared_ptr<Label> LabelRegistry::get(const std::string& id) {
    return mRegistry[id];
}

bool LabelRegistry::exists(const std::string& id) {
    return mRegistry.contains(id);
}

void LabelRegistry::renderAll(MinecraftUIRenderContext& ctx) {
    for (const auto& [id, label] : mRegistry) {
        label->render(ctx);
    }
}

}
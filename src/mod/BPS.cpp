#include "mod/BPS.h"

#include "ll/api/mod/RegisterHelper.h"

namespace bps {

BPS& BPS::getInstance() {
    static BPS instance;
    return instance;
}

bool BPS::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    return true;
}

bool BPS::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool BPS::disable() {
    getSelf().getLogger().debug("Disabling...");
    // Code for disabling the mod goes here.
    return true;
}

} // namespace bps

LL_REGISTER_MOD(bps::BPS, bps::BPS::getInstance());

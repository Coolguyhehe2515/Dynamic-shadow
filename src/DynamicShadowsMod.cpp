#include "DynamicShadowsMod.h"

#include "render/RenderHooks.hpp"

DynamicShadowsMod::DynamicShadowsMod()
    : mSelf(*ll::mod::NativeMod::current()) {}

DynamicShadowsMod& DynamicShadowsMod::instance() {
    static DynamicShadowsMod instance;
    return instance;
}

bool DynamicShadowsMod::load() {
    getSelf().getLogger().info("Dynamic Shadows loading...");
    return true;
}

bool DynamicShadowsMod::enable() {
    getSelf().getLogger().info("Dynamic Shadows enabling...");

    if (!dynamicshadows::render::install()) {
        getSelf().getLogger().error(
            "Failed to install RenderLevel hook."
        );
        return false;
    }

    return true;
}

bool DynamicShadowsMod::disable() {
    dynamicshadows::render::uninstall();
    getSelf().getLogger().info("Dynamic Shadows disabled.");
    return true;
}

bool DynamicShadowsMod::unload() {
    dynamicshadows::render::uninstall();
    return true;
}

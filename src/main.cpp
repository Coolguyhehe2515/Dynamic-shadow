#include <pl/Mod.hpp>

#include "render/RenderHooks.hpp"

class DynamicShadowsMod : public ll::mod::NativeMod {
private:
    ll::mod::NativeMod& mSelf;

public:
    DynamicShadowsMod()
        : mSelf(*ll::mod::NativeMod::current()) {}

    bool load() override {
        getSelf().getLogger().info("DynamicShadows loading...");
        return true;
    }

    bool enable() override {
        getSelf().getLogger().info("DynamicShadows enabling...");

        if (!dynamicshadows::render::install()) {
            getSelf().getLogger().error(
                "Failed to install RenderLevel hook."
            );
            return false;
        }

        return true;
    }

    bool disable() override {
        dynamicshadows::render::uninstall();
        getSelf().getLogger().info("DynamicShadows disabled.");
        return true;
    }

    bool unload() override {
        dynamicshadows::render::uninstall();
        return true;
    }
};

PL_REGISTER_MOD(
    DynamicShadowsMod,
    std::make_unique<DynamicShadowsMod>()
);

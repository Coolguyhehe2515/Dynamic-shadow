#include <pl/Mod.hpp>

#include "render/RenderHooks.hpp"

class DynamicShadowsMod : public ll::mod::NativeMod {
public:
    DynamicShadowsMod()
        : NativeMod(*NativeMod::current()) {}

    bool load() override {
        return true;
    }

    bool enable() override {
        if (!dynamicshadows::render::install()) {
            return false;
        }

        return true;
    }

    bool disable() override {
        dynamicshadows::render::uninstall();
        return true;
    }

    bool unload() override {
        dynamicshadows::render::uninstall();
        return true;
    }
};

PL_REGISTER_MOD(
    DynamicShadowsMod,
    DynamicShadowsMod()
);

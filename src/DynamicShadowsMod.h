#pragma once

#include <pl/Mod.hpp>

class DynamicShadowsMod : public ll::mod::NativeMod {
public:
    static DynamicShadowsMod& instance();

    DynamicShadowsMod();

    bool load() override;
    bool enable() override;
    bool disable() override;
    bool unload() override;

private:
    ll::mod::NativeMod& mSelf;
};

#include "RenderHooks.hpp"

#include <pl/memory/Hook.hpp>
#include <pl/memory/Signature.hpp>

#include <android/log.h>

#include <atomic>
#include <cstdint>
#include <mutex>

namespace dynamicshadows::render {

namespace {

constexpr char LOG_TAG[] = "DynamicShadows";

std::mutex gMutex;
void* gRenderLevelTarget = nullptr;
void* gRenderLevelOriginal = nullptr;
bool gInstalled = false;

std::atomic<std::uint64_t> gRenderLevelCalls{0};

using RenderLevelFn = void(*)(
    void*,
    void*,
    void*,
    void*,
    void*,
    void*,
    void*,
    void*
);

RenderLevelFn renderLevelOriginal = nullptr;

void renderLevelDetour(
    void* a0,
    void* a1,
    void* a2,
    void* a3,
    void* a4,
    void* a5,
    void* a6,
    void* a7
) {
    gRenderLevelCalls.fetch_add(1, std::memory_order_relaxed);

    if (renderLevelOriginal) {
        renderLevelOriginal(
            a0,
            a1,
            a2,
            a3,
            a4,
            a5,
            a6,
            a7
        );
    }
}

}

bool install() {
    std::lock_guard lock(gMutex);

    if (gInstalled) {
        return true;
    }

    __android_log_print(
        ANDROID_LOG_INFO,
        LOG_TAG,
        "Render hook initialization."
    );

    return false;
}

void uninstall() {
    std::lock_guard lock(gMutex);

    if (!gInstalled) {
        return;
    }

    if (gRenderLevelTarget) {
        pl::memory::unhook(
            gRenderLevelTarget,
            reinterpret_cast<void*>(renderLevelDetour)
        );
    }

    gRenderLevelTarget = nullptr;
    gRenderLevelOriginal = nullptr;
    renderLevelOriginal = nullptr;
    gInstalled = false;

    __android_log_print(
        ANDROID_LOG_INFO,
        LOG_TAG,
        "Render hook removed."
    );
}

}

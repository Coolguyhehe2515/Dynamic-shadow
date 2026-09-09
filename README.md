# Dynamic Shadows

A native Minecraft Bedrock Android mod for dynamic shadow rendering.

## Goal

Dynamic Shadows adds real-time world shadows without replacing the RenderDragon shader or requiring a resource pack.

## Target

- Minecraft Bedrock Android
- ARM64
- LeviLauncher
- Preloader Android
- RenderDragon
- Initial shadow map: 150x150

## Development

Requirements:

- Android SDK
- Android NDK 28.2.13676358
- CMake 3.22+
- Ninja

Build:

```bash
cmake -S . -B build \
  -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake" \
  -DANDROID_ABI=arm64-v8a \
  -DANDROID_PLATFORM=android-28 \
  -DANDROID_STL=c++_shared \
  -DMOD_ID=dynamic_shadows \
  -DMOD_NAME="Dynamic Shadows" \
  -DMOD_AUTHOR="KrispyBRN" \
  -DMOD_VERSION=0.1.0 \
  -DMOD_LIBRARY_NAME=dynamic_shadows

cmake --build build

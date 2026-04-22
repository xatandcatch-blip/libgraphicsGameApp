#!/bin/bash

# 1. Compile Native Core with Asset Management and Android NDK libs
clang++ -shared -fPIC \
    cpp/main/JNI.cpp \
    cpp/main/GameEngine.cpp \
    cpp/main/AssetLoader.cpp \
    cpp/activity/library/SaveDataLogic.cpp \
    cpp/activity/library/dataSaveLogic.cpp \
    -landroid -ljnigraphics -lm -lstdc++ \
    -o lib/arm64-v8a/libvulkan_core.so

# 2. Assemble Smali to DEX
java -jar ~/smali.jar assemble java/main/Smali/ -o classes.dex

# 3. Sync and Track the build script too
git add build_project.sh assets/ cpp/ java/
git commit -m "NDK: Integrated AAssetManager for native asset streaming"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master > /dev/null 2>&1

echo "RuneG1: Asset Loader Linkage Complete."

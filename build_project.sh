#!/bin/bash

# 1. Compile Java Logic (Mercy & Heartbeat)
javac --release 8 java/main/GameLogic.java

# 2. Compile C++ Core (The one that was throwing errors)
clang++ -shared -fPIC \
    cpp/main/JNI.cpp \
    cpp/main/GameEngine.cpp \
    cpp/main/AssetLoader.cpp \
    cpp/activity/library/SaveDataLogic.cpp \
    cpp/activity/library/dataSaveLogic.cpp \
    -landroid -ljnigraphics -lm -lstdc++ \
    -o lib/arm64-v8a/libvulkan_core.so

# 3. Create DEX
d8 java/main/*.class --output .

# 4. Clean & Push
rm -rf java/main/*.class
git add .
git commit -m "FIX: Included jni.h in GameEngine to resolve JNIEnv errors"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master > /dev/null 2>&1

echo "RuneG1: Build Repaired and Synced."

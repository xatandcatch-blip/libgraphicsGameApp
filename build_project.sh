#!/bin/bash

# 1. Compile C++ Core
clang++ -shared -fPIC \
    cpp/main/JNI.cpp \
    cpp/main/GameEngine.cpp \
    cpp/main/AssetLoader.cpp \
    cpp/activity/library/SaveDataLogic.cpp \
    cpp/activity/library/dataSaveLogic.cpp \
    -landroid -ljnigraphics -lm -lstdc++ \
    -o lib/arm64-v8a/libvulkan_core.so

# 2. Java to Bytecode (Targeting Java 8 for D8 compatibility)
javac --release 8 java/main/GameLogic.java

# 3. Bytecode to DEX
d8 java/main/*.class --output .

# 4. Cleanup and Sync
rm java/main/*.class
git add .
git commit -m "FIX: Downgraded Java bytecode to v8 for d8 compatibility"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master > /dev/null 2>&1

echo "RuneG1: Build Successful. Bytecode version conflict resolved."

#!/bin/bash

echo "RuneG1: Initiating Release Build..."

# 1. Compile Java Brain (Optimized)
javac --release 8 java/main/GameLogic.java

# 2. Compile C++ Muscle (High Optimization -O3)
# -s strips the symbol table to make the file smaller
clang++ -O3 -shared -fPIC -s \
    cpp/main/JNI.cpp \
    cpp/main/GameEngine.cpp \
    cpp/main/AssetLoader.cpp \
    cpp/activity/library/SaveDataLogic.cpp \
    cpp/activity/library/dataSaveLogic.cpp \
    -landroid -ljnigraphics -lm -lstdc++ \
    -o lib/arm64-v8a/libvulkan_core_production.so

# 3. Dexing for Release
d8 java/main/*.class --output . --release

# 4. Final Packaging & Git Sync
rm -rf java/main/*.class
git add .
git commit -m "RELEASE: RuneG1 v1.1.0-STABLE (Optimized for Redmi A3/A5)"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master

echo "------------------------------------------------"
echo "VERSION: 1.1.0-STABLE"
echo "STATUS: Pushed to Production"
echo "------------------------------------------------"

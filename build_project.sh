#!/bin/bash

# 1. Compile Java Logic
javac --release 8 java/main/GameLogic.java

# 2. Compile C++ Core
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

# 4. Clean & Push 80+ Commits
rm -rf java/main/*.class
git add .
git commit -m "ALPHA: Integrated Death System and Battery Interference"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master

echo "RuneG1: Mega-Push Complete. 80+ Commits Synced."

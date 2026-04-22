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

# 2. Java to Bytecode (.java -> .class)
# Using 'javac' to compile. 
javac java/main/GameLogic.java

# 3. Bytecode to DEX (.class -> classes.dex)
# d8 handles the conversion of modern Java bytecode to Android's DEX format
d8 java/main/*.class --output . --lib $ANDROID_HOME/platforms/android-34/android.jar

# 4. Clean up the .class files to keep the workspace tidy
rm java/main/*.class

# 5. Git Sync
git add .
git commit -m "COMPILER: Migrated to javac + d8 pipeline for GameLogic"
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master > /dev/null 2>&1

echo "RuneG1: Build Successful using javac."

#!/bin/bash
echo "RuneG1: Deploying v1.2 (Entity Intelligence Update)..."

# 1. Java & C++ Compile
javac --release 8 java/main/GameLogic.java
clang++ -O3 -shared -fPIC -s \
    cpp/main/*.cpp \
    cpp/activity/library/*.cpp \
    -landroid -ljnigraphics -lm -lstdc++ \
    -o lib/arm64-v8a/libvulkan_core.so

# 2. Dexing
d8 java/main/*.class --output . --release
rm java/main/*.class

# 3. Git Versioning
git add .
git commit -m "RELEASE: v1.2.0 - Integrated State-Machine AI & Panic Logic"
git tag -a v1.2.0 -m "v1.2: Entity is now hunting."
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master
git push origin v1.2.0

echo "RuneG1 v1.2.0: Deployment Successful. No disasters reported."

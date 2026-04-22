#!/bin/bash

# 1. Identity Check
git config user.name "xatandcatch-blip"
git config user.email "xatandcatch-blip@users.noreply.github.com"
REPO_URL="https://github.com/xatandcatch-blip/libgraphicsGameApp.git"

# 2. Compile Architects if they don't exist
[ ! -f "./gen_res" ] && g++ gen_res.cpp -o gen_res
[ ! -f "./make_data" ] && g++ make_data.cpp -o make_data

# 3. Generate Resources (Static World)
# This writes the game_resources.arsc
./gen_res

# 4. Generate Player Data (Dynamic Save)
# Only creates data.cpp if it's missing (First Play)
if [ ! -f "data.cpp" ]; then
    ./make_data 100 1 0 100
fi

# 5. Native Compilation for Redmi (ARM64)
mkdir -p lib/arm64-v8a
clang++ -shared -fPIC data.cpp -o lib/arm64-v8a/libdata.so

# 6. Force Sync Everything to GitHub
git add .
git commit -m "CORE: Full Engine Reconstruction (Res + Data) - $(date +%T)" --allow-empty
git push -f $REPO_URL master > /dev/null 2>&1

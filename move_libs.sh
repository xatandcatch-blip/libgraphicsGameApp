#!/bin/bash
# 1. Create Architecture Folders
mkdir -p lib/arm64-v8a
mkdir -p lib/armeabi-v7a

# 2. Compile the Native Core (Large Code)
# Ensuring the binary is built first
clang++ -shared -fPIC data.cpp -o libdata.so

# 3. The Migration (Moving without .so extension)
if [ -f "libdata.so" ]; then
    echo "Syncing Libraries..."
    cp libdata.so lib/arm64-v8a/libdata
    mv libdata.so lib/armeabi-v7a/libdata
    echo "Success: Libraries moved to lib/ paths."
else
    echo "Error: libdata.so was not built. Check data.cpp for errors."
fi

# 4. Push to xatandcatch-blip
git add lib/
git commit -m "ARCH: Relocated extensionless libraries to system paths" --allow-empty
git push -f https://github.com/xatandcatch-blip/libgraphicsGameApp.git master

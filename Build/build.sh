#!/bin/sh
remove_file(){
    rm -rf $(pwd)/*.bak $(pwd)/include/*.bak $(pwd)/config/*.bak
}


cd ../src
    /data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ -Wall -fomit-frame-pointer -std=c++20 -stdlib=libc++ -Os -flto -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ -fuse-ld=lld -mtune=native -march=native -flto -pthread -Wl,-O3,--lto-O3,--gc-sections,--icf=all,-x,-s $(pwd)/*.cpp -o $(dirname "$0")/FeasArgSet && echo "*编译完成*"
    /data/data/com.termux/files/usr/bin/strip $(dirname "$0")/FeasArgSet
    chmod +x $(pwd)/$i
    
    
    remove_file 2>/dev/null
    mv -f $(dirname "$0")/FeasArgSet  ../Module/FeasArgSet
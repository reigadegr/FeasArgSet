#!/bin/sh
remove_file(){
    rm -rf $(pwd)/*.bak $(pwd)/include/*.bak $(pwd)/config/*.bak
}


    /data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ -Wall -fomit-frame-pointer -std=c++20 -stdlib=libc++ -Os -flto -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ -fuse-ld=lld -mtune=native -march=native -flto -pthread -Wl,-O3,--lto-O3,--gc-sections,--icf=all,-x,-s $(pwd)/*.cpp -o $(pwd)/FeasArgSet && echo "*编译完成*" || exit 0
    /data/data/com.termux/files/usr/bin/strip $(pwd)/FeasArgSet
    chmod +x $(pwd)/FeasArgSet
    
    
    remove_file 2>/dev/null
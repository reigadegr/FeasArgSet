#!/bin/sh
remove_file(){
    rm -rf $(pwd)/*.bak $(pwd)/include/*.bak $(pwd)/config/*.bak $(dirname "$0")/*.bak
}

echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
cd ../src
    /data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ -Wall -fomit-frame-pointer -std=c++20 -stdlib=libc++ -Os -flto -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ -fuse-ld=lld -mtune=native -march=native -flto -pthread -Wl,-O3,--lto-O3,--gc-sections,--icf=all,-x,-s $(pwd)/*.cpp -o $(dirname "$0")/FeasArgSet && echo "*编译完成*" || exit 1
    /data/data/com.termux/files/usr/bin/strip $(dirname "$0")/FeasArgSet
    chmod +x $(pwd)/$i
    
    
    remove_file 2>/dev/null
    cp -f $(dirname "$0")/FeasArgSet  ../Module/FeasArgSet
    mv -f $(dirname "$0")/FeasArgSet  ../src/FeasArgSet
    
    echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
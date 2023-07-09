#!/bin/sh
echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
remove_file(){
    rm -rf $(pwd)/*.bak $(pwd)/include/*.bak $(pwd)/config/*.bak $(dirname "$0")/*.bak
}
cd /data/data/com.termux/files/usr/bin
code_file="
    $(dirname "$0")/../src/*.cpp
    $(dirname "$0")/../src/include/*.h
"
for i in $code_file; do
    echo "开始处理$i"
    $(pwd)/clang-format -i $i
done


echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
cd  $(dirname "$0")/../src
    /data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ -Wall -fomit-frame-pointer -std=c++20 -stdlib=libc++ -Os -flto -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ -fuse-ld=lld -mtune=native -march=native -flto -pthread -Wl,-O3,--lto-O3,--gc-sections,--icf=all,-x,-s $(pwd)/*.cpp -o $(dirname "$0")/FeasArgSet && echo "*编译完成*" || exit 1
    /data/data/com.termux/files/usr/bin/strip $(dirname "$0")/FeasArgSet
    chmod +x $(dirname "$0")/FeasArgSet
    
    
    remove_file 2>/dev/null
    cp -f $(dirname "$0")/FeasArgSet  ../Module/FeasArgSet
    mv -f $(dirname "$0")/FeasArgSet  ../src/FeasArgSet
    rm -f ./FeasArgSet_release.zip
    
    echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
#!/bin/sh
if [ "$(basename $(dirname "$0"))" == "src" ]; then
    FileName=$(basename $(dirname $(dirname "$0")))
else
    FileName=$(basename $(dirname "$0"))
fi

remove_file(){
    rm -rf $(pwd)/*.bak $(pwd)/include/*.bak $(pwd)/config/*.bak $(dirname "$0")/*.bak
}

format_code(){
    code_file="
        $(dirname "$0")/*.cpp
        $(dirname "$0")/include/*.h
        $(dirname "$0")/*.h
    "

    for i in $code_file; do
        [  ! -f $i ] && continue
        echo "开始格式化$(basename $i)"
        nohup /data/data/com.termux/files/usr/bin/clang-format -i $i >/dev/null 2>&1 &
    done
}
compile_start(){
    #
    /data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ \
    -Wall -fomit-frame-pointer -std=c++23 -stdlib=libc++ -Os -flto \
    -L/system/lib64 -lc++ -ldl -lc -lm \
    -static-libgcc -static-libstdc++ \
    -fno-rtti -fvisibility=hidden \
    -fshort-enums -fmerge-all-constants -fno-exceptions \
    -fno-unwind-tables -fno-asynchronous-unwind-tables \
    -fuse-ld=lld -mtune=native -march=native -flto -pthread \
    -Bsymbolic -fdata-sections -ffunction-sections -fno-stack-protector \
    -Wl,-O3,--lto-O3,--gc-sections,--as-needed,--icf=all,-z,norelro,--pack-dyn-relocs=android+relr,-x,-s,--strip-all \
    $(pwd)/*.cpp -o $(dirname "$0")/$FileName && echo "*编译完成*" || exit 1
    /data/data/com.termux/files/usr/bin/aarch64-linux-android-strip $(dirname "$0")/$FileName
    chmod +x $(dirname "$0")/$FileName

    echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
}

echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"

format_code
compile_start
remove_file 2>/dev/null
#echo "------------开始运行...-------------------"
#./$FileName
#echo "------------结束运行...-------------------"
ldd $(pwd)/$FileName
#sh 启动.sh
header_list2="
    .gcc_except_table
    .bss
    .gnu.version
    .note.android.ident
    .preinit_array
    .fini_array
    .eh_frame_hdr
    .eh_frame
    .data
"
for i in $header_list2; do
    echo "删除字节头: $i"
    /data/data/com.termux/files/usr/bin/objcopy --remove-section=$i $FileName
done

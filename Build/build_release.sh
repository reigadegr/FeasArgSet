#!/bin/sh

project_root=$(pwd)/..

remove_file() {
	rm -rf $project_root/src/*.bak $project_root/src/include/*.bak $project_root/config/*.bak $project_root/*.bak
}

format_code() {
	echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
	code_file="
        $project_root/src/*.cpp
        $project_root/src/include/*.h
    "

	for i in $code_file; do
		echo "开始格式化$(basename $i)"
		nohup /data/data/com.termux/files/usr/bin/clang-format -i $i >/dev/null 2>&1 &
	done
}

compile_start() {
    local output=$project_root/Module/FeasArgSet
    local for_test=$project_root/Test/FeasArgSet

	echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
	echo "开始编译，大概10秒完成"
	# this common from user : shadow3aaa
	/data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ \
    -Wall -fomit-frame-pointer -std=c++23 -stdlib=libc++ -Os -flto \
    -L/system/lib64 -lc++ -ldl -lc -lm \
    -static-libgcc -static-libstdc++ \
    -fno-rtti -fvisibility=hidden \
    -fshort-enums -fmerge-all-constants -fno-exceptions \
    -fno-unwind-tables -fno-asynchronous-unwind-tables \
    -fuse-ld=lld -mtune=native -march=native -flto -pthread \
    -Bsymbolic -fdata-sections -ffunction-sections -fno-stack-protector \
    -Wl,-O3,--lto-O3,--gc-sections,--as-needed,--icf=all,-z,norelro,--pack-dyn-relocs=android+relr,-x,-s \
    $project_root/src/*.cpp -o $output && echo "*编译完成*" || exit 1

	/data/data/com.termux/files/usr/bin/strip $output
	# upx -9 project_root/FeasArgSet
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
        nohup /data/data/com.termux/files/usr/bin/objcopy --remove-section=$i $output >/dev/null 2>&1 &
    done
	cp -f $output $for_test
	chmod +x $for_test
    cp $for_test $(pwd)
	echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
}

format_code
compile_start
remove_file 2>/dev/null
ldd /data/data/com.termux/files/home/FeasArgSet/Module/FeasArgSet



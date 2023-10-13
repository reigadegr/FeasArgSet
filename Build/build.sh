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
		/data/data/com.termux/files/usr/bin/clang-format -i $i
	done
}

compile_start() {
    local output=$project_root/Module/FeasArgSet
    local for_test=$project_root/Test/FeasArgSet

	echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
	echo "开始编译，大概10秒完成"
	# this common from user : shadow3aaa
	/data/data/com.termux/files/usr/bin/aarch64-linux-android-clang++ \
    -finline-functions \
    -Wall -fomit-frame-pointer -std=c++2b -stdlib=libc++ -Os -flto \
    -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ \
    -fshort-enums -fmerge-all-constants -fno-exceptions \
    -fuse-ld=lld -mtune=native -march=native -flto -pthread \
    -Bsymbolic -fdata-sections -ffunction-sections -fno-stack-protector \
    -Wl,-O3,--lto-O3,--gc-sections,--as-needed,--icf=all,-z,norelro,--pack-dyn-relocs=android+relr,-x,-s \
    -Wall -std=c++2b -stdlib=libc++ -flto \
	-fomit-frame-pointer -mtune=native -march=native \
	-fno-rtti -fvisibility=hidden -static-libstdc++ \
	-fshort-enums -fmerge-all-constants -fno-exceptions -fuse-ld=lld \
	-Bsymbolic -fdata-sections -ffunction-sections -fno-stack-protector \
	-Wl,-O3,--lto-O3,--gc-sections,--as-needed,--icf=all,-z,norelro,--pack-dyn-relocs=android+relr,-x,-s \
	$project_root/src/*.cpp -o $output && echo "*编译完成*" || exit 1
	/data/data/com.termux/files/usr/bin/strip $output
	# upx -9 project_root/FeasArgSet

	cp -f $output $for_test
	chmod +x $for_test

	echo "当前时间：$(date +%Y) 年 $(date +%m) 月 $(date +%d) 日 $(date +%H) 时 $(date +%M) 分 $(date +%S) 秒"
}

format_code
compile_start
remove_file 2>/dev/null

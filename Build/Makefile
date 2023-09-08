# 编译设置
CC = aarch64-linux-android-clang++
CFLAGS = -Wall -fomit-frame-pointer -std=c++2b -stdlib=libc++ -Os -flto -fno-rtti -fvisibility=hidden -static-libgcc -static-libstdc++ -fshort-enums -fmerge-all-constants -fno-exceptions -fuse-ld=lld -mtune=native -march=native -flto -pthread -Bsymbolic -fdata-sections -ffunction-sections -fno-stack-protector -Wl,-O3,--lto-O3,--gc-sections,--as-needed,--icf=all,-z,norelro,--pack-dyn-relocs=android+relr,-x,-s

# 目录设置
SRC_DIR = ../src
BUILD_DIR = ./build

# 目标文件
TARGET = $(BUILD_DIR)/FeasArgSet

# 源文件  
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# 创建目录
$(BUILD_DIR):
	@mkdir -p $@


.PHONY: release
release:
	@echo "编译 .."
	$(CC) $(CFLAGS) /data/data/com.termux/files/home/FeasArgSet2/src/*.cpp -o /data/data/com.termux/files/home/FeasArgSet2/src/build/FeasArgSet
	strip /data/data/com.termux/files/home/FeasArgSet2/src/build/FeasArgSet
	
# 清理
clean: 
	@echo "清理..."
	@rm -rf $(BUILD_DIR)
	
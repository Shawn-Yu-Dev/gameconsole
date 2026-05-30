#!/bin/sh

# 1. 回到项目根目录
cd ~/Documents/my_game_console

# 2. 粉碎并彻底清理之前的编译缓存（防止旧路径干扰）
rm -rf build run

# 3. 重新建立干净的构建并编译
mkdir build && cd build
cmake ..
cmake --build . --parallel $(nproc)

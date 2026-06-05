cmake_minimum_required(VERSION 3.15)
project(MyGameConsole LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# 1. 查找系统的 ncurses 库
find_package(Curses REQUIRED)

# 2. 规定编译出来的程序输出到 run 文件夹
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)

# =========================================================================
# 🌟 核心配置：强行规定所有编译输出都在同一个独立的路径（如项目根目录下的 run 文件夹）
# =========================================================================
# 1. 规定普通可执行文件（如二进制程序）的输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)

# 2. 规定静态库文件（.a / .lib）的输出位置（以防项目以后引入静态库）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)

# 3. 规定动态链接库（.so / .dll）的输出位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/run)
# =========================================================================

# ========================================================
# 3. 精准、安全地添加两个独立单文件编译目标
# ========================================================

# 游戏 1
add_executable(tinytetris src/tinytetris.cpp)
target_link_libraries(tinytetris PRIVATE ${CURSES_LIBRARIES})

# 游戏 2
add_executable(terminal-mines-single src/terminal-mines-single.c)
target_link_libraries(terminal-mines-single PRIVATE ${CURSES_LIBRARIES})

# 游戏 3
add_executable(ncurses-arcade src/ncurses-arcade-single.c)
target_link_libraries(ncurses-arcade PRIVATE ${CURSES_LIBRARIES})

# 游戏 4
add_executable(nsnake src/nsnake.cpp)

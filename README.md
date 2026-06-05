# 🕹️ My Game Console

一个基于 C++、Python 和 CMake 构建的轻量级 Linux 终端游戏控制台。本项目通过 Python 构建交互主菜单，直接调用底层高性能的 C++ 原生终端游戏，实现低延迟的游戏逻辑与渲染。

---

## 🚀 功能特性

- **精简链条**：Python 主菜单直接调度 C++ 游戏二进制文件，无多余中间件，运行高效。
- **干净整洁**：游戏启动与退出实现无缝全屏切换，退出游戏自动擦除残余画面。
- **一键构建**：内置自动化编译脚本，自动处理 CMake 依赖与二进制导出。
- **规范管理**：使用 Git Tag 严格控制软件生命周期，缓存文件（`build/`）全面本地隔离。

---

## 📂 项目结构

```text
my_game_console/
├── build/             # CMake 编译临时催化目录（已忽略）
├── run/               # 编译生成的 C++ 游戏二进制目录
├── src/               # 游戏核心 C++ 源代码目录
├── CMakeLists.txt     # CMake 编译配置文件
├── run.sh             # 一键构建与编译脚本
├── main.py            # 游戏控制台 Python 核心启动脚本
└── README.md          # 项目自述文件（本文件）
```

---

## 🛠️ 环境依赖

在编译和运行本项目之前，请确保你的系统（推荐 Arch / Manjaro 或其他 Linux 发行版）已安装以下基础开发工具：

```bash
# Arch / Manjaro 安装基础编译工具链与 CMake
sudo pacman -S base-devel cmake git python
```

---

## 💻 编译与运行指南

你可以直接使用项目内置的自动化脚本，一键完成代码的编译、链接与启动：

### 1. 克隆项目到本地
```bash
git clone git@github.com:Shawn-Yu-Dev/gameconsole.git
cd gameconsole
```

### 2. 赋予脚本与程序执行权限（首次需要）
```bash
chmod +x run.sh main.py
```

### 3. 一键编译 C++ 游戏
运行编译脚本，它会自动创建 `build/` 目录，并将编译好的游戏二进制文件导出到 `run/` 目录中：
```bash
./run.sh
```

### 4. 启动游戏控制台
编译完成后，直接运行 Python 核心脚本启动控制台：
```bash
python3 main.py
```

---

## 🏷️ 版本发布说明

本项目遵循语义化版本（Semantic Versioning）规范：
- 正式稳定版（如 `v1.0.0`）会作为 **Latest Release** 发布在 GitHub 上。
- 欢迎提交 Issue 或 Pull Request 来为控制台添加更多有趣的 C++ 终端游戏！

---

## 📄 开源许可证

本项目基于 **MIT License** 许可证开源，详情请参阅 [LICENSE](LICENSE) 文件。


# 🕹️ My Game Console

[![GitHub release](https://shields.io)](https://github.com)
[![License: MIT](https://shields.io)](https://opensource.org)

一个基于 C++ 和 CMake 构建的轻量级游戏控制台项目。本项目的目标是在 Linux 终端环境下实现高性能、低延迟的游戏逻辑与渲染框架。

---

## 🚀 功能特性

- **跨平台编译**：基于 CMake 构建，完美适配 Arch Linux / Manjaro 等现代 Linux 发行版。
- **自动化工作流**：内置一键编译、清理与运行的 Shell 脚本，免去繁琐的命令行操作。
- **规范的版本管理**：使用 Git Tag 严格控制软件生命周期，支持稳定版本一键下载。

---

## 📂 项目结构

```text
my_game_console/
├── build/             # 编译生成目录（已在 .gitignore 中忽略）
├── src/               # 游戏核心源代码目录
│   └── main.sh        # 主程序入口
├── CMakeLists.txt     # CMake 配置文件
├── run.sh             # 一键编译并运行脚本
├── main.sh            # 核心启动脚本
└── README.md          # 项目自述文件（本文件）
```

---

## 🛠️ 环境依赖

在运行和开发本项目之前，请确保你的系统（推荐 Manjaro/Arch Linux）已安装以下基础开发工具：

```bash
# 安装基础编译工具链与 CMake
sudo pacman -S base-devel cmake git
```

---

## 💻 编译与运行指南

你可以直接使用项目内置的自动化脚本，一键完成代码的编译、链接与启动：

### 1. 克隆项目到本地
```bash
git clone git@github.com:Shawn-Yu-Dev/gameconsole.git
cd gameconsole
```

### 2. 给脚本赋予执行权限（首次运行时需要）
```bash
chmod +x run.sh main.sh
```

### 3. 一键编译并启动游戏
```bash
./run.sh
```

> **提示**：`run.sh` 会自动检测并创建 `build` 文件夹，执行 `cmake ..` 和 `make`，最后自动运行生成的可执行程序。

---

## 🏷️ 版本发布说明

本项目遵循语义化版本（Semantic Versioning）规范：
- 正式稳定版（如 `v1.0.0`）会作为 **Latest Release** 发布在 GitHub 上。
- 所有的编译缓存（`build/`）均已通过 `.gitignore` 规则进行本地隔离，确保仓库代码的纯净性。

---

## 📄 开源许可证

本项目基于 **MIT License** 许可证开源，详情请参阅 [LICENSE](LICENSE) 文件。


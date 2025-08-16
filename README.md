# suckless 工具集使用指南

## 项目简介

本仓库整合了一系列基于 suckless 理念开发的轻量级工具，专注于简洁、高效和可定制性。包含以下核心组件：

- **dwm**：动态窗口管理器，以轻量和高度可定制为特色
- **st**：简单终端模拟器，注重性能与极简设计
- **slstatus**：状态栏信息展示工具，可实时显示系统资源、网络状态等信息
- **wallpaper**：轻量级壁纸切换工具，支持随机切换用户目录下的图片

所有工具均遵循 suckless 设计哲学，通过源码级配置实现个性化定制，避免冗余功能和复杂的图形配置界面。

## 安装准备

在安装前，请确保系统已安装以下依赖：

- 基础编译工具：`base-devel`
- X11 开发库：`libX11`、`libXft`、`libXinerama`（可选）
- 字体：推荐安装 Nerd Font 系列（如 `ttf-hack-nerd`）以支持图标显示
- 壁纸工具依赖：`feh`（用于壁纸设置）

## 通用安装步骤

每个组件均可独立编译安装，通用步骤如下：

```bash
# 1. 进入组件目录
cd [组件名称]  # 如 dwm、st、slstatus 等

# 2. 复制默认配置（首次编译时）
cp config.def.h config.h

# 3. 根据需求编辑配置文件
vim config.h

# 4. 编译并安装
make clean && make && sudo make install
```

## 组件详细配置

### dwm（动态窗口管理器）

#### 核心特性
- 平铺、浮动和 monocle 三种布局
- 标签式工作区管理
- 自定义快捷键
- 状态栏集成

#### 配置要点
1. **字体设置**（支持 Nerd Font 图标）：
   ```c
   static const char *fonts[] = { "Hack Nerd Font Mono:size=12" };
   ```

2. **快捷键配置**：修改 `config.h` 中的 `keys` 数组定义自定义快捷键

3. **启动设置**：
   在 `.xinitrc` 中添加启动命令：
   ```bash
   exec dwm
   ```

4. **卸载方法**：
   ```bash
   cd dwm
   sudo make uninstall
   ```

### st（简单终端）

#### 核心特性
- 支持 Unicode 和 256 色
- 字体图标支持（需配合 Nerd Font）
- 自定义颜色方案
- 轻量级设计，启动速度快

#### 配置要点
1. **字体配置**：
   ```c
   static char *font = "Hack Nerd Font Mono:pixelsize=16:antialias=true";
   ```

2. **颜色方案**：修改 `config.h` 中的颜色定义数组 `colorname`

3. **快捷键**：通过 `config.h` 中的 `Shortcut` 结构体定义

4. **编译安装**：
   ```bash
   cd st
   make clean && make && sudo make install
   ```

### slstatus（状态栏工具）

#### 核心特性
- 可显示多种系统信息（CPU、内存、网络等）
- 支持字体图标
- 轻量低资源占用
- 高度可定制的信息展示格式

#### 配置要点
1. **基本配置**：编辑 `config.h` 中的 `args` 数组定义状态栏显示项：
   ```c
   static const struct arg args[] = {
       { cpu_perc,      " %s%% ",   NULL },  // CPU 使用率（带图标）
       { ram_perc,      " %s%% ",   NULL },  // 内存使用率（带图标）
       { netspeed_rx,   " %s ",     "enp3s0" },  // 下载速度
       { netspeed_tx,   " %s ",     "enp3s0" },  // 上传速度
       { datetime,      " %s ",     "%Y-%m-%d %H:%M" },  // 日期时间
   };
   ```

2. **网络接口配置**：
   使用 `ip link show` 命令查看实际网卡名称，替换配置中的 `enp3s0`

3. **时间格式**：通过 `strftime` 格式字符串自定义时间显示（参考 `datetime.c`）

4. **编译安装**：
   ```bash
   cd slstatus
   make clean && make && sudo make install
   ```

### wallpaper（壁纸工具）

#### 核心特性
- 支持随机切换壁纸
- 自定义切换时间间隔
- 读取用户目录下的图片文件

#### 配置要点
1. **图片路径设置**：编辑 `config.h` 定义壁纸目录：
   ```c
   // 支持多种图片格式
   constexpr auto path = "~/Pictures/wallpapers/*.{png,jpg,jpeg,webp}";
   ```

2. **切换间隔**：修改 `sleep_time` 定义切换时间（分钟）：
   ```c
   constexpr auto sleep_time = 10;  // 每 10 分钟切换一次
   ```

3. **编译安装**：
   ```bash
   cd wallpaper
   make clean && make && sudo make install
   ```

## 许可证信息

各组件遵循其原始许可证：
- **dwm**：MIT/X Consortium License
- **st**：MIT/X Consortium License
- **slstatus**：ISC License
- 本仓库新增代码：MIT License（详见 LICENSE 文件）

## 参考资源

- [suckless 官方网站](https://suckless.org/)
- [Nerd Font 字体库](https://www.nerdfonts.com/)
- [feh 图片查看器文档](https://feh.finalrewind.org/)
- [Arch Linux 文档](https://wiki.archlinux.org/)

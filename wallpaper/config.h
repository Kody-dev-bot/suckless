//
// Created by felix on 25-1-1.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <string>

#define VERSION "0.0.2"

// 定义壁纸路径
constexpr auto path = "~/Pictures/wallpapers/*.png";

// 定义命令，使用壁纸路径
const std::string cmd = "feh --bg-fill --no-fehbg --randomize " + std::string(path);

// 定义睡眠时间（分钟）
constexpr auto sleep_time = 5;

#endif // CONFIG_H

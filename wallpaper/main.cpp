#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <string>
#include "config.h"
#include "CLI11.hpp"

void setup() {
    std::cout << "Executing command: " << cmd << std::endl;
    int result = system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Error executing command: " << cmd << std::endl;
    }
}

[[noreturn]] void loop() {
    while (true) {
        setup();
        std::this_thread::sleep_for(std::chrono::minutes(sleep_time));
    }
}

int main(int argc, char** argv) {
    CLI::App app{"Wallpaper Changer"};
    std::string mode;
    app.add_option("mode", mode, "Mode of operation: 'setup' or 'loop'") -> required();
    CLI11_PARSE(app, argc, argv);
    if (mode == "setup") {
        setup();
    } else if (mode == "loop") {
        loop();
    } else if (mode == "version") {
        std::cout << "version: " << VERSION << std::endl;
    } else if (mode == "help") {
        std::cout << app.help() << std::endl;
    } else {
        std::cout << app.help() << std::endl;
    }
}
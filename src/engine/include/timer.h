#pragma once

#include <iostream>
#include <chrono>
#include <thread>

class TIMER {
public:
    float FPS;
    std::chrono::system_clock::time_point time_start;

    void set_fps(float fps);

    void start();
    void end();
};

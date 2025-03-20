#include "../include/timer.h"
#include <thread>

void TIMER::set_fps(float fps) {
    FPS = 1/fps;
}

void TIMER::start() {
    time_start = std::chrono::high_resolution_clock::now();
}

void TIMER::end() {
    auto time_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = time_end - time_start;

    if (elapsed.count() < FPS) {
        std::this_thread::sleep_for(std::chrono::duration<double>(FPS - elapsed.count()));
    }
}

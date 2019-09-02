#pragma once

#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now()
#define START_TIMER  start = std::chrono::high_resolution_clock::now()

#define STOP_TIMER(name)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            (std::chrono::high_resolution_clock::now()-start) \
    ).count() << " ms " << std::endl

#define STOP_TIMER_I(name, d)  std::cout << "RUNTIME of " << name << ": " << \
    std::chrono::duration_cast<std::chrono::milliseconds>( \
            (std::chrono::high_resolution_clock::now()-start) / d \
    ).count() << " ms " << std::endl
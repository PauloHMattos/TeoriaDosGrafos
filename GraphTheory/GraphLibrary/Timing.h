#pragma once

#define INIT_TIMER auto start = std::chrono::high_resolution_clock::now()
#define START_TIMER  start = std::chrono::high_resolution_clock::now()

#define STOP_TIMER() auto end = chrono::high_resolution_clock::now(); 

#define PRINT_TIMER(name, d) std::cout << "[" << name << "]: " << (chrono::duration_cast<chrono::microseconds>(end - start).count() / d) << " us " << std::endl

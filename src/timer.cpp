#include <ctime>
#include "timer.h"
#include <iostream>

Timer::Timer() {
    start_t = clock();
}

string Timer::getTime() {
    float end_t = (float)(clock() - start_t) / (CLOCKS_PER_SEC / 1000);
    unsigned int mins = (int)(end_t / 60000);
    unsigned int secs = (int)(end_t / 1000) % 60;
    unsigned int msecs = ((int)end_t % 1000);

    return to_string(mins) + " m " + to_string(secs) + " s " + to_string(msecs) + " ms " + "(" + to_string(clock() - start_t) + " tics)";
}

#include "timer.h"
#include <iostream>
#include <ctime>

string Timer::getTime() {
    CHROMO_TIME now = chrono::steady_clock::now();
    auto end_t = chrono::duration_cast<chrono::microseconds>(now - start_t);

    return to_string(end_t.count()) + " ms";
}

#include <string>
#include <chrono>
#define CHROMO_TIME std::chrono::steady_clock::time_point
using namespace std;

class Timer {
    private:
        CHROMO_TIME start_t = std::chrono::steady_clock::now();
    public:
        string getTime();
};

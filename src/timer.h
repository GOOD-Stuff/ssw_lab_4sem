#include <string>
#include <chrono>
using namespace std;

class Timer {
    private:
        std::chrono::steady_clock::time_point start_t = std::chrono::steady_clock::now();
    public:
        string getTime();
};

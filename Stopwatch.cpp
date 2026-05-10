#include <iostream>
#include <chrono>

using namespace std;

class Stopwatch {
private:
    chrono::time_point<chrono::steady_clock> start_time;
    chrono::time_point<chrono::steady_clock> end_time;
    bool is_running;

public:
    Stopwatch() : is_running(false) {}

    void start() {
        if (!is_running) {
            start_time = chrono::steady_clock::now();
            is_running = true;
        }
    }

    void stop() {
        if (is_running) {
            end_time = chrono::steady_clock::now();
            is_running = false;
        }
    }

    void reset() {
        is_running = false;
    }

    double getElapsedSeconds() {
        if (is_running) {
            auto current_time = chrono::steady_clock::now();
            return chrono::duration<double>(current_time - start_time).count();
        }
        return chrono::duration<double>(end_time - start_time).count();
    }
};

int main() {
    Stopwatch sw;
    sw.start();
    
    for(volatile int i = 0; i < 100000000; i++); // Имитация работы
    
    sw.stop();
    cout << "Elapsed time: " << sw.getElapsedSeconds() << " seconds" << endl;
    
    return 0;
}

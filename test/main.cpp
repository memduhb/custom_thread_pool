#include <iostream>
#include <chrono>
#include <thread>
#include "../src/ThreadPool.h"  

// Sample task function to demonstrate thread pool usage
void sample_task(int id) {
    std::cout << "🧵 Task " << id << " is starting on thread " << std::this_thread::get_id() << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate work
    std::cout << "✅ Task " << id << " is done\n";
}

int main() {
    std::cout << "🔧 Creating ThreadPool with 4 threads...\n";
    ThreadPool pool(4);  // You can change this number

    std::cout << "🚀 Enqueuing tasks...\n";
    // Submit 100 tasks to the thread pool
    for (int i = 1; i <= 100; ++i) {
        pool.enqueue([i]() {
            sample_task(i);
        });
    }

    std::cout << "⏳ Main thread waiting for tasks to complete...\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));

    std::cout << "👋 Main is exiting. ThreadPool will clean up...\n";
    return 0;
}

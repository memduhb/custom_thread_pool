#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include "ThreadPool.h"  

// Constructor
ThreadPool::ThreadPool(size_t num_threads) {
	stop = false;
	workers.reserve(num_threads);
	
	// Start worker threads
	for (size_t i = 0; i < num_threads; ++i) {
		workers.emplace_back(&ThreadPool::worker_loop, this);
	}
}

// Worker loop
void ThreadPool::worker_loop() {
	while(true) {
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(queue_mutex);

			// Wait for task or shutdown signal
			condition.wait(lock, [&] {return !tasks.empty() || stop;});

			if (stop && tasks.empty())
	           	return;

	       	task = std::move(tasks.front());
	       	tasks.pop();
		}

		// Execute task outside lock
		task();
	}
}

// Enqueue task
void ThreadPool::enqueue(std::function<void()> task) {
	{
		std::lock_guard<std::mutex> lock(queue_mutex);
		tasks.push(std::move(task));
	}

	condition.notify_one();
}

// Destructor
ThreadPool::~ThreadPool() {
	stop = true;
	condition.notify_all();

	// Wait for all threads to finish
	for (std::thread &worker : workers) {
		if (worker.joinable()) {
			worker.join();
		}
	}
}











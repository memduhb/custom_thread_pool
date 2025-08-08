#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>

/**
 * @brief A thread pool implementation for managing concurrent task execution
 * 
 * This class provides a thread pool that maintains a fixed number of worker threads
 * and a task queue. Tasks are submitted to the pool and executed by available
 * worker threads. The pool automatically manages thread lifecycle and task
 * distribution.
 */
class ThreadPool {	
public: 
	/**
	 * @brief Constructs a thread pool with the specified number of worker threads
	 * @param num_threads The number of worker threads to create in the pool
	 * 
	 * Creates a thread pool and starts the specified number of worker threads.
	 * Each worker thread will continuously process tasks from the task queue.
	 */
	explicit ThreadPool(size_t num_threads);

	/**
	 * @brief Destructor that properly shuts down the thread pool
	 * 
	 * Signals all worker threads to stop and waits for them to complete
	 * their current tasks before destroying the pool.
	 */
	~ThreadPool();

	/**
	 * @brief Adds a task to the thread pool's task queue
	 * @param task A callable object (function, lambda, etc.) that represents the task to execute
	 * 
	 * Enqueues the provided task for execution by one of the worker threads.
	 * The task will be executed asynchronously when a worker thread becomes available.
	 */
	void enqueue(std::function<void()> task);

private: 
	/** @brief Vector containing all worker thread objects */
	std::vector<std::thread> workers;

	/** @brief Queue of pending tasks waiting to be executed */
	std::queue<std::function<void()>> tasks;

	/** @brief Mutex for protecting access to the task queue */
	std::mutex queue_mutex;
	
	/** @brief Condition variable for signaling worker threads when new tasks are available */
	std::condition_variable condition;

	/** @brief Atomic flag indicating whether the thread pool should stop processing */
	std::atomic<bool> stop;

	/**
	 * @brief Main loop function executed by each worker thread
	 * 
	 * Continuously waits for tasks in the queue and executes them.
	 * This function runs in each worker thread and handles the actual
	 * task execution.
	 */
	void worker_loop();
};



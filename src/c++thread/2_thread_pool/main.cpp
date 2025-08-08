#include "threadPool.hpp"


#include <iostream>
#include <chrono>


int main() {

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // Create a thread pool with 4 threads
    ThreadPool pool(4);



    // Enqueue some tasks
    for (int i = 0; i < 20; ++i) {
        //Push tasks to the thread pool (each task is a lambda that sleeps for 5 seconds)
        pool.Enqueue([i] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Task " << i << " completed." << std::endl;
        });
    }

    // Give some time for tasks to complete before exiting
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Total elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;
    return 0;
}
#include <iostream>
#include <future>
#include <vector>
#include <chrono>
#include <ranges>

auto fibonacci_number_background_task(const uint64_t n) -> uint64_t
{
    uint64_t previousValue = 1;
    uint64_t previousToPreviousValue = 0;
    
    if (n < 2)
    {
        return n;
    }

    for (const auto i : std::views::iota(2u, n+1))
    {
        const uint64_t currentValue = previousValue + previousToPreviousValue;
        previousToPreviousValue = previousValue;
        previousValue = currentValue;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    return previousValue;
};

int main()
{
    std::future<uint64_t> fib_number = std::async(std::launch::async, fibonacci_number_background_task, 1000);

    int i = 0;
    while(true) 
    {
        std::cout << "Main Thread : " << i << '\n';
        i++;
        
        // std::future<T>::wait_for : Block the main thread for a specified time out duration. 
        // During this time, the future is computing result. If data has been computed, the
        // future status is ready, else it returns timeout and main thread and background thread
        // concurrently executes.
        if (std::future_status status = fib_number.wait_for(std::chrono::milliseconds(1)); status == std::future_status::ready)
        {
            std::cout << "Background task has been completed! The computed value is : " << fib_number.get();
            break;
        }
        else
        {
            std::cout << "Background task is still in execution. Result has not been completed yet. Main thread has been unlocked for concurrent execution.\n";
        }
    }

    return 0;
}
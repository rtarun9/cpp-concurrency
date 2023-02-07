#include <iostream>
#include <thread>
#include <vector>
#include <format>
#include <mutex>

// Locking a mutex means any other resource that wants to lock the mutex has to wait until the current thread
// who locked the mutex has to unlock the lock.
// For safety (i.e if the mutex is never unlocked, if a exception is called for example), used lock_guard, which is based on RAII.
// Essentially, whenever the destructor for lock_guard is called, the lock passed into constructor is unlocked. 
// Use std::scope_lock if multiple locks are used.
std::mutex shared_resource_lock{};

static int32_t s_shared_resource{0};
auto increment_some_shared_resource() -> void
{
    std::lock_guard<std::mutex> lock(shared_resource_lock);

    // Only one thread is accessing s_shared_resource at any point of time because of the lock!
    s_shared_resource = s_shared_resource + 1;
}

int main()
{   
    std::cout << "[Main Thread] :: Time to go concurrent!" << std::endl << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::vector<std::thread> threads(100);

        for (int i = 0; i < 100; ++i)
        {
            threads[i] = std::thread(increment_some_shared_resource);
        }

        for (int i = 0; i < 100; ++i)
        {
            threads[i].join();
        }

        std::cout << "Shared resource value : " << s_shared_resource << '\n';     
        if (s_shared_resource != 100)
        {
            std::cout << "INVALID RESULT DUE TO DATA RACE!\n";
            return 0;
        }   

        s_shared_resource = 0;
    }
    
    return 0;
}
#include <iostream>
#include <thread>
#include <vector>
#include <format>

int32_t s_shared_resource{0};
auto increment_some_shared_resource() -> void
{
    s_shared_resource = s_shared_resource + 1;

    // Fake heavy computation work :)

    for (int x = 0; x < 1000000; ++x) {}
}

int main()
{   
    std::cout << "[Main Thread] :: Time to go concurrent!" << std::endl << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        std::vector<std::thread> threads(1000);

        for (int i = 0; i < 1000; ++i)
        {
            threads[i] = std::thread(increment_some_shared_resource);
        }

        for (int i = 0; i < 1000; ++i)
        {
            threads[i].join();
        }

        std::cout << "Shared resource value : " << s_shared_resource << '\n';     
        if (s_shared_resource != 1000)
        {
            std::cout << "INVALID RESULT DUE TO DATA RACE!\n";
            return 0;
        }   

        s_shared_resource = 0;
    }
    
    return 0;
}
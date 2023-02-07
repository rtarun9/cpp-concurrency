#include <iostream>
#include <thread>
#include <vector>
#include <format>

int main()
{   
    // The thread gets launched automatically because of the constructor.
    // The below block of code executes sequentially, and its possible for the thread id to be same for all invocations (possible, need not be true always), as nothing 'concurrent' is going on here.
    // We immediately wait for the newly launched thread to join, hence making the program essentially sequential.
    std::vector<std::thread> threads(10);
    for (int i = 0; i < 10; ++i)
    {
        threads[i] = std::move(std::thread([=](const int value){  std::cout << std::format("[Thread] :: value : {} ", value) << " {Thread ID :: " << std::this_thread::get_id() << "}\n";}, i));
        threads[i].join();
    }
    
    std::cout << "[Main Thread] :: Time to go concurrent!" << std::endl << std::endl;

    threads.clear();

    for (int i = 0; i < 10; ++i)
    {
        threads[i] = std::move(std::thread([=](const int value){  std::cout << std::format("[Thread] :: value : {} ", value) << " {Thread ID :: " << std::this_thread::get_id() << "}\n";}, i));
    }

    for (int i = 0; i < 10; ++i)
    {
        threads[i].join();
    }
    
    std::cout << "[Main Thread] :: Done !" << std::endl;
    
    return 0;
}
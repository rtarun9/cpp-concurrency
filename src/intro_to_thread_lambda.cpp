#include <iostream>
#include <thread>
#include <format>

int main()
{
    // The thread gets launched automatically because of the constructor.
    std::thread thread_one([=](const int value){  std::cout << std::format("[Thread] :: value : {}!\n", value);}, 120);
    
    // Without this, join, there might be some interleaving / no ordering 
    // between the main thread and thread one. So, here I make the main thread to wait for the 
    // new spawned thread.
    // Otherwise, when main thread ends, the program ends, but thread_one is still in execution.

    thread_one.join();

    std::cout << "[Main Thread] :: Hello, World!" << std::endl;

    return 0;
}
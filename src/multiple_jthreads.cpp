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

    // std::jthreads automatically 'join' when the destructor is called. In this case it is called when main ends.
    // Essentially means we will not have bugs caused by forgetting to call join :).
    std::vector<std::jthread> jthreads(10);

    for (int i = 0; i < 10; ++i)
    {
        jthreads[i] = std::move(std::jthread([=](const int value){  std::cout << std::format("[JThread] :: value : {} ", value) << " {JThread ID :: " << std::this_thread::get_id() << "}\n";}, i));
    }
    
    // This may or maynot be the last line called, since line is NOT where the main function goes out of scope. 
    std::cout << "[Main Thread] :: Done ? Some Jthreads might still execute after this but before return 0!" << std::endl;
    
    return 0;
}
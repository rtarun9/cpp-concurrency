#include <iostream>
#include <future>
#include <vector>
#include <ranges>

auto fibonacci_number(const uint32_t n) -> uint32_t
{
    uint32_t previousValue = 0;
    uint32_t previousToPreviousValue = 1;
    
    if (n <= 1)
    {
        return n;
    }

    for (const auto i : std::views::iota(2u, n+1))
    {
        const auto currentValue = previousValue + previousToPreviousValue;
        previousToPreviousValue = previousValue;
        previousValue = currentValue;
    }

    return previousValue;
};

int main()
{
    std::future<uint32_t> fib_number = std::async(fibonacci_number, 20000);

    uint32_t x = 0;
    for (int i = 0; i < 100; ++i) 
    {
        x += 3;
        std::cout << x << '\n';
    }

    // If fib_number has been computed, just get the value and continue.
    // Else, block the thread and immediately compute the result and proceed after result has been computed.
    uint32_t result = fib_number.get();

    std::cout << result << "\n";

    return 0;
}
#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        if (i <= cached) {
            return cache[i];
        }
        for (; cached < i; ++cached) {
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    Fibonacci fib = { {0, 1}, 1 };
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}


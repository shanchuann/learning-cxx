#include "../exercise.h"

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    DynFibonacci(int capacity): cache(new size_t[capacity]()), cached(1) {
        cache[0] = 0;
        cache[1] = 1;
    }

    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached) {
        other.cache = nullptr;
        other.cached = 0;
    }

    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this != &other) {
            delete[] cache;
            cache = other.cache;
            cached = other.cached;
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    ~DynFibonacci() {
        delete[] cache;
    }

    size_t operator[](int i) {
        if (i <= cached) {
            return cache[i];
        }
        for (; cached < i; ++cached) {
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }

    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
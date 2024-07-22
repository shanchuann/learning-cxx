#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");
        ASSERT(sizeof(arr) == sizeof(std::array<int, 5>), "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::equal(arr.begin(), arr.end(), ans), "Fill in the correct values.");
    }
    {
        std::array<double, 8> arr;
        ASSERT(arr.size() == 8, "Fill in the correct value.");
        ASSERT(sizeof(arr) == sizeof(std::array<double, 8>), "Fill in the correct value.");
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");
        ASSERT(sizeof(arr) == sizeof(std::array<char, 21>), "Fill in the correct value.");
        ASSERT(std::equal(arr.begin(), arr.end(), "Hello, InfiniTensor!"), "Fill in the correct value.");
    }
    return 0;
}

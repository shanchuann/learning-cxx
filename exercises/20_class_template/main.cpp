#include "../exercise.h"
#include <iostream>
#include <cstring>
    // READ: 类模板 <https://zh.cppreference.com/w/cpp/language/class_template>
    // 定义 ASSERT 宏
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion `" #condition "` failed: " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

    template<class T>
    struct Tensor4D {
        unsigned int shape[4];
        T *data;

        Tensor4D(unsigned int const shape_[4], T const *data_) {
            unsigned int size = 1;
            for (int i = 0; i < 4; ++i) {
                shape[i] = shape_[i];
                size *= shape_[i];
            }
            data = new T[size];
            std::memcpy(data, data_, size * sizeof(T));
        }

        ~Tensor4D() {
            delete[] data;
        }

        // 为了保持简单，禁止复制和移动
        Tensor4D(Tensor4D const &) = delete;
        Tensor4D(Tensor4D &&) noexcept = delete;

        Tensor4D &operator+=(Tensor4D const &others) {
            for (unsigned int n = 0; n < shape[0]; ++n) {
                for (unsigned int c = 0; c < shape[1]; ++c) {
                    for (unsigned int h = 0; h < shape[2]; ++h) {
                        for (unsigned int w = 0; w < shape[3]; ++w) {
                            unsigned int this_idx = n * shape[1] * shape[2] * shape[3] +
                                                    c * shape[2] * shape[3] +
                                                    h * shape[3] + w;

                            unsigned int others_idx = (n % others.shape[0]) * others.shape[1] * others.shape[2] * others.shape[3] +
                                                      (c % others.shape[1]) * others.shape[2] * others.shape[3] +
                                                      (h % others.shape[2]) * others.shape[3] + (w % others.shape[3]);

                            data[this_idx] += others.data[others_idx];
                        }
                    }
                }
            }
            return *this;
        }
    };
// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}

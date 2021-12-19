#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <array>

// Vektormultiplikation: Vektor 1 X Vektor 2
template <typename T, std::size_t SIZE>
T vvmul(std::array< T, SIZE> v1, std::array< T, SIZE> v2)
{
    static_assert(v1.size() == v2.size(), "The vectors are not the same size.");

    T result { 0 };

    for(std::size_t i = 0; i < v1.size(); i++)
    {
        result += v1[i] * v2[i];
    }

    return result;
}

// Matrizenmultiplakation: Matrix x Vektor
template <typename T, std::size_t SIZE_R, std::size_t SIZE_C>
std::array< T, SIZE_R> mvmul(std::array<std::array<T, SIZE_C>,SIZE_R> m, std::array< T, SIZE_C> v)
{
    static_assert(m[0].size() == v.size(), "The matrix and the vector are not the same size.");

    std::array<T, SIZE_R> result { 0 };

    for(std::size_t i = 0; i < m.size(); i++)
    {
        result[i] = vvmul(m[i], v);
    }

    return result;
}


#endif //MATRIX_H
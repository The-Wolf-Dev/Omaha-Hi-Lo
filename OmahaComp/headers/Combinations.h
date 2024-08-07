#ifndef COMBINATIONS_H
#define COMBINATIONS_H

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class Combinations
{
    std::vector<bool> m_mask;
    std::vector<T> m_source;
    size_t m_size;
    unsigned m_callsCount, m_elemCount;
public:
    Combinations(const std::vector<T>& source, unsigned elemCount)
        : m_source{ source }, m_elemCount{ elemCount }, m_size{ source.size() },
        m_mask(source.size()), m_callsCount{} {
        std::fill(m_mask.begin(), m_mask.begin() + m_elemCount, true);
    };
    bool generateCombination(std::vector<T>& result);
};

template<typename T>
bool Combinations<T>::generateCombination(std::vector<T>& result) {
    if (m_callsCount != 0U) {
        if (!std::prev_permutation(m_mask.begin(), m_mask.end())) {
            m_callsCount = 0U;
            return false;
        }
    }

    result.clear();

    for (size_t i{ 0U }; i < m_size; ++i) {
        if (m_mask[i]) {
            result.push_back(m_source[i]);
            //std::cout << m_source[i] << " ";
        }
    }

    ++m_callsCount;
    return true;
}

#endif // COMBINATIONS_H

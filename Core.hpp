// Created by peldax 20/12/2015

#pragma once

#include <array>
#include <vector>
#include <memory>

/* ********************************************************************************************** */

template<typename T, std::size_t size> using Array = std::array<T, size>;
template<typename T> using DynamicArray = std::vector<T>;
template<typename T> using SharedPtr = std::shared_ptr<T>;

using Values = DynamicArray<unsigned int>;
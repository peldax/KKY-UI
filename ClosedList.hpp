// Created by peldax 20/12/2015

#pragma once

#include <algorithm>
#include "Core.hpp"

/* ********************************************************************************************** */

class ClosedList
{
private:

    DynamicArray<Values> list;

public:

    inline const bool contains(const Values& element) const noexcept
    {
        auto ptr = std::find(list.begin(), list.end(), element);
        return ptr != list.end();
    }

    inline void addLast(const Values& element) noexcept
    {
        list.push_back(element);
    }
};

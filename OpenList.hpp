// Created by peldax 20/12/2015

#pragma once

#include "Core.hpp"
#include "Node.hpp"

/* ********************************************************************************************** */

class OpenList
{
private:

    DynamicArray<SharedPtr<Node>> list;

public:

    inline void addLast(SharedPtr<Node> element) noexcept
    {
        list.push_back(element);
    }

    inline void removeFirst() noexcept
    {
        list.erase(list.begin());
    }

    inline const bool isEmpty() const noexcept
    {
        return !list.size();
    }

    inline const unsigned int getValueFromFirstAt(unsigned int index) const noexcept
    {
        return list[0]->getValueAt(index);
    }

    inline const Values getValuesFromFirst() const noexcept
    {
        return list[0]->getValues();
    }

    inline SharedPtr<Node> getFirst() const noexcept
    {
        return list[0];
    }
};
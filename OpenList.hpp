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

    inline void addInPlace(const SharedPtr<Node> element) noexcept
    {
        if (isEmpty())
            addLast(element);

        auto it = list.begin();
        const auto rank = element->getRank();

        while (it != list.end() && (*it)->getRank() <= rank)
        {
            ++it;
        }
        list.insert(it, element);
    }

    inline void addLast(const SharedPtr<Node> element) noexcept
    {
        list.push_back(element);
    }

    inline void removeFirst() noexcept
    {
        list.erase(list.begin());
    }

    inline bool isEmpty() const noexcept
    {
        return !list.size();
    }

    inline const SharedPtr<Node>& getFirst() const noexcept
    {
        return list[0];
    }
};
// Created by peldax 20/12/2015

#pragma once

#include "Core.hpp"
#include "Node.hpp"

/* ********************************************************************************************** */

class OpenList
{
private:

    DynamicArray<SharedPtr<Node>> m_list;

public:

    inline void addInPlace(SharedPtr<Node> element) noexcept
    {
        const auto it = std::upper_bound(m_list.begin(), m_list.end(), element,
                [](const SharedPtr<Node>& lhs, const SharedPtr<Node>& rhs)
                {
                    return lhs->getRank() < rhs->getRank();
                }
        );

        m_list.insert(it, std::move(element));
    }

    inline void addLast(SharedPtr<Node> element) noexcept
    {
        m_list.push_back(std::move(element));
    }

    inline void removeFirst() noexcept
    {
        m_list.erase(m_list.begin());
    }

    inline bool isEmpty() const noexcept
    {
        return !m_list.size();
    }

    inline const SharedPtr<Node>& getFirst() const noexcept
    {
        return m_list[0];
    }
};
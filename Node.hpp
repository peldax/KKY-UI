// Created by peldax 20/12/2015

#pragma once

#include <limits.h>
#include "Core.hpp"

/* ********************************************************************************************** */

struct Path
{
    unsigned int m_from;
    unsigned int m_to;

    Path(unsigned int from = 0, unsigned int to = 0):
    m_from(from), m_to(to)
    {
        // Nothing to do.
    }
};

/* ********************************************************************************************** */

class Node
{

    Values m_values;

    SharedPtr<Node> m_parent;
    const Path m_path;

    unsigned int m_rank;

public:

    Node(
            Values values,
            SharedPtr<Node> parent = nullptr,
            const unsigned int from = 0,
            const unsigned int to = 0,
            const unsigned int rank = UINT_MAX):
    m_values(std::move(values)), m_parent(std::move(parent)), m_path(Path(from, to)), m_rank(rank)
    {
        // Nothing to do
    }

    inline const Values& getValues() const noexcept
    {
        return m_values;
    }

    inline const SharedPtr<Node>& getParent() const noexcept
    {
        return m_parent;
    }

    inline unsigned int getValueAt(unsigned int index) const noexcept
    {
        return m_values[index];
    }

    inline unsigned int getPathFrom() const noexcept
    {
        return m_path.m_from;
    }

    inline unsigned int getPathTo() const noexcept
    {
        return m_path.m_to;
    }

    inline unsigned int getRank() const noexcept
    {
        return m_rank;
    }

    inline bool isRoot() const noexcept
    {
        return m_parent == nullptr;
    }

    inline void printValues() const noexcept
    {
        for (const auto value : m_values)
        {
            std::cout << " " << value;
        }
        std::cout << "\n";
    }

    inline void printPath() const noexcept
    {
        std::cout
        << "Moved from unit #"
        << getPathFrom() + 1
        << " to unit #"
        << getPathTo() + 1
        << ".\n";
    }
};

/* ********************************************************************************************** */

inline bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.getValues() == rhs.getValues();
}

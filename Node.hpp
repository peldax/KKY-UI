// Created by peldax 20/12/2015

#pragma once

#include "Core.hpp"

/* ********************************************************************************************** */

class Node
{

public:

    struct Parent
    {
        SharedPtr<Node> m_parent;
        unsigned int m_from;
        unsigned int m_to;

        Parent(SharedPtr<Node> parent = nullptr, unsigned int from = 0, unsigned int to = 0):
        m_parent(parent), m_from(from), m_to(to)
        {
            // Nothing to do.
        }
    };

private:

    Values m_values;
    Parent m_parent;

public:

    Node(const Values& values, const Parent& parent = {}):
            m_values(values), m_parent(parent)
    {
        // Nothing to do
    }

    inline const Values getValues() const noexcept
    {
        return m_values;
    }

    inline const unsigned int getValueAt(unsigned int index) const noexcept
    {
        return m_values[index];
    }

    inline const Parent getParent() const noexcept
    {
        return m_parent;
    }
};

/* ********************************************************************************************** */

static bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.getValues() == rhs.getValues();
}

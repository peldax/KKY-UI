// Created by peldax 20/12/2015

#include "Executor.hpp"

/* ********************************************************************************************** */

void Executor::execute()
{
    unsigned int numberOfUnits;

    std::cout << "Insert number of units:\n> ";
    std::cin >> numberOfUnits;

    if (numberOfUnits == 0)
        return;

    // Load states and sizes

    loadSizes(numberOfUnits);
    loadDesired(numberOfUnits);
    Values initial = loadInitial(numberOfUnits);

    // Initiate open list

    SharedPtr<Node> root = std::make_shared<Node>(initial);
    m_openList.addLast(root);

    executeBFS();
}

void Executor::loadSizes(unsigned int numberOfUnits) noexcept
{
    m_sizes = Values(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        std::cout << "Insert maximum size of " << (i + 1) << ". unit:\n> ";
        std::cin >> m_sizes[i];
    }
}

void Executor::loadDesired(unsigned int numberOfUnits)
{
    m_desired = Values(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        std::cout << "Insert desired state of " << (i + 1) << ". unit:\n> ";
        std::cin >> m_desired[i];
        if (m_desired[i] > m_sizes[i])
            throw std::runtime_error("Desired value is bigger than units size.");
    }
}

Values Executor::loadInitial(unsigned int numberOfUnits) const
{
    Values initial(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        std::cout << "Insert initial state of " << (i + 1) << ". unit:\n> ";
        std::cin >> initial[i];
        if (initial[i] > m_sizes[i])
            throw std::runtime_error("Initial value is bigger than units size.");
    }

    return initial;
}

void Executor::executeBFS()
{
    while (!m_openList.isEmpty())
    {
        for (unsigned int j = 0; j < m_sizes.size(); j++)
        {
            auto jValue = m_openList.getValueFromFirstAt(j);

            // I have nothing to move because unit is empty.
            if (jValue == 0)
                continue;

            for (unsigned int k = 0; k < m_sizes.size(); k++)
            {
                if (k == j)
                    continue;

                auto kValue = m_openList.getValueFromFirstAt(k);

                // I cannot move anything here because target unit is full.
                if (kValue == m_sizes[k])
                    continue;

                // How much can I move to this unit.
                auto capacity = m_sizes[k] - kValue;

                // How much is actualy moved this iteration.
                auto change = std::min(capacity, jValue);

                // Perform.
                auto local = m_openList.getValuesFromFirst();
                local[j] -= change;
                local[k] += change;

                // Desired state check.
                if (local == m_desired)
                {
                    auto result = std::make_shared<Node>(local, Node::Parent(m_openList.getFirst(), j, k));
                    showSolution(result);
                    return;
                }

                // Close list check.
                if (m_closeList.contains(local))
                    continue;

                // Add new state to open list.
                auto ptr = std::make_shared<Node>(local, Node::Parent(m_openList.getFirst(), j, k));
                m_openList.addLast(ptr);
            }
        }
        // Add current state to close list.
        m_closeList.addLast(m_openList.getValuesFromFirst());
        // Remove current state from open list.
        m_openList.removeFirst();
    }
    std::cout << "No solution found.\n> ";
}

void Executor::showSolution(SharedPtr<Node> result) const noexcept
{
    while (true)
    {
        std::cout << "Current state:";

        for (auto value : result->getValues())
        {
            std::cout << " " << value;
        }

        auto parent = result->getParent();
        if (parent.m_parent == nullptr)
        {
            std::cout << "\n";
            break;
        }

        std::cout << ". Moved from unit #" << (parent.m_from + 1) << " to unit #" << (parent.m_to + 1) << "\n";
        result = parent.m_parent;
    }
}
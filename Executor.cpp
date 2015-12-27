// Created by peldax 20/12/2015

#include "Executor.hpp"

/* ********************************************************************************************** */

void Executor::load()
{
    unsigned int numberOfUnits;

    std::cout << "Insert number of units:\n> ";
    std::cin >> numberOfUnits;

    if (numberOfUnits <= 0)
        return;

    // Load states and sizes

    loadSizes(numberOfUnits);
    loadDesired(numberOfUnits);
    Values initial = loadInitial(numberOfUnits);

    execute(std::move(initial));
}

void Executor::loadArguments(int argc, char *argv[])
{
    if ((argc - 1) % 3 != 0)
    {
        std::cout << "Wrong arguments.";
        return;
    }

    unsigned int numberOfUnits = std::abs((argc - 1 ) / 3);

    unsigned int it = 1;

    m_sizes = Values(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        m_sizes[i] = std::abs(std::atoi(argv[it]));
        ++it;
    }

    m_desired = Values(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        m_desired[i] = std::abs(std::atoi(argv[it]));
        if (m_desired[i] > m_sizes[i])
            throw std::runtime_error("Desired value is bigger than units size.");
        ++it;
    }

    Values initial(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        initial[i] = std::abs(std::atoi(argv[it]));
        if (initial[i] > m_sizes[i])
            throw std::runtime_error("Initial value is bigger than units size.");
        ++it;
    }

    execute(std::move(initial));
}

void Executor::execute(Values initial)
{
    SharedPtr<Node> root = std::make_shared<Node>(std::move(initial));
    m_openList.addLast(std::move(root));

    executeBFS();
}

void Executor::loadSizes(const unsigned int numberOfUnits) noexcept
{
    m_sizes = Values(numberOfUnits);

    for (unsigned int i = 0; i < numberOfUnits; i++)
    {
        std::cout << "Insert maximum size of " << (i + 1) << ". unit:\n> ";
        std::cin >> m_sizes[i];
    }
}

void Executor::loadDesired(const unsigned int numberOfUnits)
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

Values Executor::loadInitial(const unsigned int numberOfUnits) const
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
        const auto current = m_openList.getFirst();

        m_openList.removeFirst();
        m_closedList.addLast(current->getValues());

        for (unsigned int j = 0; j < m_sizes.size(); j++)
        {
            const auto jValue = current->getValueAt(j);

            // I have nothing to move because unit is empty.
            if (jValue == 0)
                continue;

            for (unsigned int k = 0; k < m_sizes.size(); k++)
            {
                if (k == j)
                    continue;

                const auto kValue = current->getValueAt(k);

                // I cannot move anything here because target unit is full.
                if (kValue == m_sizes[k])
                    continue;

                // How much can I move to this unit.
                const auto capacity = m_sizes[k] - kValue;

                // How much is actually moved this iteration.
                const auto change = std::min(capacity, jValue);

                // Perform movement.
                auto local = current->getValues();
                local[j] -= change;
                local[k] += change;

                // Closed list check.
                if (m_closedList.contains(local))
                    continue;

                const auto rank = calculateRank(local);

                const auto node = std::make_shared<Node>(std::move(local), current, j, k, rank);

                if (rank == 0)
                {
                    showSolution(std::move(node));
                    return;
                }

                m_openList.addInPlace(std::move(node));
            }
        }
    }
    std::cout << "No solution found.\n> ";
}

unsigned int Executor::calculateRank(const Values& values) const noexcept
{
    unsigned int rank = 0u;

    for (unsigned int i = 0; i < values.size(); i++)
    {
        const int a = values[i] - m_desired[i];
        rank += std::abs(a);
    }

    return rank;
}

void Executor::showSolution(SharedPtr<Node> node) const noexcept
{
    Stack<SharedPtr<Node>> stack;

    // Push path to stack.
    stack.push(node);
    while (!stack.top()->isRoot())
    {
        stack.push(stack.top()->getParent());
    }

    // Print initial state.
    stack.top()->printValues();
    stack.pop();

    // Print children.
    do
    {
        stack.top()->printPath();
        stack.top()->printValues();
        stack.pop();
    }
    while (!stack.empty());
}
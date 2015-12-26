// Created by peldax 20/12/2015

#pragma once

#include <iostream>
#include "Core.hpp"
#include "Node.hpp"
#include "ClosedList.hpp"
#include "OpenList.hpp"

/* ********************************************************************************************** */

class Executor
{

private:

    Values m_sizes;
    Values m_desired;

    ClosedList m_closedList;
    OpenList m_openList;

public:

    Executor(const Values& sizes, const Values& desired):
    m_sizes(sizes), m_desired(desired)
    {
        // Nothing to do
    }

    Executor() = default;

    void load();
    void loadArguments(int argc, char *argv[]);
    void execute(const Values& initial);

private:

    void loadSizes(const unsigned int numberOfUnits) noexcept;
    void loadDesired(const unsigned int numberOfUnits);
    Values loadInitial(const unsigned int numberOfUnits) const;

    void executeBFS();

    unsigned int calculateRank(const Values& values) const noexcept;

    void showSolution(const SharedPtr<Node>& result) const noexcept;
};
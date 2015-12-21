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

    ClosedList m_closeList;
    OpenList m_openList;

public:

    void execute();

private:

    void loadSizes(unsigned int numberOfUnits) noexcept;
    void loadDesired(unsigned int numberOfUnits);
    Values loadInitial(unsigned int numberOfUnits) const;

    void executeBFS();

    void showSolution(SharedPtr<Node> result) const noexcept;
};
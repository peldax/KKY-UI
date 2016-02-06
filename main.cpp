// Created by peldax 20/12/2015

#include <exception>
#include <string>
#include <iostream>

#include "Executor.hpp"

/* ********************************************************************************************** */

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        try {
            Executor().loadArguments(argc, argv);
        }
        catch (const std::exception &ex) {
            std::cout << ex.what();
        }
    }
    else
    {
        while (true)
        {
            try
            {
                Executor().load();
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << "\n";

                std::string input;
                std::cout << "Would you like to try again? [y/n]\n>n ";
                std::cin >> input;
                if (input != "y")
                    break;
            }
        }
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include "../functions.h"

/**
 * @brief Prompts the user to either test another dataset or run another algorithm.
 *
 * This function presents the user with the option to either test another dataset
 * or run another algorithm. Based on the user's input, it either returns to the
 * main menu, reruns the algorithm selection, or exits the program.
 *
 * @param truck A reference to the Truck object, used if the user opts to run another algorithm.
 * @param pallets A constant reference to a vector of Pallet objects, used if the user opts to run another algorithm.
 */
void promptRestartOrExit(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::string input;
    char choice;
    // Ask the user whether they want to test another dataset
    std::cout << "Do you want test another dataset? (y/n): ";
    std::cin >> input;
    // Validate user input: only accept 'y' or 'n'
    while (input.size() != 1 || (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N'))
    {
        std::cout << "\nInvalid option. Please choose between y and n: ";
        std::cin >> input;
    }
    choice = input[0];
    // If yes, return to the main menu to select another dataset
    if (choice == 'y' || choice == 'Y')
    {
        showMainMenu();
    }
    else if (choice == 'n' || choice == 'N')
    {
        // If not, ask whether to run another algorithm on the same dataset
        std::cout << "\nDo you want to run another algorithm? (y/n): ";
        std::cin >> input;
        // Validate user input again
        while (input.size() != 1 || (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N'))
        {
            std::cout << "\nInvalid option. Please choose between y and n: ";
            std::cin >> input;
        }
        choice = input[0];
        // If yes, go back to algorithm selection with the same dataset
        if (choice == 'y' || choice == 'Y')
        {
            chooseAlgorithm(truck, pallets);
        }
        else if (choice == 'n' || choice == 'N')
        {
            // If no, exit the program gracefully
            std::cout << "\nThank you for using the program!\n";
            exit(0);
        }
    }
}
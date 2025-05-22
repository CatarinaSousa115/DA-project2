#include <iostream>
#include <vector>
#include <string>
#include "../functions.h"

void promptRestartOrExit(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::string input;
    char choice;

    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║                   NEXT ACTION                  ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    std::cout << "[1] Test another dataset\n";
    std::cout << "[2] Run another algorithm on the same dataset\n";
    std::cout << "[3] Exit\n";
    std::cout << "--------------------------------------------------\n";
    std::cout << "Your choice: ";
    std::cin >> input;

    while (input.size() != 1 || input[0] < '1' || input[0] > '3')
    {
        std::cout << "\nInvalid option. Please choose between 1 and 3: ";
        std::cin >> input;
    }

    choice = input[0];

    switch (choice)
    {
    case '1':
        // If the user chooses to test another dataset, go back to the main menu
        showMainMenu();
        break;
    case '2':
        // If the user chooses to run another algorithm on the same dataset, go back to algorithm selection
        chooseAlgorithm(truck, pallets);
        break;
    case '3':
        // If the user chooses to exit, print a thank you message and exit
        std::cout << "\nThank you for using the program!\n";
        exit(0);
    }
}
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "functions.h"

void displayMenu()
{
    int filenr;
    std::cout << "Please insert the number of the dataset to use: ";
    std::cin >> filenr;

    std::ostringstream fileTruckAndPallets;
    std::ostringstream filePallets;

    fileTruckAndPallets << "../datasets-extra/TruckAndPallets_"
                        << std::setw(2) << std::setfill('0') << filenr << ".csv";

    filePallets << "../datasets-extra/Pallets_"
                << std::setw(2) << std::setfill('0') << filenr << ".csv";

    std::ifstream fileTruck(fileTruckAndPallets.str());
    std::ifstream filePallet(filePallets.str());

    if (!fileTruck.is_open() && !filePallet.is_open())
    {
        std::cerr << "\nError: Files 'TruckAndPallets_"
                  << std::setw(2) << std::setfill('0') << filenr << ".csv' and/or 'Pallets_"
                  << std::setw(2) << std::setfill('0') << filenr << ".csv' do not exist or cannot be opened.\n";

        std::cout << "Please select another dataset.\n\n";
        displayMenu();
    }

    Truck truck = readTruckAndPallets(fileTruckAndPallets.str());

    std::vector<Pallet> pallets = readPallets(filePallets.str());

    chooseAlgorithm(truck, pallets);
}

void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets)
{
    int choice = 0;

    std::cout << "\n=== Select the algorithm to apply ===\n";
    std::cout << "[1] Brute-force (exhaustive)\n";
    std::cout << "[2] Dynamic programming\n";
    std::cout << "[3] Greedy algorithm\n";
    std::cout << "[4] Integer Linear Programming (ILP)\n";
    std::cout << "=====================================\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    while (choice < 1 || choice > 4)
    {
        std::cout << "Invalid option. Please choose between 1 and 4: ";
        std::cin >> choice;
    }

    if (choice == 1)
    {
        bruteForce(truck, pallets);
    }
}
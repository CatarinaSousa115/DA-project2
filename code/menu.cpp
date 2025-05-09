#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

#include "functions.h"

/**
 * @brief Displays the main menu of the application.
 * 
 * This function prints the program title and calls displayMenu() to begin user interaction.
 */
void showMainMenu()
{
    std::cout << "\n=== Delivery Truck Pallet Packing Optimization ===\n";
    displayMenu();
}

/**
 * @brief Prompts the user to select a dataset and loads the corresponding files.
 * 
 * This function constructs the filenames for the truck and pallet datasets based on user input,
 * validates the files, loads the data, and proceeds to algorithm selection.
 */
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

/**
 * @brief Allows the user to choose which algorithm to apply for pallet packing optimization.
 * 
 * Presents a list of available algorithms and calls the corresponding function based on user selection.
 * 
 * @param truck The truck configuration including capacity and number of pallets.
 * @param pallets The list of available pallets to consider.
 */
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

    switch (choice)
    {
    case 1:
        bruteForce(truck, pallets);
    case 2:
        dynamicProgramming(truck, pallets);
    }
}
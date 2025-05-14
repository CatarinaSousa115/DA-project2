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
    /// Ask user for dataset number to determine which files to load.
    int filenr;
    std::cout << "Please insert the number of the dataset to use: ";
    std::cin >> filenr;

    /// Construct the filenames for the truck and pallets CSV files.
    std::ostringstream fileTruckAndPallets;
    std::ostringstream filePallets;

    fileTruckAndPallets << "../datasets-extra/TruckAndPallets_"
                        << std::setw(2) << std::setfill('0') << filenr << ".csv";

    filePallets << "../datasets-extra/Pallets_"
                << std::setw(2) << std::setfill('0') << filenr << ".csv";

    std::ifstream fileTruck(fileTruckAndPallets.str());
    std::ifstream filePallet(filePallets.str());

    /// Check if both files could be opened; if not, prompt user to try again.
    if (!fileTruck.is_open() && !filePallet.is_open())
    {
        std::cerr << "\nError: Files 'TruckAndPallets_"
                  << std::setw(2) << std::setfill('0') << filenr << ".csv' and/or 'Pallets_"
                  << std::setw(2) << std::setfill('0') << filenr << ".csv' do not exist or cannot be opened.\n";

        std::cout << "Please select another dataset.\n\n";
        displayMenu();
    }

    /// Read truck data from the selected CSV file.
    Truck truck = readTruckAndPallets(fileTruckAndPallets.str());

    /// Read pallet data from the selected CSV file.
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
    char choice;

    std::cout << "\n=== Select the algorithm to apply ===\n";
    std::cout << "[1] Brute-force (exhaustive)\n";
    std::cout << "[2] Dynamic programming\n";
    std::cout << "[3] Greedy algorithm\n";
    std::cout << "[4] Integer Linear Programming (ILP)\n";
    std::cout << "[5] Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    while (choice < '1' || choice > '5')
    {
        std::cout << "\nInvalid option. Please choose between 1 and 5: ";
        std::cin >> choice;
    }

    switch (choice)
    {
    /// @note Brute-force method: tests all possible combinations (may be slow).
    case '1':
        bruteForce(truck, pallets);
    /// @note Dynamic programming: uses DP table to find optimal solution efficiently.
    case '2':
        dynamicProgramming(truck, pallets);
    /// @note Options [3] and [4] (Greedy, ILP) not yet implemented.
    /// Exit the program.
    case '5':
        std::cout << "\nThank you for using the program!\n";
        exit(0);
    }
}
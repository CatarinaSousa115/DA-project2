#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <fstream>

#include "../functions.h"

void showMainMenu()
{
    std::cout << "\n=== Delivery Truck Pallet Packing Optimization ===\n";
    displayMenu();
}

void displayMenu()
{
    std::string input;
    int filenr;

    std::cout << "Please insert the number of the dataset to use: ";
    std::cin >> input;

    if (input.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cout << "\nInvalid input. Please enter a valid number.\n\n";
        displayMenu();
    }

    filenr = std::stoi(input);

    std::ostringstream fileTruckAndPallets;
    std::ostringstream filePallets;

    fileTruckAndPallets << "../datasets/TruckAndPallets_"
                        << std::setw(2) << std::setfill('0') << filenr << ".csv";

    filePallets << "../datasets/Pallets_"
                << std::setw(2) << std::setfill('0') << filenr << ".csv";

    std::ifstream fileTruck(fileTruckAndPallets.str());
    std::ifstream filePallet(filePallets.str());

    /// Check if both files could be opened; if not, prompt user to try again.
    if (!fileTruck.is_open() || !filePallet.is_open())
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

void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::string input;
    char choice;

    std::cout << "\n=== Select the algorithm to apply ===\n";
    std::cout << "[1] Brute-force (exhaustive)\n";
    std::cout << "[2] Dynamic programming\n";
    std::cout << "[3] Greedy algorithm\n";
    std::cout << "[4] Hybrid algorithm\n";
    std::cout << "[5] Exit\n";
    std::cout << "=====================================\n";
    std::cout << "Your choice: ";
    std::cin >> input;
    while (input.size() != 1 || input[0] < '1' || input[0] > '5')
    {
        std::cout << "\nInvalid option. Please choose between 1 and 5: ";
        std::cin >> input;
    }
    choice = input[0];

    switch (choice)
    {
    /// @note Brute-force method: tests all possible combinations (may be slow).
    case '1':
        bruteForce(truck, pallets);
    /// @note Dynamic programming: uses DP table to find optimal solution efficiently.
    case '2':
        dynamicProgramming(truck, pallets);
    /// @note Greedy algorithm: selects pallets based on profit-to-weight ratio.
    case '3':
        greedyAlgorithm(truck, pallets);
    /// @note Hybrid algorithm: combines greedy and DP for improved performance.
    case '4':
        hybridAlgorithm(truck, pallets);
    /// @note Exit: terminates the program.
    case '5':
        std::cout << "\nThank you for using the program!\n";
        exit(0);
    }
}
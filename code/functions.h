#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <string>
#include <vector>
#include "Truck.h"
#include "Pallet.h"

/**
 * @brief Reads truck information from a file.
 * @param fileName Name of the file containing truck data.
 * @return A Truck object with loaded data.
 */
Truck readTruckAndPallets(const std::string &fileName);

/**
 * @brief Reads pallet information from a file.
 * @param fileName Name of the file containing pallet data.
 * @return A vector of Pallet objects.
 */
std::vector<Pallet> readPallets(const std::string &fileName);

int main();

/**
 * @brief Displays the main menu of the program.
 */
void showMainMenu();

/**
 * @brief Prompts the user to select a dataset and initiates the loading process.
 */
void displayMenu();

/**
 * @brief Lets the user choose and run one of the available optimization algorithms.
 * @param truck The truck object containing the capacity and number of pallets.
 * @param pallets The list of available pallets.
 */
void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the knapsack problem using brute-force.
 * @param truck Truck configuration.
 * @param pallets List of available pallets.
 */
void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the knapsack problem using dynamic programming.
 * @param truck Truck configuration.
 * @param pallets List of available pallets.
 */
void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Prints details of the selected pallets.
 * @param bestPallets Indices of the selected pallets.
 * @param pallets Complete list of pallets.
 */
void printPalletDetails(const std::vector<int> &bestPallets, const std::vector<Pallet> &pallets);

#endif
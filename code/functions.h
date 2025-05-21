#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <string>
#include <vector>
#include "structs/Truck.h"
#include "structs/Pallet.h"

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

/**
 * @brief Entry point of the program.
 * Handles the initial setup and triggers the main menu.
 * @return int Exit code.
 */
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

void greedyAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

void sortPallets(std::vector<Pallet> &pallets);

/**
 * @brief Prints details of the selected pallets.
 * @param bestPallets Indices of the selected pallets.
 * @param pallets Complete list of pallets.
 */
void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck);

/**
 * @brief Prompts the user to either test another dataset or run another algorithm.
 * @param truck The current truck configuration.
 * @param pallets List of pallets associated with the current dataset.
 */
void promptRestartOrExit(const Truck &truck, const std::vector<Pallet> &pallets);

void backtrack(const std::vector<Pallet> &pallets, int maxWeight, int index, int currentWeight,
               int currentProfit,
               std::vector<Pallet> &currentPallets, std::vector<Pallet> &bestPallets,
               int &maxProfit);

#endif
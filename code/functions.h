#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <string>
#include <vector>
#include "structs/Truck.h"
#include "structs/Pallet.h"

/**
 * @brief Reads truck information and associated pallets from a file.
 *
 * Parses the given file to load truck capacity and pallet details.
 *
 * @param fileName Name of the input file.
 * @return A Truck object containing the loaded data.
 */
Truck readTruckAndPallets(const std::string &fileName);

/**
 * @brief Reads pallet information from a file.
 *
 * Extracts a list of pallets from the specified file.
 *
 * @param fileName Name of the input file containing pallet data.
 * @return Vector of Pallet objects.
 */
std::vector<Pallet> readPallets(const std::string &fileName);

/**
 * @brief Program entry point.
 *
 * Sets up initial configuration and triggers the main menu.
 *
 * @return Exit status code.
 */
int main();

/**
 * @brief Displays the main menu to the user.
 */
void showMainMenu();

/**
 * @brief Presents dataset selection menu and handles dataset loading.
 */
void displayMenu();

/**
 * @brief Prompts the user to restart or exit the program after completing a task.
 *
 * @param truck The current truck configuration.
 * @param pallets The current list of pallets.
 */
void promptRestartOrExit(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Allows the user to choose and run an optimization algorithm.
 *
 * @param truck The truck configuration including capacity.
 * @param pallets The list of available pallets to choose from.
 */
void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the knapsack problem using brute-force search.
 *
 * Tries all combinations of pallets to find the optimal set within truck capacity.
 *
 * @param truck Truck configuration.
 * @param pallets List of pallets.
 */
void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Recursive helper for brute-force approach to generate pallet combinations.
 *
 * @param pallets List of available pallets.
 * @param maxWeight Maximum truck capacity.
 * @param index Current pallet index in recursion.
 * @param currentWeight Weight of current combination.
 * @param currentProfit Profit of current combination.
 * @param currentPallets Currently selected pallets in recursion.
 * @param bestPallets Best pallets combination found so far.
 * @param maxProfit Maximum profit found so far.
 */
void backtrack(const std::vector<Pallet> &pallets, int maxWeight, int index, int currentWeight,
               int currentProfit,
               std::vector<Pallet> &currentPallets, std::vector<Pallet> &bestPallets,
               int &maxProfit);

/**
 * @brief Solves the knapsack problem using dynamic programming.
 *
 * Uses DP table to compute the optimal subset of pallets within capacity constraints.
 *
 * @param truck Truck configuration.
 * @param pallets List of pallets.
 */
void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the knapsack problem using a greedy heuristic.
 *
 * Selects pallets by descending profit-to-weight ratio until capacity is reached.
 *
 * @param truck Truck configuration.
 * @param pallets List of pallets.
 */
void greedyAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Sorts pallets by descending profit-to-weight ratio.
 *
 * @param pallets Vector of pallets to sort.
 */
void sortPallets_ratio(std::vector<Pallet> &pallets);

/**
 * @brief Sorts pallets by ascending pallet ID.
 *
 * @param pallets Vector of pallets to sort.
 */
void sortPallets(std::vector<Pallet> &pallets);

/**
 * @brief Prints details about the selected pallets.
 *
 * @param bestPallets Vector of pallets selected as the best solution.
 * @param pallets Full list of available pallets.
 * @param truck Truck configuration.
 */
void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck);

#endif
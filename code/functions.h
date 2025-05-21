#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include <string>
#include <vector>
#include "structs/Truck.h"
#include "structs/Pallet.h"

/**
 * @brief Reads the truck's capacity and number of pallets from a CSV file.
 *
 * The function skips the header line and reads the second line,
 * extracting the truck capacity and the number of pallets.
 *
 * @param fileName Name of the CSV file containing the truck data.
 * @return Truck Struct with the loaded capacity and pallet count.
 */
Truck readTruckAndPallets(const std::string &fileName);

/**
 * @brief Reads pallet data from a CSV file.
 *
 * This function opens a CSV file, skips the header, and reads each line
 * to extract pallet ID, weight, and profit. It returns a vector of Pallet objects.
 *
 * @param fileName The name of the CSV file to read.
 * @return std::vector<Pallet> List of pallets read from the file.
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
 * @brief Displays the main menu of the application.
 *
 * This function prints the program title and calls displayMenu() to begin user interaction.
 */
void showMainMenu();

/**
 * @brief Prompts the user to select a dataset and loads the corresponding files.
 *
 * This function constructs the filenames for the truck and pallet datasets based on user input,
 * validates the files, loads the data, and proceeds to algorithm selection.
 */
void displayMenu();

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
void promptRestartOrExit(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Allows the user to choose which algorithm to apply for pallet packing optimization.
 *
 * Presents a list of available algorithms and calls the corresponding function based on user selection.
 *
 * @param truck The truck configuration including capacity and number of pallets.
 * @param pallets The list of available pallets to consider.
 */
void chooseAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the 0/1 knapsack problem using brute-force approach.
 *
 * This function tries every possible combination of pallets to find the subset
 * with the maximum profit that fits within the truck's weight capacity.
 *
 * @param truck The truck object containing the capacity and number of pallets.
 * @param pallets A vector of Pallet objects available to choose from.
 *
 * @note Time complexity: O(2^n), where n is the number of pallets.
 * @note Space complexity: O(n), where n is the number of pallets (due to the subset vectors).
 */
void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Recursive helper function to generate all possible combinations of pallets.
 *
 * This function uses backtracking to explore all possible subsets of pallets,
 * updating the combination with the highest profit that respects the truck's weight limit.
 *
 * @param pallets Vector of available Pallet objects.
 * @param maxWeight Maximum weight capacity of the truck.
 * @param index Current index in the pallets vector.
 * @param currentWeight Accumulated weight of the current combination.
 * @param currentProfit Accumulated profit of the current combination.
 * @param currentPallets Temporary vector holding the current combination of pallets.
 * @param bestPallets Vector storing the best combination of pallets found so far.
 * @param maxProfit Reference to the highest profit found.
 */
void backtrack(const std::vector<Pallet> &pallets, int maxWeight, int index, int currentWeight,
               int currentProfit,
               std::vector<Pallet> &currentPallets, std::vector<Pallet> &bestPallets,
               int &maxProfit);

/**
 * @brief Computes the sum of indices of a subset of pallets within the full pallet list.
 *
 * This helper function is used to break ties between equally profitable combinations
 * by preferring the one with the lower sum of original indices (i.e., chosen earlier).
 *
 * @param subset The selected subset of pallets being evaluated.
 * @param allPallets The full list of available pallets.
 * @return The sum of the indices of the subset pallets within the allPallets vector.
 */
int sumIndices(const std::vector<Pallet> &subset, const std::vector<Pallet> &allPallets);

/**
 * @brief Solves the 0/1 knapsack problem using dynamic programming.
 *
 * Fills a 2D table where each cell represents the maximum profit achievable using the first i pallets
 * with a given capacity w. Reconstructs the optimal set of pallets based on this table.
 *
 * @param truck The truck object with the capacity constraint.
 * @param pallets The list of pallets with associated weight and profit values.
 *
 * @note Time complexity: O(n * W), where n is the number of pallets and W is the truck's capacity.
 * @note Space complexity: O(n * W), due to the 2D DP table.
 */
void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Solves the 0/1 knapsack problem using a greedy heuristic.
 *
 * Sorts pallets by profit-to-weight ratio and selects as many as fit within
 * the truck's capacity. This does not guarantee an optimal solution but is efficient.
 *
 * @param truck The truck object with a defined capacity.
 * @param pallets The list of available pallets with weight and profit.
 *
 * @note Time complexity: O(n log n), where n is the number of pallets (due to sorting).
 * @note Space complexity: O(n), for storing sorted and selected pallets.
 */
void greedyAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Hybrid algorithm combining greedy and dynamic programming approaches.
 *
 * Executes a greedy algorithm to get an initial solution and profit, then runs a dynamic programming
 * algorithm with pruning to find an optimal or improved solution. Compares the final result with the greedy one.
 *
 * @param truck The truck object with a defined capacity.
 * @param pallets The list of available pallets with weight and profit.
 */
void hybridAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets);

/**
 * @brief Sorts pallets in descending order of profit-to-weight ratio.
 *
 * This function is used to prioritize pallets that provide the highest profit per unit of weight,
 * which is essential for the greedy approach to the 0/1 knapsack problem.
 * In case of ties, pallets are sorted by descending weight, and then ascending pallet ID.
 *
 * @param pallets Vector of pallets to be sorted.
 */
void sortPallets_ratio(std::vector<Pallet> &pallets);

/**
 * @brief Sorts pallets by their palletID in ascending order.
 *
 * This is used to maintain consistent order when displaying pallets.
 *
 * @param pallets Vector of pallets to be sorted.
 */
void sortPallets(std::vector<Pallet> &pallets);

/**
 *
 *
 * @brief Prints details about the selected pallets.
 *
 * This function iterates over the best pallets and prints their pallet number, weight, and profit.
 *
 * @param bestPallets A vector containing the pallet numbers of the best solution.
 * @param pallets A vector of all available Pallet objects.
 *@param truck Truck configuration.
 */
void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck);

#endif
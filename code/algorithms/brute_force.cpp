#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <limits>
#include "../functions.h"

/**
 * @brief Solves the 0/1 knapsack problem using brute-force approach.
 *
 * This function tries every possible combination of pallets to find the subset
 * with the maximum profit that fits within the truck's weight capacity.
 *
 * @param truck The truck object containing the capacity and number of pallets.
 * @param pallets A vector of Pallet objects available to choose from.
 *
 * @note Time complexity: O(n × 2^n), where n is the number of pallets.
 * @note Space complexity: O(n), where n is the number of pallets (due to the subset vectors).
 */
void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Brute-force Algorithm ===\n";
    auto start = std::chrono::high_resolution_clock::now();
    char choice;
    /// Warns the user if the number of pallets is too high for brute-force and prompts for confirmation.
    if (truck.numPallets >= 20)
    {
        std::cout << "The number of pallets is too high for the brute-force algorithm.\n";
        std::cout << "You really want to use this algorithm? (y/n): ";
        std::string input;
        std::cin >> input;
        while (input.size() != 1 || (input[0] != 'y' && input[0] != 'Y' && input[0] != 'n' && input[0] != 'N'))
        {
            std::cout << "\nInvalid option. Please choose between y and n: ";
            std::cin >> input;
        }
        choice = input[0];
        if (choice == 'n' || choice == 'N')
        {
            std::cout << "\nPlease choose another algorithm.\n";
            chooseAlgorithm(truck, pallets);
        }
        else if (choice == 'y' || choice == 'Y')
        {
            std::cout << "\nThis algorithm may take a considerable amount of time to run.\n";
            std::cout << "Please wait!\n";
        }
    }

    /// Stores the maximum profit found among all valid subsets.
    int max = 0;
    
    // Number of total combinations = 2^n (each pallet can be included or not)
    int numSubSet = pow(2, truck.numPallets);
    std::vector<int> bestPallets;

    /**
     * @brief Calculates all possible subsets and checks which ones are valid under the truck's capacity.
     *
     * Iterates through each subset represented by an integer bitmask, calculates the total weight and profit,
     * and updates the best solution if criteria are met.
     */
    for (int i = 0; i < numSubSet; i++)
    {
        /// Builds a subset of pallets and calculates its total weight and profit.
        int totalWeight = 0;
        int totalProfit = 0;
        std::vector<int> selectedPallets;

        for (int j = 0; j < truck.numPallets; j++)
        {
            // Checks if pallet j is included in the current subset (i's bitmask)
            if (i & (1 << j))
            {
                totalWeight += pallets[j].weight;
                totalProfit += pallets[j].profit;
                selectedPallets.push_back(pallets[j].palletID);
            }
        }

        /// Updates the best solution if the current subset is valid and more profitable or equally profitable but smaller.
        if (totalWeight <= truck.capacity &&
            (totalProfit > max || (totalProfit == max && bestPallets.size() > selectedPallets.size())))
        {
            max = totalProfit;
            bestPallets = selectedPallets;
        }
    }

    // If no valid subset was found (i.e., all exceed truck capacity)
    if (bestPallets.empty())
    {
        std::cout << "No valid combination of pallets found within capacity.\n";
        promptRestartOrExit(truck, pallets);
        return;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    // Print the pallets selected as the optimal solution
    printPalletDetails(bestPallets, pallets, truck);
}
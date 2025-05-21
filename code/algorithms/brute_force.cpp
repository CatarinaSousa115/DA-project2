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
 * @note Time complexity: O(2^n), where n is the number of pallets.
 * @note Space complexity: O(n), where n is the number of pallets (due to the subset vectors).
 */

 
void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Brute-force Algorithm ===\n";
    auto start = std::chrono::high_resolution_clock::now();
    char choice;
    /// Warns the user if the number of pallets is too high for brute-force and prompts for confirmation.
    if (truck.numPallets > 30)
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

    int maxWeight = truck.capacity;
    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    int maxProfit = 0;
    std::vector<Pallet> bestPallets;
    std::vector<Pallet> currentPallets;

    backtrack(pallets, maxWeight, 0, 0, 0, currentPallets, bestPallets, maxProfit);

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

    std::cout << "Maximum profit: " << maxProfit << "\n";

    // Print the pallets selected as the optimal solution
    printPalletDetails(bestPallets, pallets, truck);
}

void backtrack(const std::vector<Pallet> &pallets, int maxWeight, int index, int currentWeight,
               int currentProfit,
               std::vector<Pallet> &currentPallets, std::vector<Pallet> &bestPallets,
               int &maxProfit)
{
    // Base case: if the current index is equal to the number of pallets
    if (index == pallets.size())
    {
        if (currentProfit > maxProfit ||
            (currentProfit == maxProfit && currentPallets.size() < bestPallets.size()))

        {
            maxProfit = currentProfit;
            bestPallets = currentPallets;
        }
        return;
    }
    backtrack(pallets, maxWeight, index + 1, currentWeight, currentProfit, currentPallets, bestPallets, maxProfit);
    int newWeight = currentWeight + pallets[index].weight;
    if (newWeight <= maxWeight)
    {
        currentPallets.push_back(pallets[index]);
        backtrack(pallets, maxWeight, index + 1, newWeight,
                  currentProfit + pallets[index].profit,
                  currentPallets, bestPallets, maxProfit);
        currentPallets.pop_back();
    }
}

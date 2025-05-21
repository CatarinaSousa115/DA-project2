/**
 * @file brute_force.cpp
 * @brief Implements the brute-force algorithm for the 0/1 knapsack problem.
 *
 * Contains the main bruteForce function and its recursive helper (backtrack).
 * This algorithm explores all possible combinations of pallets to find the most profitable subset
 * that fits within the truck's weight capacity.
 */
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

    std::cout << "Maximum profit: " << maxProfit << "\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    // Print the pallets selected as the optimal solution
    printPalletDetails(bestPallets, pallets, truck);
}

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
// Helper function to sum indices of subset pallets in the original pallets vector
int sumIndices(const std::vector<Pallet> &subset, const std::vector<Pallet> &allPallets)
{
    int sum = 0;
    for (const auto &p : subset)
    {
        for (size_t i = 0; i < allPallets.size(); ++i)
        {
            if (p.palletID == allPallets[i].palletID)
            {
                sum += static_cast<int>(i);
                break;
            }
        }
    }
    return sum;
}

void backtrack(const std::vector<Pallet> &pallets, int maxWeight, int index, int currentWeight,
               int currentProfit,
               std::vector<Pallet> &currentPallets, std::vector<Pallet> &bestPallets,
               int &maxProfit)
{
    // Base case: if the current index is equal to the number of pallets
    if (index == pallets.size())
    {
        if (currentProfit > maxProfit)
        {
            maxProfit = currentProfit;
            bestPallets = currentPallets;
        }
        else if (currentProfit == maxProfit)
        {
            if (currentPallets.size() < bestPallets.size())
            {
                bestPallets = currentPallets;
            }
            else if (currentPallets.size() == bestPallets.size())
            {
                int currentSum = sumIndices(currentPallets, pallets);
                int bestSum = sumIndices(bestPallets, pallets);
                if (currentSum < bestSum)
                {
                    bestPallets = currentPallets;
                }
            }
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

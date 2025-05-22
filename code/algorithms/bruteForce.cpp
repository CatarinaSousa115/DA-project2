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

void bruteForce(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║              BRUTE-FORCE ALGORITHM             ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    auto start = std::chrono::high_resolution_clock::now();
    char choice;

    int maxWeight = truck.capacity;
    if (pallets.empty() || maxWeight <= 0)
    {
        // Exit early if there are no pallets or the truck has no capacity
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    int maxProfit = 0;
    std::vector<Pallet> usedPallets;
    std::vector<Pallet> currentPallets;

    // Start backtracking to find the best subset of pallets with maximum profit
    backtrack(pallets, maxWeight, 0, 0, 0, currentPallets, usedPallets, maxProfit);

    // If no valid subset was found (i.e., all exceed truck capacity)
    if (usedPallets.empty())
    {
        std::cout << "No valid combination of pallets found within capacity.\n";
        promptRestartOrExit(truck, pallets);
        return;
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Maximum profit: " << maxProfit << "\n";

    std::cout << "Number of pallets: " << usedPallets.size() << "\n";

    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    std::cout << "-------------------- PALLETS: --------------------\n";

    // Print the pallets selected as the optimal solution
    printPalletDetails(usedPallets, pallets, truck);
}

int sumIndices(const std::vector<Pallet> &subset, const std::vector<Pallet> &allPallets)
{
    // Calculate the sum of indices of the selected subset of pallets in the original pallet list
    int sum = 0;
    for (const auto &p : subset)
    {
        // Find the index of the current pallet in the full pallet list by matching palletID
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
        // Check if the current combination has a better profit than the best so far
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
    // Explore path where current pallet is not included
    backtrack(pallets, maxWeight, index + 1, currentWeight, currentProfit, currentPallets, bestPallets, maxProfit);
    int newWeight = currentWeight + pallets[index].weight;
    // Explore path where current pallet is included, if it doesn't exceed capacity
    if (newWeight <= maxWeight)
    {
        currentPallets.push_back(pallets[index]);
        backtrack(pallets, maxWeight, index + 1, newWeight,
                  currentProfit + pallets[index].profit,
                  currentPallets, bestPallets, maxProfit);
        // Backtrack: remove last added pallet to try next combination
        currentPallets.pop_back();
    }
}

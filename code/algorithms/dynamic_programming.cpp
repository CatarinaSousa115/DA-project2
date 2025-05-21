/**
 * @file dynamic_programming.cpp
 * @brief Implements the dynamic programming algorithm for the 0/1 knapsack problem.
 *
 * This file contains the function that calculates the most profitable combination of pallets
 * that fit within the truck's weight capacity using dynamic programming.
 */
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>

#include "../functions.h"

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
void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Dynamic Programming Algorithm ===\n";
    auto start = std::chrono::high_resolution_clock::now();

    int maxWeight = truck.capacity;
    int n = pallets.size();

    std::vector<std::vector<int>> bestProfitAtWeight(n + 1, std::vector<int>(maxWeight + 1, 0));

    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    for (int i = 1; i <= n; ++i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;
        for (int w = 0; w <= maxWeight; ++w)
        {
            if (w >= weight)
                bestProfitAtWeight[i][w] = std::max(bestProfitAtWeight[i - 1][w], bestProfitAtWeight[i - 1][w - weight] + profit);
            else
                bestProfitAtWeight[i][w] = bestProfitAtWeight[i - 1][w];
        }
    }
    std::vector<Pallet> usedPallets;
    int w = maxWeight;
    for (int i = n; i > 0 && w > 0; --i)
    {
        if (bestProfitAtWeight[i][w] != bestProfitAtWeight[i - 1][w])
        {
            usedPallets.push_back(pallets[i - 1]);
            w -= pallets[i - 1].weight;
        }
    }

    std::reverse(usedPallets.begin(), usedPallets.end());

    std::cout << "Maximum profit: " << bestProfitAtWeight[n][maxWeight] << "\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    printPalletDetails(usedPallets, pallets, truck);
}
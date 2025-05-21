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

    // Initialize DP tables to store maximum profit, minimum number of pallets, and sum of indices
    std::vector<std::vector<int>> bestProfitAtWeight(n + 1, std::vector<int>(maxWeight + 1, 0));
    std::vector<std::vector<int>> minPallets(n + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    minPallets[0][0] = 0;
    std::vector<std::vector<int>> sumIndices(n + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    sumIndices[0][0] = 0;

    // Handle edge case where there are no pallets or the truck capacity is zero
    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    // Fill DP tables based on each pallet and capacity
    for (int i = 1; i <= n; ++i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;
        for (int w = 0; w <= maxWeight; ++w)
        {
            // Check if current pallet can be included for the current weight
            if (w >= weight)
            {
                int includeProfit = bestProfitAtWeight[i - 1][w - weight] + profit;
                int excludeProfit = bestProfitAtWeight[i - 1][w];

                int includeCount = minPallets[i - 1][w - weight] + 1;
                int excludeCount = minPallets[i - 1][w];

                int includeSumIdx = sumIndices[i - 1][w - weight] + (i - 1);
                int excludeSumIdx = sumIndices[i - 1][w];

                if (includeProfit > excludeProfit)
                {
                    bestProfitAtWeight[i][w] = includeProfit;
                    minPallets[i][w] = includeCount;
                    sumIndices[i][w] = includeSumIdx;
                }
                else if (includeProfit < excludeProfit)
                {
                    bestProfitAtWeight[i][w] = excludeProfit;
                    minPallets[i][w] = excludeCount;
                    sumIndices[i][w] = excludeSumIdx;
                }
                else
                {
                    // Tie in profit, break tie by selecting the combination with fewer pallets
                    if (includeCount < excludeCount)
                    {
                        bestProfitAtWeight[i][w] = includeProfit;
                        minPallets[i][w] = includeCount;
                        sumIndices[i][w] = includeSumIdx;
                    }
                    else if (includeCount > excludeCount)
                    {
                        bestProfitAtWeight[i][w] = excludeProfit;
                        minPallets[i][w] = excludeCount;
                        sumIndices[i][w] = excludeSumIdx;
                    }
                    else
                    {
                        // Tie in number of pallets, break tie by selecting the combination with the smallest sum of indices
                        if (includeSumIdx < excludeSumIdx)
                        {
                            bestProfitAtWeight[i][w] = includeProfit;
                            minPallets[i][w] = includeCount;
                            sumIndices[i][w] = includeSumIdx;
                        }
                        else
                        {
                            bestProfitAtWeight[i][w] = excludeProfit;
                            minPallets[i][w] = excludeCount;
                            sumIndices[i][w] = excludeSumIdx;
                        }
                    }
                }
            }
            // If the pallet cannot be included, inherit values from the previous row
            else
            {
                bestProfitAtWeight[i][w] = bestProfitAtWeight[i - 1][w];
                minPallets[i][w] = minPallets[i - 1][w];
                sumIndices[i][w] = sumIndices[i - 1][w];
            }
        }
    }
    // Reconstruct the solution to find which pallets were used
    std::vector<Pallet> usedPallets;
    int w = maxWeight;
    for (int i = n; i > 0 && w > 0; --i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;

        if (w >= weight)
        {
            int includeProfit = bestProfitAtWeight[i - 1][w - weight] + profit;
            int includeCount = minPallets[i - 1][w - weight] + 1;
            int includeSumIdx = sumIndices[i - 1][w - weight] + (i - 1);

            if (bestProfitAtWeight[i][w] == includeProfit &&
                minPallets[i][w] == includeCount &&
                sumIndices[i][w] == includeSumIdx)
            {
                usedPallets.push_back(pallets[i - 1]);
                w -= weight;
            }
        }
    }

    // Reverse to get the order of pallets as selected
    std::reverse(usedPallets.begin(), usedPallets.end());

    // Output the results: maximum profit and execution time
    std::cout << "Maximum profit: " << bestProfitAtWeight[n][maxWeight] << "\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    printPalletDetails(usedPallets, pallets, truck);
}
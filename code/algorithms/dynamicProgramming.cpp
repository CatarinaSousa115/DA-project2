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

void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║          DYNAMIC PROGRAMMING ALGORITHM         ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";
    auto start = std::chrono::high_resolution_clock::now();

    int maxWeight = truck.capacity;
    int size = pallets.size();

    // Initialize DP tables to store maximum profit, minimum number of pallets, and sum of indices
    std::vector<std::vector<int>> bestProfit(size + 1, std::vector<int>(maxWeight + 1, 0));
    std::vector<std::vector<int>> minPallets(size + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    minPallets[0][0] = 0;
    std::vector<std::vector<int>> sumIndices(size + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    sumIndices[0][0] = 0;

    // Handle edge case where there are no pallets or the truck capacity is zero
    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    // Fill DP tables based on each pallet and capacity
    for (int i = 1; i <= size; ++i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;
        for (int w = 0; w <= maxWeight; ++w)
        {
            // Check if current pallet can be included for the current weight
            if (w >= weight)
            {
                int incProf = bestProfit[i - 1][w - weight] + profit;
                int excProf = bestProfit[i - 1][w];

                int incCount = minPallets[i - 1][w - weight] + 1;
                int excCount = minPallets[i - 1][w];

                int incID = sumIndices[i - 1][w - weight] + (i - 1);
                int excID = sumIndices[i - 1][w];

                if (incProf > excProf)
                {
                    bestProfit[i][w] = incProf;
                    minPallets[i][w] = incCount;
                    sumIndices[i][w] = incID;
                }
                else if (incProf < excProf)
                {
                    bestProfit[i][w] = excProf;
                    minPallets[i][w] = excCount;
                    sumIndices[i][w] = excID;
                }
                else
                {
                    // Tie in profit, break tie by selecting the combination with fewer pallets
                    if (incCount < excCount)
                    {
                        bestProfit[i][w] = incProf;
                        minPallets[i][w] = incCount;
                        sumIndices[i][w] = incID;
                    }
                    else if (incCount > excCount)
                    {
                        bestProfit[i][w] = excProf;
                        minPallets[i][w] = excCount;
                        sumIndices[i][w] = excID;
                    }
                    else
                    {
                        // Tie in number of pallets, break tie by selecting the combination with the smallest sum of indices
                        if (incID < excID)
                        {
                            bestProfit[i][w] = incProf;
                            minPallets[i][w] = incCount;
                            sumIndices[i][w] = incID;
                        }
                        else
                        {
                            bestProfit[i][w] = excProf;
                            minPallets[i][w] = excCount;
                            sumIndices[i][w] = excID;
                        }
                    }
                }
            }
            // If the pallet cannot be included, inherit values from the previous row
            else
            {
                bestProfit[i][w] = bestProfit[i - 1][w];
                minPallets[i][w] = minPallets[i - 1][w];
                sumIndices[i][w] = sumIndices[i - 1][w];
            }
        }
    }
    // Reconstruct the solution to find which pallets were used
    std::vector<Pallet> usedPallets;
    int w = maxWeight;
    for (int i = size; i > 0 && w > 0; --i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;

        if (w >= weight)
        {
            int incP = bestProfit[i - 1][w - weight] + profit;
            int incC = minPallets[i - 1][w - weight] + 1;
            int incS = sumIndices[i - 1][w - weight] + (i - 1);

            if (bestProfit[i][w] == incP &&
                minPallets[i][w] == incC &&
                sumIndices[i][w] == incS)
            {
                usedPallets.push_back(pallets[i - 1]);
                w -= weight;
            }
        }
    }

    // Reverse to get the order of pallets as selected
    std::reverse(usedPallets.begin(), usedPallets.end());

    auto end = std::chrono::high_resolution_clock::now();
    
    // Output the results: maximum profit and execution time
    std::cout << "Maximum profit: " << bestProfit[size][maxWeight] << "\n";

    std::cout << "Number of pallets: " << usedPallets.size() << "\n";

    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    printPalletDetails(usedPallets, pallets, truck);
}
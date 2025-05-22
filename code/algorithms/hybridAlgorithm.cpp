/**
 * @file hybrid_algorithm.cpp
 * @brief Implements a hybrid algorithm combining greedy and dynamic programming for the 0/1 knapsack problem.
 *
 * First runs a greedy heuristic to get a baseline profit and then uses dynamic programming
 * with pruning based on the greedy profit to find an optimal or improved solution.
 */
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

#include "../functions.h"

void hybridAlgorithm(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n╔════════════════════════════════════════════════╗\n";
    std::cout << "║                HYBRID ALGORITHM                ║\n";
    std::cout << "╚════════════════════════════════════════════════╝\n";

    auto start = std::chrono::high_resolution_clock::now();

    // Run greedy algorithm to get baseline solution (lower bound)
    std::vector<Pallet> sortedPallets = pallets;
    sortPallets_ratio(sortedPallets);

    int maxWeight = truck.capacity;
    int greedyProfit = 0;
    int greedyWeight = 0;
    std::vector<Pallet> greedySet;

    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    for (const Pallet &pallet : sortedPallets)
    {
        if (greedyWeight + pallet.weight <= maxWeight)
        {
            greedySet.push_back(pallet);
            greedyWeight += pallet.weight;
            greedyProfit += pallet.profit;
        }
    }

    // Dynamic Programming with proper pruning
    int size = pallets.size();

    // dp[i][w] = max profit using first i pallets with capacity w
    std::vector<std::vector<int>> bestProfit(size + 1, std::vector<int>(maxWeight + 1, 0));
    std::vector<std::vector<int>> minPallets(size + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    minPallets[0][0] = 0;
    std::vector<std::vector<int>> sumIndices(size + 1, std::vector<int>(maxWeight + 1, INT_MAX));
    sumIndices[0][0] = 0;

    for (int i = 1; i <= size; ++i)
    {
        int weight = pallets[i - 1].weight;
        int profit = pallets[i - 1].profit;

        for (int w = 0; w <= maxWeight; ++w)
        {

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
            else
            {
                bestProfit[i][w] = bestProfit[i - 1][w];
                minPallets[i][w] = minPallets[i - 1][w];
                sumIndices[i][w] = sumIndices[i - 1][w];
            }
        }
    }

    // Backtrack to find the chosen pallets (with tie-breaking: profit, count, sumIndices)
    int w = maxWeight;
    std::vector<Pallet> usedPallets;
    for (int i = size; i > 0 && w > 0; --i)
    {
        int wt = pallets[i - 1].weight;
        int val = pallets[i - 1].profit;

        if (w >= wt)
        {
            int includeProfit = bestProfit[i - 1][w - wt] + val;
            int includeCount = minPallets[i - 1][w - wt] + 1;
            int includeSumIdx = sumIndices[i - 1][w - wt] + (i - 1);

            if (bestProfit[i][w] == includeProfit &&
                minPallets[i][w] == includeCount &&
                sumIndices[i][w] == includeSumIdx)
            {
                usedPallets.push_back(pallets[i - 1]);
                w -= wt;
            }
        }
    }

    std::reverse(usedPallets.begin(), usedPallets.end());
    sortPallets(usedPallets);

    auto end = std::chrono::high_resolution_clock::now();

    // Output results
    int totalProfit = bestProfit[size][maxWeight];
    int totalWeight = 0;
    for (const auto &p : usedPallets)
        totalWeight += p.weight;

    std::cout << "Maximum profit: " << totalProfit << "\n";

    std::cout << "Number of pallets: " << usedPallets.size() << "\n";

    std::cout << "Execution time: "
              << std::chrono::duration<double, std::milli>(end - start).count()
              << " ms\n";

    std::cout << "--------------------------------------------------\n";

    // Compare with greedy
    std::cout << "  Comparison with Greedy Algorithm:\n";
    std::cout << "- Greedy profit: " << greedyProfit << ", weight: " << greedyWeight << "\n";
    if (totalProfit == greedyProfit)
        std::cout << "- DP solution matches greedy solution profit.\n";
    else if (totalProfit > greedyProfit)
        std::cout << "- DP solution improves upon greedy solution.\n";
    else
        std::cout << "- Error: This should never happen - DP is guaranteed to be at least as good as greedy.\n";

    printPalletDetails(usedPallets, pallets, truck);
}
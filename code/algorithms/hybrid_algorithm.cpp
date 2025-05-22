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

    if (pallets.empty() || truck.capacity <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    // Run greedy algorithm to get baseline solution (lower bound)
    std::vector<Pallet> sortedPallets = pallets;
    sortPallets_ratio(sortedPallets);

    int maxWeight = truck.capacity;
    int greedyProfit = 0;
    int greedyWeight = 0;
    std::vector<Pallet> greedySet;

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
    int n = pallets.size();
    int W = maxWeight;

    // dp[i][w] = max profit using first i pallets with capacity w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        int wt = pallets[i - 1].weight;
        int val = pallets[i - 1].profit;

        for (int w = 0; w <= W; ++w)
        {
            if (wt > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
            }
        }

        // Early termination if we've already found a solution better than greedy
        if (dp[i][W] >= greedyProfit && i < n)
        {
            // Check if remaining items can't possibly improve the solution
            int remainingMaxProfit = 0;
            int remainingCapacity = W;
            for (int j = i + 1; j <= n; ++j)
            {
                if (pallets[j - 1].weight <= remainingCapacity)
                {
                    remainingMaxProfit += pallets[j - 1].profit;
                    remainingCapacity -= pallets[j - 1].weight;
                }
            }

            if (dp[i][W] >= greedyProfit + remainingMaxProfit)
            {
                break; // No need to continue
            }
        }
    }

    // Backtrack to find the chosen pallets
    int resProfit = dp[n][W];
    int w = W;
    std::vector<Pallet> usedPallets;

    for (int i = n; i > 0 && resProfit > 0; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            usedPallets.push_back(pallets[i - 1]);
            w -= pallets[i - 1].weight;
            resProfit -= pallets[i - 1].profit;
        }
    }

    std::reverse(usedPallets.begin(), usedPallets.end());
    sortPallets(usedPallets);

    auto end = std::chrono::high_resolution_clock::now();

    // Output results
    int totalProfit = dp[n][W];
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
    std::cout << "-------------------- PALLETS: --------------------\n";

    printPalletDetails(usedPallets, pallets, truck);
}
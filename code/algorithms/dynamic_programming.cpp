#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <chrono>

#include "../functions.h"

void dynamicProgramming(const Truck &truck, const std::vector<Pallet> &pallets)
{
    std::cout << "\n=== Dynamic Programming Algorithm ===\n";
    auto start = std::chrono::high_resolution_clock::now();

    int maxWeight = truck.capacity;
    int n = pallets.size();

    std::vector<int> bestProfitAtWeight(maxWeight + 1, 0);
    std::vector<int> palletCountAtWeight(maxWeight + 1, INT_MAX);
    std::vector<int> previousWeight(maxWeight + 1, -1);
    std::vector<int> chosenPalletIndex(maxWeight + 1, -1);
    palletCountAtWeight[0] = 0;

    if (pallets.empty() || maxWeight <= 0)
    {
        std::cout << "No pallets available or 0 capacity" << std::endl;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        int weight = pallets[i].weight;
        int profit = pallets[i].profit;
        for (int w = maxWeight; w >= 0; --w)
        {
            if (w >= weight && chosenPalletIndex[w - weight] != i)
            {
                int prevW = w - weight;
                int newProfit = bestProfitAtWeight[prevW] + profit;
                int newusedPallets = palletCountAtWeight[prevW] + 1;
                if (newProfit > bestProfitAtWeight[w] || (newProfit == bestProfitAtWeight[w] && newusedPallets < palletCountAtWeight[w]))
                {
                    bestProfitAtWeight[w] = newProfit;
                    palletCountAtWeight[w] = newusedPallets;
                    previousWeight[w] = prevW;
                    chosenPalletIndex[w] = i;
                }
            }
        }
    }
    int maxProfit = bestProfitAtWeight[maxWeight];

    std::vector<Pallet> usedMaxProfitPallets;
    std::vector<bool> used(n, false);
    int w = maxWeight;

    while (w > 0 && chosenPalletIndex[w] != -1)
    {
        int idx = chosenPalletIndex[w];
        if (!used[idx]) {
            usedMaxProfitPallets.push_back(pallets[idx]);
            used[idx] = true;
        }
        w = previousWeight[w];
    }
    std::reverse(usedMaxProfitPallets.begin(), usedMaxProfitPallets.end());

    std::cout << "Maximum profit: " << maxProfit << "\n";

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    printPalletDetails(usedMaxProfitPallets, pallets, truck);
}
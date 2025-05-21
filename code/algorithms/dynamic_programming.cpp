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
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    printPalletDetails(usedPallets, pallets, truck);
}
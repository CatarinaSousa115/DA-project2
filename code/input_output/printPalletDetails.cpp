#include <iostream>
#include "../functions.h"

/**
 * @brief Prints the details of the selected pallets.
 *
 * This function iterates over the best pallets and prints their pallet number, weight, and profit.
 *
 * @param bestPallets A vector containing the pallet numbers of the best solution.
 * @param pallets A vector of all available Pallet objects.
 */
void printPalletDetails(const std::vector<Pallet> &bestPallets, const std::vector<Pallet> &pallets, const Truck &truck)
{
    for (Pallet pallet : bestPallets)
    {
        std::cout << pallet.palletID << ", " << pallet.weight << ", " << pallet.profit << "\n";
    }

    std::cout << "\n";

    promptRestartOrExit(truck, pallets);
}

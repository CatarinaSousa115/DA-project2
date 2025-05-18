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
void printPalletDetails(const std::vector<int> &bestPallets, const std::vector<Pallet> &pallets)
{
    for (int i : bestPallets)
    {
        for (Pallet pallet : pallets)
        {
            if (pallet.pallet == i)
            {
                std::cout << pallet.pallet << ", " << pallet.weight << ", " << pallet.profit << "\n";
            }
        }
    }
}

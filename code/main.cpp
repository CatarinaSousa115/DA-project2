#include <iostream>
#include "functions.h"

int main()
{
    Truck truck = readTruckAndPallets("../datasets-extra/TruckAndPallets_05.csv");
    std::vector<Pallet> pallets = readPallets("../datasets-extra/Pallets_05.csv");
    std::cout << truck.capacity << std::endl;
    std::cout << truck.numPallets << std::endl;
    std::cout << pallets[0].pallet << std::endl;
    std::cout << pallets[0].weight << std::endl;
    std::cout << pallets[0].profit << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
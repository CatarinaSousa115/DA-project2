#ifndef PALLET_H
#define PALLET_H

/**
 * @brief Represents a pallet to be loaded onto a truck.
 * 
 * Contains the pallet ID, its weight, and associated profit.
 */
struct Pallet
{
    int pallet; // Pallet ID
    int weight; // Weight of the pallet
    int profit; // Profit of the pallet
};

#endif //PALLET_H
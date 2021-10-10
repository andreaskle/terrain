#ifndef GRID_H_
#define GRID_H_
#include <vector>

#include "vertex.h"
/**
 *  Creates a triangle grid with the given number of tiles in x and z
 * @param numTilesX the number of tiles in x direction
 * @param numTilesZ the number of tiles in z direction
 * @param vertices the resulting vertices of the grid
 * @param indices the resulting indices of the grid
 */
void CreateGrid(int numTilesX, int numTilesZ, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
#endif
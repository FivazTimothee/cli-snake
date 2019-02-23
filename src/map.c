#include <stdio.h>
#include <stdlib.h>

#include "map.h"

/** @brief Skins (i.e. char displayed) for each possible cell state */
char cell_skins[CELL_TYPE_COUNT] = {[CELL_EMPTY] = ' ',
                                    [CELL_FRUIT] = '@',
                                    [CELL_SNAKE_HEAD] = 'O',
                                    [CELL_SNAKE_BODY] = '*'};

/** @brief Game map where every cell is memorized */
static cell_t game_map[MAP_SIZE_V][MAP_SIZE_H];

void map_clear(void) {
  // Initialize all the cells as empty
  for (int row = 0; row < MAP_SIZE_V; row++) {
    for (int col = 0; col < MAP_SIZE_H; col++) {
      game_map[row][col] = CELL_EMPTY;
    }
  }
}


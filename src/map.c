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

void map_init_snake(int size) {
  map_set_cell(MAP_SIZE_V / 2, MAP_SIZE_H / 2, CELL_SNAKE_HEAD);

  for (int i = 1; i < size; i++) {
    map_set_cell(MAP_SIZE_V / 2, (MAP_SIZE_H / 2) - i, CELL_SNAKE_BODY);
  }
}

void map_set_cell(int row, int column, cell_t new_state) {
  game_map[row][column] = new_state;
}


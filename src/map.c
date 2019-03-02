#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"

/** @brief Skins (i.e. char displayed) for each possible cell state */
char cell_skins[CELL_TYPE_COUNT] = {[CELL_EMPTY] = ' ',
                                    [CELL_FRUIT] = '@',
                                    [CELL_SNAKE_HEAD] = 'O',
                                    [CELL_SNAKE_BODY] = '*',
                                    [CELL_SNAKE_BODY_FULL] = '+'};

/** @brief Game map where every cell is memorized */
static cell_t game_map[MAP_SIZE_V][MAP_SIZE_H];

void map_init(void) {
  // Initialize all the cells as empty
  for (int row = 0; row < MAP_SIZE_V; row++) {
    for (int col = 0; col < MAP_SIZE_H; col++) {
      game_map[row][col] = CELL_EMPTY;
    }
  }

  srand(time(NULL));  // Initialize pseudo-random generator
}

void map_set_cell(int row, int column, cell_t new_state) {
  game_map[row][column] = new_state;
}

cell_t map_get_cell(int row, int column) {
  cell_t cell;
  cell = (row >= MAP_SIZE_V) ? CELL_EMPTY
                             : (column >= MAP_SIZE_H) ? CELL_EMPTY : game_map[row][column];
  return cell;
}

void map_place_fruit(void) {
  int x = rand() % MAP_SIZE_V;
  int y = rand() % MAP_SIZE_H;

  while (game_map[x][y] != CELL_EMPTY) {
    x = rand() % MAP_SIZE_V;
    y = rand() % MAP_SIZE_H;
  }

  game_map[x][y] = CELL_FRUIT;
}

void map_render(void) {
  static char map_str_array[MAP_SIZE_V][MAP_SIZE_H + 1];
  static char hash_line_str[MAP_SIZE_H + 3];

  memset(hash_line_str, '#', MAP_SIZE_H + 2);
  hash_line_str[MAP_SIZE_H + 2] = '\0';

  for (int row = 0; row < MAP_SIZE_V; row++) {
    for (int col = 0; col < MAP_SIZE_H; col++) {
      map_str_array[row][col] = cell_skins[game_map[row][col]];
    }
    map_str_array[row][MAP_SIZE_H] = '\0';
  }

  printf("\e[1;1H\e[2J");           // Clear console
  printf("%s\r\n", hash_line_str);  // Print hash line
  for (int row = 0; row < MAP_SIZE_V; row++) {
    printf("#%s#\r\n", map_str_array[row]);  // Print one row
  }
  printf("%s\r\n", hash_line_str);  // Print hash line
}

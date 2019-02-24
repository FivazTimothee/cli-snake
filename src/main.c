/**
 * @brief Application entry point
 */

#include <stdio.h>
#include <stdlib.h>

#include "map.h"

/**
 * @brief Game entry point
 *
 * @return EXIT_SUCCESS
 */
int main(void) {
  printf("Hello, world!\r\n");

  snake_part_t* snake_head = snake_create(10, MAP_SIZE_V / 2, MAP_SIZE_H / 2);
  map_clear();
  snake_place_on_map(snake_head);
  map_render();

  snake_destroy(snake_head);

  return EXIT_SUCCESS;
}

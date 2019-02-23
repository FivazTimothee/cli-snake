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

  map_clear();
  map_init_snake(8);
  map_render();

  return EXIT_SUCCESS;
}

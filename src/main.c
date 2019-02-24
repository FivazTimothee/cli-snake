/**
 * @brief Application entry point
 */

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "map.h"

/**
 * @brief Game entry point
 *
 * @return EXIT_SUCCESS
 */
int main(void) {
  game_loop();

  return EXIT_SUCCESS;
}

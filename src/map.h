/**
 * @brief Module managing the game map, including modifying and rendering cells
 */

/** @brief Number of vertical cells in the map */
#define MAP_SIZE_V 30

/** @brief Number of horizontal cells in the map */
#define MAP_SIZE_H 40

/** @brief Possible states for a cell */
typedef enum {
  CELL_EMPTY,
  CELL_FRUIT,
  CELL_SNAKE_HEAD,
  CELL_SNAKE_BODY,
  CELL_TYPE_COUNT
} cell_t;

/** @brief Clear the game map, i.e. empty all its cells */
void map_clear(void);


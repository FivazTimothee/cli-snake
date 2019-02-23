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

/**
 * @brief Initialize the snake in the middle of the screen
 * @param row        The size of the snake (number of cells)
 */
void map_init_snake(int size);

/**
 * @brief Modify the state of a cell
 * @param row        The row index of the cell to modify
 * @param column     The column index of the cell to modify
 * @param new_state  The state to apply to the given cell
 */
void map_set_cell(int row, int column, cell_t new_state);


/**
 * @brief Module managing the game map, including modifying and rendering cells
 */

/** @brief Number of vertical cells in the map */
#define MAP_SIZE_V 30

/** @brief Number of horizontal cells in the map */
#define MAP_SIZE_H 40

#define COLUMN_INDEX_LEFT(column_index) ((column_index > 0) ? (column_index - 1) : (MAP_SIZE_H - 1))

#define COLUMN_INDEX_RIGHT(column_index) \
  ((column_index < (MAP_SIZE_H - 1)) ? (column_index + 1) : 0)

#define ROW_INDEX_UP(row_index) ((row_index > 0) ? (row_index - 1) : (MAP_SIZE_V - 1))

#define ROW_INDEX_DOWN(row_index) ((row_index < (MAP_SIZE_V - 1)) ? (row_index + 1) : 0)

/** @brief Possible states for a cell */
typedef enum { CELL_EMPTY, CELL_FRUIT, CELL_SNAKE_HEAD, CELL_SNAKE_BODY, CELL_TYPE_COUNT } cell_t;

/** @brief Clear the game map, i.e. empty all its cells */
void map_clear(void);

/**
 * @brief Modify the state of a cell
 * @param row        The row index of the cell to modify
 * @param column     The column index of the cell to modify
 * @param new_state  The state to apply to the given cell
 */
void map_set_cell(int row, int column, cell_t new_state);

/** @brief Render the game map to the console */
void map_render(void);

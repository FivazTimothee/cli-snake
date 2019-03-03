/**
 * @brief Module managing the snake character
 */

/** @brief Structure representing the part of a snake, which works as a linked list of parts */
typedef struct snake_part {
  unsigned int row_index;
  unsigned int column_index;
  void* prev_part;
  void* next_part;
} snake_part_t;

typedef void (*fruit_eaten_callback_t)(void);
typedef void (*snake_collision_callback_t)(void);

/**
 * @brief Create a new snake at a given position and with a given size
 *
 * @param size               The number of parts composing the snake
 * @param head_row           The row at which the head will be placed
 * @param head_column        The column at which the head will be placed
 * @param fruit_callback     The function to call when the snake eats a fruit
 * @param collision_callback The function to call when the snake runs into himself
 *
 * @return A pointer on the created snake's head
 */
snake_part_t* snake_create(unsigned int size,
                           unsigned int head_row,
                           unsigned int head_col,
                           fruit_eaten_callback_t fruit_callback,
                           snake_collision_callback_t collision_callback);

/**
 * @brief Place the snake on the game map, i.e. set the map cells state concerned by the snake
 *
 * @param snake_head A pointer on the head of the snake to place on the map
 */
void snake_place_on_map(snake_part_t* snake_head);

/**
 * @brief Move a snake one cell up
 *
 * @param snake_head A pointer on the head of the snake to move
 *
 * @return A pointer on the new head
 */
snake_part_t* snake_move_up(snake_part_t* snake_head);

/**
 * @brief Move a snake one cell down
 *
 * @param snake_head A pointer on the head of the snake to move
 *
 * @return A pointer on the new head
 */
snake_part_t* snake_move_down(snake_part_t* snake_head);

/**
 * @brief Move a snake one cell left
 *
 * @param snake_head A pointer on the head of the snake to move
 *
 * @return A pointer on the new head
 */
snake_part_t* snake_move_left(snake_part_t* snake_head);

/**
 * @brief Move a snake one cell right
 *
 * @param snake_head A pointer on the head of the snake to move
 *
 * @return A pointer on the new head
 */
snake_part_t* snake_move_right(snake_part_t* snake_head);

/**
 * @brief Destroy a snake, i.e. free its memory and empty its cells on the map
 *
 * param snake_head A pointer on the head of the snake to destroy
 */
void snake_destroy(snake_part_t* snake_head);

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

/**
 * @brief Create a new snake at a given position and with a given size
 *
 * @param size        The number of parts composing the snake
 * @param head_row    The row at which the head will be placed
 * @param head_column The column at which the head will be placed
 *
 * @return A pointer on the created snake's head
 */
snake_part_t* snake_create(unsigned int size, unsigned int head_row, unsigned int head_col);


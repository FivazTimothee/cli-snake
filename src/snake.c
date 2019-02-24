#include <stdlib.h>
#include <string.h>

#include "map.h"
#include "snake.h"

/**
 * @brief Helper to create/allocate a new snake part and make sure it's empty
 *
 * @return A pointer on the snake part created
 */
static snake_part_t* new_empty_part(void) {
  snake_part_t* new_part = (snake_part_t*)malloc(sizeof(snake_part_t));
  memset(new_part, 0, sizeof(snake_part_t));
  return new_part;
}

snake_part_t* snake_create(unsigned int size, unsigned int head_row, unsigned int head_col) {
  snake_part_t* head = new_empty_part();
  head->row_index = head_row;
  head->column_index = head_col;

  snake_part_t* current_part = head;

  for (int i = 1; i < size; i++) {
    // Create a new empty snake part
    snake_part_t* new_part = new_empty_part();

    // Set the pointers to the next and prev elkements for both parts
    new_part->next_part = current_part;
    current_part->prev_part = new_part;

    // Give a correct position to the part
    new_part->row_index = current_part->row_index;
    new_part->column_index = COLUMN_INDEX_LEFT(current_part->column_index);

    // Set current part pointer to the new part
    current_part = new_part;
  }

  return head;
}


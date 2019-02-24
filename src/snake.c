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

/**
 * @brief Helper to remove the tail of a snake, i.e. free its memory and empty its cell on the map
 *
 * @return A pointer on the snake head (or any part of the snake, actually)
 */
static void remove_tail(snake_part_t* snake_head) {
  if (snake_head) {
    snake_part_t* current_part = snake_head;

    // Find the tail
    while (current_part->prev_part) {
      current_part = current_part->prev_part;
    }

    // Empty its cell, set new tail and free the memory
    snake_part_t* new_tail = current_part->next_part;
    map_set_cell(current_part->row_index, current_part->column_index, CELL_EMPTY);
    new_tail->prev_part = NULL;
    free(current_part);
  }
}

/**
 * @brief Helper to move a snake to a given cell. This cell MUST BE adjacent to the snake's head
 *
 * @param snake_head   A pointer on the head of the snake to move
 * @param row         The index of the row where the new head goes
 * @param column      The index of the column where the new head goes
 *
 * @return A pointer on the snake new head
 */
static snake_part_t* move_to(snake_part_t* snake_head, int row, int column) {
  // Create new head
  snake_part_t* new_head = new_empty_part();
  snake_head->next_part = new_head;
  new_head->prev_part = snake_head;
  new_head->row_index = row;
  new_head->column_index = column;
  map_set_cell(new_head->row_index, new_head->column_index, CELL_SNAKE_HEAD);

  // Change previous head to body
  map_set_cell(snake_head->row_index, snake_head->column_index, CELL_SNAKE_BODY);

  remove_tail(snake_head);
  return new_head;
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

void snake_place_on_map(snake_part_t* snake_head) {
  if (snake_head) {
    snake_part_t* snake_part;

    // Placing head
    map_set_cell(snake_head->row_index, snake_head->column_index, CELL_SNAKE_HEAD);

    // Placing body
    snake_part = snake_head->prev_part;
    while (snake_part->prev_part) {
      map_set_cell(snake_part->row_index, snake_part->column_index, CELL_SNAKE_BODY);
      snake_part = snake_part->prev_part;
    }
  }
}

snake_part_t* snake_move_up(snake_part_t* snake_head) {
  int new_row = ROW_INDEX_UP(snake_head->row_index);
  int new_column = snake_head->column_index;
  return move_to(snake_head, new_row, new_column);
}

snake_part_t* snake_move_down(snake_part_t* snake_head) {
  int new_row = ROW_INDEX_DOWN(snake_head->row_index);
  int new_column = snake_head->column_index;
  return move_to(snake_head, new_row, new_column);
}

snake_part_t* snake_move_left(snake_part_t* snake_head) {
  int new_row = snake_head->row_index;
  int new_column = COLUMN_INDEX_LEFT(snake_head->column_index);
  return move_to(snake_head, new_row, new_column);
}

snake_part_t* snake_move_right(snake_part_t* snake_head) {
  int new_row = snake_head->row_index;
  int new_column = COLUMN_INDEX_RIGHT(snake_head->column_index);
  return move_to(snake_head, new_row, new_column);
}


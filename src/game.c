#include <conio.h>
#include <stdio.h>
#include "game.h"
#include "map.h"
#include "snake.h"
#include "tinycthread.h"

// Cross-platform includes for the millisecond wait
#if defined(WIN32)
#include <windows.h>
#elif defined(__unix__)
#include <time.h>
#include <unistd.h>
#else
#endif

/** @brief Frequency at which each move is performed, when beginning a game */
#define GAME_START_FREQUENCY_HZ 4.0f

/** @brief Increment value of the game frequency */
#define GAME_FREQUENCY_INCREMENT_HZ 0.3f

/** @brief Maximum value of the game frequency */
#define GAME_FREQUENCY_MAX_HZ 15.0f

/** @brief Enumerate of all possible direction for the snake */
typedef enum { MV_UP, MV_DOWN, MV_RIGHT, MV_LEFT } move_direction_t;

/** @brief Shared variable used to stop the game upon a given key press */
int playing = 1;

/** @brief Shared variable used to store the snake direction of the next move */
move_direction_t next_snake_direction = MV_RIGHT;

/** @brief Shared variable used to store the current snake direction */
move_direction_t current_snake_direction = MV_RIGHT;

// Create the game time period
float game_frequency_hz = GAME_START_FREQUENCY_HZ;

// Score of the current game
unsigned int score = 0;

/**
 * @brief Function to wait a certain amount of milliseconds
 *
 * @param ms The number of milliseconds to wait
 *
 * @note Ref: https://stackoverflow.com/a/14818830/6413048
 */
static void millisleep(unsigned int ms);

static void fruit_callback(void) {
  score++;
  map_place_fruit();  // Add a new fruit so the snake doesn't starve
  if (game_frequency_hz < GAME_FREQUENCY_MAX_HZ) {
    game_frequency_hz += GAME_FREQUENCY_INCREMENT_HZ;
  }
}

static void collision_callback(void) {
  playing = 0;
}

/**
 * @brief Thread used to acquire user keyboard input continuously
 *
 * @param aArg unused
 *
 * @return unused
 */
int input_thread(void* aArg) {
  while (playing) {
    int c = getch();
    if (c != EOF) {
      switch (c) {
        case 'q':
          playing = 0;
          break;
        case 'w':
          if (current_snake_direction != MV_DOWN)
            next_snake_direction = MV_UP;
          break;
        case 's':
          if (current_snake_direction != MV_UP)
            next_snake_direction = MV_DOWN;
          break;
        case 'a':
          if (current_snake_direction != MV_RIGHT)
            next_snake_direction = MV_LEFT;
          break;
        case 'd':
          if (current_snake_direction != MV_LEFT)
            next_snake_direction = MV_RIGHT;
          break;
        default:
          break;
      }
    }
  }
  return 0;
}

void game_loop(void) {
  // Create thread for input acquisition
  thrd_t thrd_input_handle;
  thrd_create(&thrd_input_handle, input_thread, 0);

  // Creatie the snake and place it in the middle
  snake_part_t* snake_head =
      snake_create(10, MAP_SIZE_V / 2, MAP_SIZE_H / 2, fruit_callback, collision_callback);
  map_init();
  snake_place_on_map(snake_head);
  map_place_fruit();
  map_render();

  // Game loop: manage directions and render the map periodically
  while (playing) {
    switch (next_snake_direction) {
      case MV_UP:
        snake_head = snake_move_up(snake_head);
        break;
      case MV_DOWN:
        snake_head = snake_move_down(snake_head);
        break;
      case MV_LEFT:
        snake_head = snake_move_left(snake_head);
        break;
      case MV_RIGHT:
        snake_head = snake_move_right(snake_head);
        break;
      default:
        break;
    }

    current_snake_direction = next_snake_direction;

    map_render();
    printf("Score: %d\r\n", score);

    millisleep(1000.0f / game_frequency_hz);
  }

  // Destroy the snake since game is over
  snake_destroy(snake_head);

  printf("\r\nGame lost !\r\n");
}

static void millisleep(unsigned int ms) {
#if defined(WIN32)
  SetLastError(0);
  Sleep(ms);
#elif _POSIX_C_SOURCE >= 199309L
  /* prefer to use nanosleep() */
  const struct timespec ts = {
      ms / 1000,                /* seconds */
      (ms % 1000) * 1000 * 1000 /* nano seconds */
  };
  nanosleep(&ts, NULL);

#elif _BSD_SOURCE || (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && \
                         !(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700)

  /* else fallback to obsolte usleep() */
  usleep(1000 * ms);
#else
#error("No millisecond sleep available for this platform!")
#endif
}

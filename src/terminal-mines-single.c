/* ====================================================
 * 100% TRUE ORIGINAL AMALGAMATED SINGLE FILE - TERMINAL MINES
 * Automatically generated from vanilla source files.
 * ==================================================== */

#include <getopt.h>
#include <inttypes.h>
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

/* >>> FULLY ATTACHED MODULE:
 * src/terminal-mines/libminesweeper/include/minesweeper.h <<< */
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum direction { LEFT, RIGHT, UP, DOWN };

enum minesweeper_game_state {
  MINESWEEPER_PENDING_START,
  MINESWEEPER_PLAYING,
  MINESWEEPER_WIN,
  MINESWEEPER_GAME_OVER
};

struct minesweeper_tile {
  uint8_t adjacent_mine_count : 4;
  bool has_flag : 1;
  bool has_mine : 1;
  bool is_opened : 1;
};

struct minesweeper_game;
typedef void (*minesweeper_callback)(struct minesweeper_game *game,
                                     struct minesweeper_tile *tile,
                                     void *user_info);

/**
 * Contains data for a single minesweeper game.
 *
 * Do not modify fields directly - use the functions below instead. The only
 * exception to this is tile_update_callback, which can be set at any time.
 *
 * Created automatically by minesweeper_init().
 */
struct minesweeper_game {
  unsigned width;
  unsigned height;
  unsigned mine_count;
  unsigned opened_tile_count;
  unsigned flag_count;
  struct minesweeper_tile
      *selected_tile; /* Pointer to the tile under the cursor */
  struct minesweeper_tile *tiles;
  enum minesweeper_game_state state;
  minesweeper_callback tile_update_callback; /* Optional function pointer to
                                                receive tile state updates */
  void *user_info; /* Can be used for anything, will be passed as a parameter to
                      tile_update_callback */
};

/**
 * Initialize a new game
 *
 * width, height: Adjusts the size of the game area
 * mine_density: A value between 0 and 1. When 0, no tiles will have mines. When
 * 1, all tiles will have mines buffer: A memory location to store the game at.
 * Must be at least the size returned from minesweeper_minimum_buffer_size() for
 * the given height and width
 *
 * Returns a pointer to somewhere within buffer. To delete a game, invalidate
 * entire buffer.
 */
struct minesweeper_game *minesweeper_init(unsigned width, unsigned height,
                                          float mine_density, uint8_t *buffer);
size_t minesweeper_minimum_buffer_size(unsigned width, unsigned height);

/**
 * Set the location of the cursor. "The cursor"
 * is another name for game->selected_tile.
 */
void minesweeper_set_cursor(struct minesweeper_game *game, unsigned x,
                            unsigned y);

/**
 * Move the cursor in a specified direction.
 *
 * If should_wrap is true, attempting to move outside the game bounds will
 * result in the cursor wrapping to the opposite side of the game area.
 *
 * This will update game->selected_tile.
 */
void minesweeper_move_cursor(struct minesweeper_game *game,
                             enum direction direction, bool should_wrap);

/**
 * Opens an unflagged tile.
 *
 * Will recursively open all adjacent tiles that have zero
 * adjacent mines.
 *
 * If tile is already opened, all adjacent unflagged tiles will
 * be opened instead, to imitate the quick-open functionality of most
 * minesweeper games.
 */
void minesweeper_open_tile(struct minesweeper_game *game,
                           struct minesweeper_tile *tile);

/**
 * Open souraounding tiles if tile is opened, else a flag is placed
 */
void minesweeper_space_tile(struct minesweeper_game *game,
                            struct minesweeper_tile *tile);

/**
 * Toggles a flag on an unopened tile.
 */
void minesweeper_toggle_flag(struct minesweeper_game *game,
                             struct minesweeper_tile *tile);

/**
 * Get pointer to tile at location. Returns NULL if location if out of bounds.
 */
struct minesweeper_tile *minesweeper_get_tile_at(struct minesweeper_game *game,
                                                 unsigned x, unsigned y);

/**
 * Get location of a tile.
 *
 * x/y: Pointers to integers which the result will be written to.
 */
void minesweeper_get_tile_location(struct minesweeper_game *game,
                                   struct minesweeper_tile *tile, unsigned *x,
                                   unsigned *y);

/**
 * Get all tiles adjacent to tile. A tile can have at most 8 adjacent tiles,
 * but tiles adjacent to edges of the game area will have fewer.
 *
 * adjacent_tiles: A pointer to an array of 8 tile pointers. Pointers to the
 * resulting tiles will be written to this array. Some tiles may be NULL, if
 * tile is adjacent to an edge.
 */
void minesweeper_get_adjacent_tiles(struct minesweeper_game *game,
                                    struct minesweeper_tile *tile,
                                    struct minesweeper_tile *adjacent_tiles[8]);

/**
 * Toggles a mine on a tile, and adjusts the adjacent mine counts for all
 * adjacent tiles.
 */
void minesweeper_toggle_mine(struct minesweeper_game *game,
                             struct minesweeper_tile *tile);

#endif

/* <<< END OF MODULE: src/terminal-mines/libminesweeper/include/minesweeper.h
 * >>> */

/* >>> FULLY ATTACHED MODULE: src/terminal-mines/graphics.h <<< */
#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>

enum {
  COLOR_PAIR_DEFAULT = 1,
  COLOR_PAIR_CURSOR,
  COLOR_PAIR_MINE,
  COLOR_PAIR_FLAG,
  COLOR_PAIR_1,
  COLOR_PAIR_2,
  COLOR_PAIR_3,
  COLOR_PAIR_4,
  COLOR_PAIR_5,
  COLOR_PAIR_6,
  COLOR_PAIR_7,
  COLOR_PAIR_8,
  COLOR_PAIR_ADVENTURE_EXIT,
  COLOR_PAIR_ADVENTURE_PLAYER
};

#ifdef ASCII_ONLY
#define TILE_MAP                                                               \
  {" ", "1", "2", "3", "4", "5", "6", "7", "8", "#", "*", "F", "@", ">"}
#else
#define TILE_MAP                                                               \
  {" ", "1", "2", "3", "4", "5", "6", "7", "8", "■", "¤", "Þ", "@", ">"}
#endif

enum TILE_INDEX {
  TILE_INDEX_EMPTY = 0,
  TILE_INDEX_UNOPENED = 9,
  TILE_INDEX_MINE,
  TILE_INDEX_FLAG,
  TILE_INDEX_ADVENTURE_PLAYER,
  TILE_INDEX_ADVENTURE_EXIT,
};

void init_colors();
void render_game(struct minesweeper_game *game, WINDOW *window);
void render_tile(struct minesweeper_game *game, struct minesweeper_tile *tile,
                 WINDOW *window);
void update_status_window(WINDOW *status_window, struct minesweeper_game *game);

#endif

/* <<< END OF MODULE: src/terminal-mines/graphics.h >>> */

/* >>> FULLY ATTACHED MODULE: src/terminal-mines/options.h <<< */
#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>
#include <stdint.h>

struct tm_options {
  int width;
  int height;
  float mine_density;
  bool adventure_mode;
};

struct tm_options parse_options(int argc, char **argv);

#endif

/* <<< END OF MODULE: src/terminal-mines/options.h >>> */

/* >>> FULLY ATTACHED MODULE:
 * src/terminal-mines/libminesweeper/lib/minesweeper.c <<< */
#include <stdlib.h>
#include <string.h>

void generate_mines(struct minesweeper_game *game, float density);

struct minesweeper_game *minesweeper_init(unsigned width, unsigned height,
                                          float mine_density, uint8_t *buffer) {
  /* Place a game object in the start of the buffer, and
     treat the rest of the buffer as tile storage. */
  struct minesweeper_game *game = (struct minesweeper_game *)buffer;
  game->tiles =
      (struct minesweeper_tile *)buffer + sizeof(struct minesweeper_game);
  game->tile_update_callback = NULL;
  game->state = MINESWEEPER_PENDING_START;
  game->width = width;
  game->height = height;
  game->mine_count = 0;
  game->flag_count = 0;
  game->opened_tile_count = 0;
  game->selected_tile = NULL;
  game->user_info = NULL;
  memset(game->tiles, 0, sizeof(struct minesweeper_tile) * width * height);
  generate_mines(game, mine_density);
  return game;
}

size_t minesweeper_minimum_buffer_size(unsigned width, unsigned height) {
  return sizeof(struct minesweeper_game) +
         sizeof(struct minesweeper_tile) * width * height;
}

bool is_out_of_bounds(struct minesweeper_game *b, unsigned x, unsigned y) {
  return x >= b->width || y >= b->height;
}

/**
 * Get a pointer to a tile. Contains bounds checking and
 * will return NULL if the tile is out of bounds. This
 * is to simplify code that enumerates "adjacent" tiles.
 */
struct minesweeper_tile *minesweeper_get_tile_at(struct minesweeper_game *game,
                                                 unsigned x, unsigned y) {
  if (is_out_of_bounds(game, x, y))
    return NULL;
  return &game->tiles[game->width * y + x];
}

void minesweeper_get_tile_location(struct minesweeper_game *game,
                                   struct minesweeper_tile *tile, unsigned *x,
                                   unsigned *y) {
  unsigned tile_index = tile - game->tiles;
  *y = tile_index / game->width;
  *x = tile_index % game->width;
}

void minesweeper_get_adjacent_tiles(
    struct minesweeper_game *game, struct minesweeper_tile *tile,
    struct minesweeper_tile *adjacent_tiles[8]) {
  unsigned x, y;
  minesweeper_get_tile_location(game, tile, &x, &y);
  adjacent_tiles[0] = minesweeper_get_tile_at(game, x - 1, y - 1);
  adjacent_tiles[1] = minesweeper_get_tile_at(game, x - 1, y);
  adjacent_tiles[2] = minesweeper_get_tile_at(game, x - 1, y + 1);
  adjacent_tiles[3] = minesweeper_get_tile_at(game, x, y - 1);
  adjacent_tiles[4] = minesweeper_get_tile_at(game, x, y + 1);
  adjacent_tiles[5] = minesweeper_get_tile_at(game, x + 1, y - 1);
  adjacent_tiles[6] = minesweeper_get_tile_at(game, x + 1, y);
  adjacent_tiles[7] = minesweeper_get_tile_at(game, x + 1, y + 1);
}

/**
 * When attempting to open a tile that's already opened, the game
 * can "auto open" adjacent tiles if it's surrounded by the correct
 * amount of flagged tiles. This function counts the surrounding
 * flagged tiles.
 */
uint8_t count_adjacent_flags(struct minesweeper_game *game,
                             struct minesweeper_tile *tile) {
  uint8_t count = 0;
  struct minesweeper_tile *adjacent_tiles[8];
  uint8_t i;
  minesweeper_get_adjacent_tiles(game, tile, adjacent_tiles);
  for (i = 0; i < 8; i++) {
    struct minesweeper_tile *adj_tile = adjacent_tiles[i];
    if (adj_tile && !(adj_tile->is_opened) && adj_tile->has_flag) {
      count++;
    }
  }
  return count;
}

void minesweeper_toggle_mine(struct minesweeper_game *game,
                             struct minesweeper_tile *tile) {
  uint8_t i;
  struct minesweeper_tile *adjacent_tiles[8];
  int8_t count_modifier = -1;

  if (!tile) {
    return;
  }

  tile->has_mine = !tile->has_mine;
  if (tile->has_mine) {
    count_modifier = 1;
  }
  game->mine_count += count_modifier;

  /* Increase or decrease the mine counts on all adjacent tiles */
  minesweeper_get_adjacent_tiles(game, tile, adjacent_tiles);
  for (i = 0; i < 8; i++) {
    if (adjacent_tiles[i]) {
      adjacent_tiles[i]->adjacent_mine_count += count_modifier;
    }
  }
}

void generate_mines(struct minesweeper_game *game, float density) {
  unsigned tile_count = game->width * game->height;
  unsigned mine_count = tile_count * density;
  unsigned i;
  for (i = 0; i < mine_count; i++) {
    struct minesweeper_tile *random_tile = &game->tiles[rand() % tile_count];
    if (!random_tile->has_mine) {
      minesweeper_toggle_mine(game, random_tile);
    }
  }
}

void send_update_callback(struct minesweeper_game *game,
                          struct minesweeper_tile *tile) {
  if (game->tile_update_callback != NULL) {
    game->tile_update_callback(game, tile, game->user_info);
  }
}

void minesweeper_toggle_flag(struct minesweeper_game *game,
                             struct minesweeper_tile *tile) {
  if (tile && !tile->is_opened) {
    game->flag_count += tile->has_flag ? -1 : 1;
    tile->has_flag = !tile->has_flag;
    send_update_callback(game, tile);
  }
}

static inline bool all_tiles_opened(struct minesweeper_game *game) {
  return game->opened_tile_count ==
         game->width * game->height - game->mine_count;
}

void open_adjacent_tiles(struct minesweeper_game *game,
                         struct minesweeper_tile *tile);

void _open_tile(struct minesweeper_game *game, struct minesweeper_tile *tile,
                bool cascade) {
  if (tile->is_opened) {
    /* If this tile is already opened and has a mine count,
     * it should open all adjacent tiles instead. This mimics
     * the behaviour in the original minesweeper where you can
     * right click opened tiles to open adjacent tiles quickly. */
    if (tile->adjacent_mine_count > 0 &&
        tile->adjacent_mine_count == count_adjacent_flags(game, tile) &&
        cascade)
      open_adjacent_tiles(game, tile);
    return;
  }

  if (tile->has_flag) {
    return;
  }

  tile->is_opened = true;
  game->opened_tile_count += 1;
  send_update_callback(game, tile);

  if (tile->has_mine) {
    game->state = MINESWEEPER_GAME_OVER;
    return;
  }

  if (all_tiles_opened(game)) {
    game->state = MINESWEEPER_WIN;
    return;
  }

  if (tile->adjacent_mine_count != 0) {
    return;
  }

  if (cascade)
    open_adjacent_tiles(game, tile);
}

void minesweeper_open_tile(struct minesweeper_game *game,
                           struct minesweeper_tile *tile) {
  if (game->state == MINESWEEPER_PENDING_START) {
    game->state = MINESWEEPER_PLAYING;

    // Delete any potential mine on the first opened tile
    if (tile->has_mine) {
      minesweeper_toggle_mine(game, tile);
    }
  }
  _open_tile(game, tile, true);
}

void minesweeper_space_tile(struct minesweeper_game *game,
                            struct minesweeper_tile *tile) {
  if (game->state == MINESWEEPER_PENDING_START) {
    game->state = MINESWEEPER_PLAYING;

    // Delete any potential mine on the first opened tile
    if (tile->has_mine) {
      minesweeper_toggle_mine(game, tile);
    }
  }

  if (tile->is_opened) {
    _open_tile(game, tile, true);
  } else {
    minesweeper_toggle_flag(game, tile);
  }
}

void open_line_segments(struct minesweeper_game *game, unsigned x1, unsigned x2,
                        unsigned y) {
  unsigned x;
  struct minesweeper_tile *tile;
  for (x = x1; x <= x2 && (tile = minesweeper_get_tile_at(game, x, y)); x++) {
    if (!tile->is_opened)
      _open_tile(game, tile, true);
  }
}

void open_adjacent_tiles(struct minesweeper_game *game,
                         struct minesweeper_tile *tile) {
  unsigned tile_index = tile - game->tiles;
  unsigned ty = tile_index / game->width;
  unsigned tx = tile_index % game->width;
  unsigned lx, rx;
  struct minesweeper_tile *subtile;

  // Search for left boundary
  for (lx = tx - 1; (subtile = minesweeper_get_tile_at(game, lx, ty)); lx--) {
    if (subtile->is_opened && subtile->adjacent_mine_count != 0)
      break;
    _open_tile(game, subtile, false);
    if (subtile->adjacent_mine_count != 0)
      break;
  }

  // Re-adjust value if loop broke out because of out-of-bounds
  if (is_out_of_bounds(game, lx, ty))
    lx++;

  // Search for right boundary
  for (rx = tx + 1; (subtile = minesweeper_get_tile_at(game, rx, ty)); rx++) {
    if (subtile->is_opened && subtile->adjacent_mine_count != 0)
      break;
    _open_tile(game, subtile, false);
    if (subtile->adjacent_mine_count != 0)
      break;
  }

  // Re-adjust value if loop broke out because of out-of-bounds
  if (is_out_of_bounds(game, rx, ty))
    rx--;

  // Open line(s) above
  open_line_segments(game, lx, rx, ty - 1);
  // Open line(s) below
  open_line_segments(game, lx, rx, ty + 1);
}

void minesweeper_set_cursor(struct minesweeper_game *game, unsigned x,
                            unsigned y) {
  if (is_out_of_bounds(game, x, y)) {
    game->selected_tile = NULL;
  } else {
    game->selected_tile = minesweeper_get_tile_at(game, x, y);
  }
}

void minesweeper_move_cursor(struct minesweeper_game *game,
                             enum direction direction, bool should_wrap) {
  unsigned x, y;
  if (game->selected_tile == NULL) {
    return;
  }

  minesweeper_get_tile_location(game, game->selected_tile, &x, &y);
  switch (direction) {
  case LEFT:
    if (x != 0)
      x--;
    else if (should_wrap)
      x = game->width - 1;
    break;
  case RIGHT:
    if (x != game->width - 1)
      x++;
    else if (should_wrap)
      x = 0;
    break;
  case UP:
    if (y != 0)
      y--;
    else if (should_wrap)
      y = game->height - 1;
    break;
  case DOWN:
    if (y != game->height - 1)
      y++;
    else if (should_wrap)
      y = 0;
    break;
  }
  minesweeper_set_cursor(game, x, y);
}

/* <<< END OF MODULE: src/terminal-mines/libminesweeper/lib/minesweeper.c >>> */

/* >>> FULLY ATTACHED MODULE: src/terminal-mines/graphics.c <<< */
#include <string.h>

void init_colors() {
  use_default_colors();
  init_pair(COLOR_PAIR_DEFAULT, -1, -1);
  init_pair(COLOR_PAIR_CURSOR, -1, COLOR_GREEN);
  init_pair(COLOR_PAIR_MINE, -1, COLOR_RED);
  init_pair(COLOR_PAIR_FLAG, COLOR_YELLOW, -1);
  init_pair(COLOR_PAIR_1, COLOR_BLUE, -1);
  init_pair(COLOR_PAIR_2, COLOR_GREEN, -1);
  init_pair(COLOR_PAIR_3, COLOR_RED, -1);
  init_pair(COLOR_PAIR_4, COLOR_YELLOW, -1);
  // TODO: Set colors for 5,6,7,8
  init_pair(COLOR_PAIR_ADVENTURE_EXIT, COLOR_BLACK, COLOR_GREEN);
  init_pair(COLOR_PAIR_ADVENTURE_PLAYER, COLOR_GREEN, -1);
}

void update_status_window(WINDOW *status_window,
                          struct minesweeper_game *game) {
  int window_width = game->width;

  char mine_text[128];
  char flag_text[128];
  snprintf(mine_text, sizeof(mine_text), "Mines: %d", game->mine_count);
  snprintf(flag_text, sizeof(flag_text), "Flags: %d", game->flag_count);

  int flag_text_length = strlen(flag_text);

  wclear(status_window);
  box(status_window, 0, 0);
  mvwprintw(status_window, 1, 1, "%s", mine_text);
  mvwprintw(status_window, 1, window_width - (flag_text_length - 1), "%s",
            flag_text);
  wrefresh(status_window);
}

extern struct tm_options global_options;
extern struct minesweeper_tile *adventure_exit_tile;

int tile_index_for_tile(struct minesweeper_game *game,
                        struct minesweeper_tile *tile) {
  // Opened with mine, and game over state where all mines are displayed
  if ((tile->has_mine && game->state == MINESWEEPER_GAME_OVER) ||
      (tile->has_mine && tile->is_opened)) {
    return TILE_INDEX_MINE;
  }

  // In adventure mode, we display the cursor as a player '@' and an exit tile
  // '>'
  if (global_options.adventure_mode) {
    if (tile == adventure_exit_tile) {
      return TILE_INDEX_ADVENTURE_EXIT;
    } else if (tile == game->selected_tile) {
      return TILE_INDEX_ADVENTURE_PLAYER;
    }
  }

  // On opened tile, we show the adjacent mine count
  if (tile->is_opened) {
    return tile->adjacent_mine_count;
  }

  // Flags are shown as an 'F'
  if (tile->has_flag) {
    return TILE_INDEX_FLAG;
  }

  // Unopened tiles
  return TILE_INDEX_UNOPENED;
}

void render_tile(struct minesweeper_game *game, struct minesweeper_tile *tile,
                 WINDOW *window) {
  int index = tile_index_for_tile(game, tile);
  bool is_cursor = tile == game->selected_tile;
  if (index == TILE_INDEX_MINE) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_MINE));
  } else if (tile == adventure_exit_tile) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_ADVENTURE_EXIT));
  } else if (is_cursor && global_options.adventure_mode) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_ADVENTURE_PLAYER));
  } else if (is_cursor) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_CURSOR));
  } else if (index == TILE_INDEX_FLAG) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_FLAG));
  } else if (index >= 1 && index <= 8) {
    wattron(window, COLOR_PAIR(COLOR_PAIR_1 + (index - 1)));
  } else {
    wattron(window, COLOR_PAIR(COLOR_PAIR_DEFAULT));
  }

  // Add 1 to the position in both axes so we stay within the
  // window border.
  unsigned x, y;
  minesweeper_get_tile_location(game, tile, &x, &y);
  static char *tile_map[] = TILE_MAP;
  mvwaddstr(window, y + 1, x + 1, tile_map[index]);
}

void render_game(struct minesweeper_game *game, WINDOW *window) {
  for (unsigned x = 0; x < game->width; x++) {
    for (unsigned y = 0; y < game->height; y++) {
      struct minesweeper_tile *tile = minesweeper_get_tile_at(game, x, y);
      render_tile(game, tile, window);
    }
  }
}

/* <<< END OF MODULE: src/terminal-mines/graphics.c >>> */

/* >>> FULLY ATTACHED MODULE: src/terminal-mines/options.c <<< */
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void show_help();
void print_version();

struct tm_options parse_options(int argc, char **argv) {
  static struct option options[] = {
      {"width", required_argument, NULL, 'w'},
      {"height", required_argument, NULL, 'h'},
      {"mine-density", required_argument, NULL, 'm'},
      {"help", no_argument, NULL, 1},
      {"version", no_argument, NULL, 'v'},
      {"adventure-mode", no_argument, NULL, 'a'},
      {NULL, 0, NULL, 0}};

  // Default options
  struct tm_options tm_options = {
      .width = 20, .height = 10, .mine_density = 0.1, .adventure_mode = false};

  signed char param;
  while ((param = getopt_long(argc, argv, "w:h:m:va", options, NULL)) != -1) {
    switch (param) {
    case 'w': {
      uintmax_t value = strtoumax(optarg, NULL, 10);
      if (value != UINTMAX_MAX) {
        tm_options.width = (int)value;
      }
      break;
    }

    case 'h': {
      uintmax_t value = strtoumax(optarg, NULL, 10);
      if (value != UINTMAX_MAX) {
        tm_options.height = (int)value;
      }
      break;
    }

    case 'm': {
      float value = strtof(optarg, NULL);
      if (value != 0) {
        tm_options.mine_density = value;
      }
      break;
    }

    case 'v': {
      print_version();
      exit(0);
    }

    case 'a': {
      tm_options.adventure_mode = true;
      break;
    }

    case 1: {
      show_help();
      exit(0);
    }
    }
  }

  return tm_options;
}

void show_help() {
  // If manpage exists locally, prioritize it to allow local builds to show help
  char *manpage_path = NULL;
  if (access("man/terminal-mines.1", F_OK | R_OK) != -1) {
    manpage_path = "man/terminal-mines.1";
  } else {
    manpage_path = "terminal-mines";
  }

  pid_t pid = fork();
  if (pid == 0) { /* Child process */
    char *argv[] = {"man", manpage_path, NULL};
    execv("/usr/bin/man", argv);
    exit(127);          /* only if execv fails */
  } else {              /* pid != 0; parent process */
    waitpid(pid, 0, 0); /* wait for child to exit */
  }
}

void print_version() { puts("1.2.0"); }

/* <<< END OF MODULE: src/terminal-mines/options.c >>> */

/* >>> FULLY ATTACHED MODULE: src/terminal-mines/terminal-mines.c <<< */
#include <inttypes.h>
#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void start_with_game(struct minesweeper_game *game, struct tm_options options);
void game_loop(WINDOW *window, struct minesweeper_game *game,
               struct tm_options options);
void tile_changed(struct minesweeper_game *game, struct minesweeper_tile *tile,
                  void *context);

WINDOW *game_win;
WINDOW *status_win;
struct tm_options global_options;
struct minesweeper_tile *adventure_exit_tile;

void setup_ncurses() {
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  cbreak();
  noecho();
  init_colors();
  curs_set(0);
}

int main(int argc, char **argv) {
  global_options = parse_options(argc, argv);
  setup_ncurses();

  // Make sure the desired size is not larger than the terminal window
  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);

  int max_width = screen_width - 2;   // Remove 2 so we can fit window border
  int max_height = screen_height - 5; // Window border + status window height

  if (global_options.width > max_width) {
    global_options.width = max_width;
  }

  if (global_options.height > max_height) {
    global_options.height = max_height;
  }

  // Set up a game game
  srand(time(NULL));
  uint8_t *buffer = malloc(minesweeper_minimum_buffer_size(
      global_options.width, global_options.height));
  struct minesweeper_game *b =
      minesweeper_init(global_options.width, global_options.height,
                       global_options.mine_density, buffer);
  b->tile_update_callback = &tile_changed;

  // Start the ncurses frontend
  start_with_game(b, global_options);
  free(buffer);
}

void start_with_game(struct minesweeper_game *game, struct tm_options options) {
  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);

  // Create window where we will draw the game. Add 2
  // tiles padding so we can draw a box around it
  int window_width = game->width + 2;
  int window_height = game->height + 2;
  int window_x = screen_width / 2 - window_width / 2;
  int window_y = screen_height / 2 - window_height / 2;
  game_win = newwin(window_height, window_width, window_y, window_x);
  box(game_win, 0, 0);

  status_win = newwin(3, window_width, window_y + window_height, window_x);

  // When we run in adventure mode, we want to place the player in the
  // bottom left corner, and make sure there are no mines too close
  if (options.adventure_mode) {
    minesweeper_set_cursor(game, 0, game->height - 1);
    adventure_exit_tile = minesweeper_get_tile_at(game, game->width - 1, 0);

    // Clear the 8 tiles closest to the player
    struct minesweeper_tile *clear_tile =
        minesweeper_get_tile_at(game, 1, game->height - 2);
    if (clear_tile && clear_tile->has_mine)
      minesweeper_toggle_mine(game, clear_tile);
    struct minesweeper_tile *adjacent_tiles[8];
    minesweeper_get_adjacent_tiles(game, clear_tile, adjacent_tiles);
    for (int i = 0; i < 8; i++) {
      struct minesweeper_tile *tile = adjacent_tiles[i];
      if (tile && tile->has_mine)
        minesweeper_toggle_mine(game, tile);
    }

    // Clear the exit tile
    if (adventure_exit_tile->has_mine) {
      minesweeper_toggle_mine(game, adventure_exit_tile);
    }

    minesweeper_open_tile(game, game->selected_tile);
  } else {
    minesweeper_set_cursor(game, game->width / 2, game->height / 2);
  }

  // Draw an initial representation so you see the window when the game starts
  render_game(game, game_win);
  refresh();
  wrefresh(game_win);
  update_status_window(status_win, game);
  wrefresh(status_win);

  game_loop(game_win, game, options);
}

void tm_move_cursor(struct minesweeper_game *game, enum direction direction,
                    struct tm_options options) {
  minesweeper_move_cursor(game, direction, !options.adventure_mode);
  if (options.adventure_mode) {
    if (game->selected_tile == adventure_exit_tile) {
      game->state = MINESWEEPER_WIN;
    } else {
      minesweeper_open_tile(game, game->selected_tile);
    }
  }
}

void game_loop(WINDOW *window, struct minesweeper_game *game,
               struct tm_options options) {
  // Wait for keygame input
  keypad(stdscr, TRUE);
  int ch;
  while ((ch = getch()) != KEY_F(1) &&
         (game->state == MINESWEEPER_PENDING_START ||
          game->state == MINESWEEPER_PLAYING)) {
    struct minesweeper_tile *previous_tile = game->selected_tile;
    switch (ch) {
    case KEY_LEFT:
    case 'h':
      tm_move_cursor(game, LEFT, options);
      break;

    case KEY_RIGHT:
    case 'l':
      tm_move_cursor(game, RIGHT, options);
      break;

    case KEY_UP:
    case 'k':
      tm_move_cursor(game, UP, options);
      break;

    case KEY_DOWN:
    case 'j':
      tm_move_cursor(game, DOWN, options);
      break;

    case 'g':
    case 'f':
      minesweeper_toggle_flag(game, game->selected_tile);
      update_status_window(status_win, game);
      break;
    case ' ':
      minesweeper_space_tile(game, game->selected_tile);
      update_status_window(status_win, game);
      break;
    case ',':
      minesweeper_open_tile(game, game->selected_tile);
      update_status_window(status_win, game);
      break;
    }

    if (game->selected_tile != previous_tile) {
      render_tile(game, previous_tile, window);
      render_tile(game, game->selected_tile, window);
    }

    wrefresh(window);
  }

  render_game(game, window);
  wrefresh(window);

  // Create a win/lose window, and then exit the game after a key press
  char *end_text = NULL;
  if (game->state == MINESWEEPER_GAME_OVER) {
    end_text = "You failed!";
  } else if (game->state == MINESWEEPER_WIN) {
    end_text = "You win! Niiiice!";
  }

  int screen_width, screen_height;
  getmaxyx(stdscr, screen_height, screen_width);
  int window_width = strlen(end_text) + 2;
  WINDOW *end_win = newwin(3, window_width, screen_height / 2 - 2,
                           screen_width / 2 - window_width / 2);
  box(end_win, 0, 0);
  mvwprintw(end_win, 1, 1, end_text);
  wrefresh(end_win);

  wgetch(window);
  endwin();
}

// Callback from libminesweeper
void tile_changed(struct minesweeper_game *game, struct minesweeper_tile *tile,
                  void *context) {
  render_tile(game, tile, game_win);
}

/* <<< END OF MODULE: src/terminal-mines/terminal-mines.c >>> */

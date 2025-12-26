#include "funlib.h"
#include "game.h"
#include "gl_renderer.h"
#include "input.h"
#include "platform.h"
#include "render_interface.h"
#include <unistd.h>
// ##############################################################
//                   Game DLL Stuff
// ##############################################################
// Function pointer to update_game in game.cpp
typedef decltype(update_game) update_game_type;
static update_game_type *update_game_ptr;
// ##############################################################
//               Cross Platform Functions
// ##############################################################
void reload_game_DLL(BumpAllocator *transientStorage);

Input *input = nullptr;
RenderData *renderData = nullptr;
GameState *gameState = nullptr;

int main() {
  BumpAllocator transientStorage = Make_Bump_Allocator(MB(50));
  BumpAllocator persistentStorage = Make_Bump_Allocator(MB(50));

  input = (Input *)Bump_Alloc(&persistentStorage, sizeof(Input));
  if (!input) {
    LOG_ERROR("Failed to allocate Input");
    return -1;
  }
  renderData = (RenderData *)Bump_Alloc(&persistentStorage, sizeof(RenderData));
  if (!renderData) {
    LOG_ERROR("Failed to allocate RenderData")
    return -1;
  }
  gameState = (GameState *)Bump_Alloc(&persistentStorage, sizeof(GameState));
  if (!gameState) {
    LOG_ERROR("Failed to allocate GameState")
    return -1;
  }

  input->screenSizeX = 1200;
  input->screenSizeY = 700;

  if (!platform_create_window(1200, 700, (char *)"Window")) {
    return 1;
  }

  gl_init(&transientStorage);

  while (running) {
    reload_game_DLL(&transientStorage);
    platform_update_window();
    update_game(gameState, renderData, input);
    gl_render();
    platform_swap_buffers();

    transientStorage.used = 0;
  }

  platform_destroy_window();
  return 0;
}

void update_game(GameState *gameStateIn, RenderData *renderDataIn,
                 Input *inputIn) {
  update_game_ptr(gameStateIn, renderDataIn, inputIn);
}

void reload_game_DLL(BumpAllocator *transientStorage) {
  static void *gameDLL = nullptr;
  static long long lastTs = 0;

  long long ts = get_timestamp("game.so");
  if (ts == 0) {
    // If your timestamp helper can fail, don't attempt reload
    return;
  }

  // Only reload if the file actually changed or first load
  if (gameDLL && ts == lastTs) {
    return;
  }

  // unload old
  if (gameDLL) {
    platform_free_dynamic_library(gameDLL);
    gameDLL = nullptr;
    update_game_ptr = nullptr;
    LOG_TRACE("Freed game DLL");
  }

  // copy to temp name
  // IMPORTANT: copy_file must fully overwrite destination (truncate) and close
  // it.
  while (!copy_file("game.so", "game_load.so", transientStorage)) {
    usleep(50 * 1000);
  }
  LOG_TRACE("Copied game.so into game_load.so");

  // load new
  gameDLL = platform_load_dynamic_library("game_load.so");
  FN_ASSERT(gameDLL, "dlopen game_load.so failed");

  update_game_ptr = (update_game_type *)platform_load_dynamic_function(
      gameDLL, "update_game");
  FN_ASSERT(update_game_ptr, "Failed to load update_game");

  lastTs = ts;
  LOG_TRACE("Reloaded game DLL OK (ts=%lld)", ts);
}

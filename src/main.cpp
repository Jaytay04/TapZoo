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

  input->screenSizeX = 1200;
  input->screenSizeY = 700;

  if (!platform_create_window(1200, 700, (char *)"Window")) {
    return 1;
  }

  gl_init(&transientStorage);

  while (running) {
    platform_update_window();
    update_game(renderData, input);
    gl_render();
    platform_swap_buffers();

    transientStorage.used = 0;
  }

  platform_destroy_window();
  return 0;
}

void update_game(RenderData *renderDataIn, Input *inputIn) {
  update_game_ptr(renderDataIn, inputIn);
}

void reload_game_DLL(BumpAllocator *transientStorage) {
  static void *gameDLL;
  static long long lastEditTimestampGameDLL;

  long long currentTimestampGameDLL = get_timestamp("game.so");
  if (currentTimestampGameDLL > lastEditTimestampGameDLL) {
    if (gameDLL) {
      bool freeResult = platform_free_dynamic_library(gameDLL);
      gameDLL = nullptr;
      LOG_TRACE("Freed game.dll");
    }
  }
  while (!copy_file("game.so", "game_load.so", transientStorage)) {
    sleep(10);
  }
  LOG_TRACE("Copied game.so into game_load.so");

  update_game_ptr = (update_game_type *)platform_load_dynamic_function(
      gameDLL, "update_game");
  FN_ASSERT(update_game_ptr, "Failed to load update_game function");
  lastEditTimestampGameDLL = currentTimestampGameDLL;
}

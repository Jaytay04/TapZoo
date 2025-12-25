#include "funlib.h"
#include "game.h"
#include "gl_renderer.h"
#include "input.h"
#include "platform.h"

Input input = {};

int main() {
  BumpAllocator transientStorage = Make_Bump_Allocator(MB(50));

  input.screenSizeX = 1200;
  input.screenSizeY = 700;

  if (!platform_create_window(1200, 700, (char *)"Window")) {
    return 1;
  }

  gl_init(&transientStorage);

  while (running) {
    platform_update_window();
    update_game();
    gl_render();
    platform_swap_buffers();
  }

  platform_destroy_window();
  return 0;
}

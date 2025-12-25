#include "funlib.h"
#include "game.h"
#include "gl_renderer.h"
#include "input.h"
#include "platform.h"
#include "render_interface.h"

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
    update_game();
    gl_render();
    platform_swap_buffers();

    transientStorage.used = 0;
  }

  platform_destroy_window();
  return 0;
}

#include "game.h"
#include "assets.h"
#include "render_interface.h"

extern Input *input;
extern RenderData *renderData;

constexpr int WORLD_WIDTH = 320;
constexpr int WORLD_HEIGHT = 180;
constexpr int TILESIZE = 8;
void update_game(GameState *gameStateIn, RenderData *renderDataIn,
                 Input *inputIn) {
  if (renderData != renderDataIn) {
    gameState = gameStateIn;
    renderData = renderDataIn;
    input = inputIn;
  }
  if (!gameState->initialized) {
    renderData->gameCamera.dimensions = {WORLD_WIDTH, WORLD_HEIGHT};
    renderData->gameCamera.position = {0, 0};
    gameState->initialized = true;
  }
  draw_sprite(SPRITE_DICE, {0, 0});
  /*
   */
}

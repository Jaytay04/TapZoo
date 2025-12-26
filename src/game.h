#pragma once
#include "funlib.h"
#include "input.h"
#include "render_interface.h"

// ##############################################################
//                        Game Structs
// ##############################################################
struct GameState {
  bool initialized = false;
  IVec2 playerPos;
};
// ##############################################################
//                        Game Globals
// ##############################################################
extern GameState *gameState;
// ##############################################################
//                   Game Functions (Exposed)
// ##############################################################

extern "C" {
void update_game(GameState *gameStateIn, RenderData *renderDataIn,
                 Input *inputIn);
}

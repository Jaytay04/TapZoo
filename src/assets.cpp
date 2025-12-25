#include "assets.h"
Sprite get_sprite(SpriteID spriteID) {
  Sprite sprite = {};

  switch (spriteID) {

  case SPRITE_DICE: {
    sprite.atlasOffset = {0, 0};
    sprite.spriteSize = {16, 16};
    break;
  }
  case SPRITE_FROG: {
    sprite.atlasOffset = {16, 0};
    sprite.spriteSize = {216, 216};
  }
  case SPRITE_COUNT: {
    break;
  }
  }

  return sprite;
}

#pragma once
#include "assets.h"
#include "funlib.h"

constexpr int MAX_TRANSFORMS = 1000;

struct Transform {
  Vec2 pos;
  Vec2 size;
  IVec2 atlasOffset;
  IVec2 spriteSize;
};

struct RenderData {
  int transformCount;
  Transform transforms[MAX_TRANSFORMS];
};

extern RenderData *renderData;

void draw_sprite(SpriteID spriteID, Vec2 pos, Vec2 size);

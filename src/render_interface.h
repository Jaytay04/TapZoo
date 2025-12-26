#pragma once
#include "assets.h"
#include "funlib.h"

constexpr int MAX_TRANSFORMS = 1000;

struct OrthographicCamera2D {
  float zoom = 1.0f;
  Vec2 dimensions;
  Vec2 position;
};

struct Transform {
  Vec2 pos;
  Vec2 size;
  IVec2 atlasOffset;
  IVec2 spriteSize;
};

struct RenderData {
  OrthographicCamera2D gameCamera;
  OrthographicCamera2D uiCamera;
  int transformCount;
  Transform transforms[MAX_TRANSFORMS];
};

extern RenderData *renderData;

void draw_sprite(SpriteID spriteID, Vec2 pos);

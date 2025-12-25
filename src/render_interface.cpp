#include "render_interface.h"
#include "assets.h"
#include "funlib.h"

RenderData renderData = {};

void draw_sprite(SpriteID spriteID, Vec2 pos, Vec2 size) {
  Sprite sprite = get_sprite(spriteID);

  FN_ASSERT(renderData.transformCount < MAX_TRANSFORMS,
            "MAX_TRANSFORMS exceeded");

  Transform transform = {};
  transform.pos = pos;
  transform.size = size;
  transform.atlasOffset = sprite.atlasOffset;
  transform.spriteSize = sprite.spriteSize;

  renderData.transforms[renderData.transformCount++] = transform;
}

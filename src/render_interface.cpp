#include "render_interface.h"
#include "funlib.h"

void draw_sprite(SpriteID spriteID, Vec2 pos) {
  Sprite sprite = get_sprite(spriteID);

  FN_ASSERT(renderData->transformCount < MAX_TRANSFORMS,
            "MAX_TRANSFORMS exceeded");

  Transform transform = {};
  transform.pos = pos - vec_2(sprite.spriteSize) / 2.0f;
  transform.size = vec_2(sprite.spriteSize);
  transform.atlasOffset = sprite.atlasOffset;
  transform.spriteSize = sprite.spriteSize;

  renderData->transforms[renderData->transformCount++] = transform;
}

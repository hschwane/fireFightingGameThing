/*
 * fireFightingGameThing
 * SpriteRenderer.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the SpriteRenderer class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_SPRITERENDERER_H
#define FIREFIGHTINGGAMETHING_SPRITERENDERER_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

// namespace
//--------------------
namespace SpriteRenderer {
//--------------------

void setView(const glm::mat4& view);
void setProjection(const glm::mat4& proj);
void drawSprite(mpu::gph::Texture& tex, const glm::vec2& size, const glm::vec2& pos, float rotation);

}


#endif //FIREFIGHTINGGAMETHING_SPRITERENDERER_H

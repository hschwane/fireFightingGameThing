/*
 * fireFightingGameThing
 * GameObject.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the GameObject class
 *
 * Copyright (c) 2019 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "GameObject.h"
#include "engine/SpriteRenderer.h"
//--------------------


// function definitions of the GameObject class
//-------------------------------------------------------------------

GameObject::GameObject(std::string texFile, const glm::vec2 &size)
        : m_tex(mpu::gph::TextureFileType::eU8, texFile), m_size(size)
{
}

void GameObject::draw()
{
    SpriteRenderer::drawSprite(m_tex,m_size,m_pos,m_rotation);
}

/*
 * fireFightingGameThing
 * RootedObject.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the RootedObject class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "RootedObject.h"
#include "layer.h"
//--------------------

// function definitions of the RootedObject class
//-------------------------------------------------------------------

void RootedObject::draw(mpu::gph::Renderer2D& renderer) const
{
    renderer.addSprite(m_objectType->getSprite(),glm::translate(glm::vec3(m_rootTile,0)),ROOTED_OBJECT_LAYER);
}

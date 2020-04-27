/*
 * fireFightingGameThing
 * Map.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Map class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "Map.h"
#include "layer.h"
#include "defaultElements.h"
//--------------------

// function definitions of the Map class
//-------------------------------------------------------------------
Map::Map(glm::uvec2 size)
    : m_size(size), m_length(size.x*size.y)
{
    m_tileTypes.resize(m_length, ttNone());
}

void Map::addTilesForRendering(mpu::gph::Renderer2D& renderer)
{
    glm::uvec2 id{0,0};
    for(id.y = 0; id.y<m_size.y; id.y++)
        for(id.x = 0; id.x<m_size.x; id.x++)
        {
            unsigned int memId = getTileId(id);
            renderer.addSprite(m_tileTypes[memId].get().getSprite(), glm::translate(glm::vec3({id, 0})), MAP_LAYER);
        }
}

void Map::setTileType(const glm::uvec2& id, const TileType& type)
{
    m_tileTypes[getTileId(id)] = type;
}

unsigned int Map::getTileId(const glm::uvec2&  id2d)
{
    return id2d.y * m_size.x + id2d.x;
}

glm::uvec2 Map::getTileId2d(uint32_t id)
{
    return glm::uvec2(id%m_size.x,id/m_size.x);
}


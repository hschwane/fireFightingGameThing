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
#include "App.h"
//--------------------

// function definitions of the Map class
//-------------------------------------------------------------------
Map::Map(glm::uvec2 size)
    : m_size(size), m_length(size.x*size.y)
{
    m_tileTypes.resize(m_length, ttNone());
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


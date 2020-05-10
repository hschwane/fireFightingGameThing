/*
 * fireFightingGameThing
 * Map.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "Map.h"
//--------------------

// function definitions of the Map class
//-------------------------------------------------------------------
Map::Map(glm::ivec2 size, const TileType& defaultTile )
        : m_size(size), m_length(size.x*size.y)
{
    m_tileTypes.resize(m_length, defaultTile);
}

void Map::forEachTile(std::function<void(Map&, const glm::ivec2&)> func)
{
    glm::ivec2 id;
    for(id.y = 0; id.y<getSize().y; id.y++)
        for(id.x = 0; id.x<getSize().x; id.x++)
        {
            func(*this,id);
        }
}

void Map::forEachTile(std::function<void(const Map&, const glm::ivec2&)> func) const
{
    glm::ivec2 id;
    for(id.y = 0; id.y<getSize().y; id.y++)
        for(id.x = 0; id.x<getSize().x; id.x++)
        {
            func(*this,id);
        }
}

void Map::forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(Map&, const glm::ivec2&)> func)
{
    glm::ivec2 min = glm::max(tileAtWorld(glm::min(posA,posB)), {0,0});
    glm::ivec2 max = glm::min(tileAtWorld(glm::max(posA,posB)), m_size-glm::ivec2(1,1));

    glm::ivec2 id;
    for(id.y = min.y; id.y<=max.y; id.y++)
        for(id.x = min.x; id.x<=max.x; id.x++)
        {
            func(*this,id);
        }
}

void Map::forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB,
                                   std::function<void(const Map&, const glm::ivec2&)> func) const
{
    glm::ivec2 min = glm::max(tileAtWorld(glm::min(posA,posB)), {0,0});
    glm::ivec2 max = glm::min(tileAtWorld(glm::max(posA,posB)), {0,0}, m_size-glm::ivec2(1,1));

    glm::ivec2 id;
    for(id.y = min.y; id.y<=max.y; id.y++)
        for(id.x = min.x; id.x<=max.x; id.x++)
        {
            func(*this,id);
        }
}

void Map::setTileType(const glm::ivec2& id, const TileType& type)
{
    m_tileTypes[getTileId(id)] = type;
}

unsigned int Map::getTileId(const glm::ivec2&  id2d) const
{
    return id2d.y * m_size.x + id2d.x;
}

glm::ivec2 Map::getTileId2d(uint32_t id) const
{
    return glm::ivec2(id%m_size.x,id/m_size.x);
}

glm::ivec2 Map::tileAtWorld(glm::vec2 position)
{
    return glm::round(position);
}

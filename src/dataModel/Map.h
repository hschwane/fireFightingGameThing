/*
 * fireFightingGameThing
 * Map.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Map class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_MAP_H
#define FIREFIGHTINGGAMETHING_MAP_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
#include "TileType.h"
#include "defaultElements.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class Map
 *
 * The map for one operation area.
 */
class Map
{
public:

    Map(glm::uvec2 size = {10,10}, const TileType& defaultTile = ttNone());

    // iterate
    void forEachTile(std::function<void(Map&, const glm::uvec2&)> func); //!< executes func on every tile of the map
    void forEachTile(std::function<void(const Map&, const glm::uvec2&)> func) const; //!< executes func on every tile of the map
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(Map&, const glm::uvec2&)> func); //!< executes func on every tile of the map
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(const Map&, const glm::uvec2&)> func) const; //!< executes func on every tile of the map

    // changing the map
    void setTileType(const glm::uvec2& id, const TileType& type); //!< set type for tile at id
    const TileType& getTileType(const glm::uvec2& id) const {return m_tileTypes[getTileId(id)];}

    glm::uvec2 getSize() const {return  m_size;} //!< returns size of the map

    static glm::uvec2 tileAtWorld(glm::vec2 position); //!< returns tile id at world position

private:
    // some internal helper functions
    unsigned int getTileId(const glm::uvec2& id2d) const; //!< computes memory location from tile id
    glm::uvec2 getTileId2d(uint32_t id) const; //!< computes 2d id of tile from memory location

    // size of the map
    glm::uvec2 m_size;
    unsigned int m_length;

    // data for every tile
    std::vector<std::reference_wrapper<const TileType>> m_tileTypes;
};

// function definitions of the Map class
//-------------------------------------------------------------------
inline Map::Map(glm::uvec2 size, const TileType& defaultTile )
        : m_size(size), m_length(size.x*size.y)
{
    m_tileTypes.resize(m_length, defaultTile);
}

inline void Map::forEachTile(std::function<void(Map&, const glm::uvec2&)> func)
{
    glm::uvec2 id{0,0};
    for(id.y = 0; id.y<getSize().y; id.y++)
        for(id.x = 0; id.x<getSize().x; id.x++)
        {
            func(*this,id);
        }
}

inline void Map::forEachTile(std::function<void(const Map&, const glm::uvec2&)> func) const
{
    glm::uvec2 id{0,0};
    for(id.y = 0; id.y<getSize().y; id.y++)
        for(id.x = 0; id.x<getSize().x; id.x++)
        {
            func(*this,id);
        }
}

inline void Map::forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(Map&, const glm::uvec2&)> func)
{
    glm::uvec2 min = clamp(tileAtWorld(posA), {0,0}, m_size);
    glm::uvec2 max = clamp(tileAtWorld(posB), {0,0}, m_size);

    glm::uvec2 id{0,0};
    for(id.y = min.x; id.y<max.y; id.y++)
        for(id.x = min.y; id.x<max.x; id.x++)
        {
            func(*this,id);
        }
}

inline void Map::forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB,
                            std::function<void(const Map&, const glm::uvec2&)> func) const
{
    glm::uvec2 min = clamp(glm::uvec2{posA}, {0,0}, m_size);
    glm::uvec2 max = clamp(glm::uvec2{posB}, {0,0}, m_size);

    glm::uvec2 id{0,0};
    for(id.y = min.x; id.y<max.y; id.y++)
        for(id.x = min.y; id.x<max.x; id.x++)
        {
            func(*this,id);
        }
}

inline void Map::setTileType(const glm::uvec2& id, const TileType& type)
{
    m_tileTypes[getTileId(id)] = type;
}

inline unsigned int Map::getTileId(const glm::uvec2&  id2d) const
{
    return id2d.y * m_size.x + id2d.x;
}

inline glm::uvec2 Map::getTileId2d(uint32_t id) const
{
    return glm::uvec2(id%m_size.x,id/m_size.x);
}

inline glm::uvec2 Map::tileAtWorld(glm::vec2 position)
{
    return glm::round(position);
}

#endif //FIREFIGHTINGGAMETHING_MAP_H

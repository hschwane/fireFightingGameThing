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
#include "dataModel/TileType.h"
#include "buildinElements.h"
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

    explicit Map(glm::ivec2 size = {10,10}, const TileType& defaultTile = *noneTile());

    // iterate
    void forEachTile(std::function<void(Map&, const glm::ivec2&)> func); //!< executes func on every tile of the map
    void forEachTile(std::function<void(const Map&, const glm::ivec2&)> func) const; //!< executes func on every tile of the map
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(Map&, const glm::ivec2&)> func); //!< executes func on every tile of the map
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB, std::function<void(const Map&, const glm::ivec2&)> func) const; //!< executes func on every tile of the map

    // changing the map
    void setTileType(const glm::ivec2& id, const TileType& type); //!< set type for tile at id
    const TileType& getTileType(const glm::ivec2& id) const {return m_tileTypes[getTileId(id)];}

    // accessing data at tiles
    glm::ivec2 getSize() const {return  m_size;} //!< returns size of the map
    static glm::ivec2 tileAtWorld(glm::vec2 position); //!< returns tile id at world position

private:
    // some internal helper functions
    unsigned int getTileId(const glm::ivec2& id2d) const; //!< computes memory location from tile id
    glm::ivec2 getTileId2d(uint32_t id) const; //!< computes 2d id of tile from memory location

    // size of the map
    glm::ivec2 m_size;
    unsigned int m_length;

    // data for every tile
    std::vector<std::reference_wrapper<const TileType>> m_tileTypes;
};


#endif //FIREFIGHTINGGAMETHING_MAP_H

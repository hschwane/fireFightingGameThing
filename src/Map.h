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

    Map(glm::uvec2 size = {10,10});

    // changing the map
    void setTileType(const glm::uvec2& id, const TileType& type); //!< set type for tile at id
    const TileType& getTileType(const glm::uvec2& id) {return m_tileTypes[getTileId(id)];}

    glm::uvec2 getSize() const {return  m_size;}

private:
    // some internal helper functions
    unsigned int getTileId(const glm::uvec2& id2d); //!< computes memory location from tile id
    glm::uvec2 getTileId2d(uint32_t id); //!< computes 2d id of tile from memory location

    // size of the map
    glm::uvec2 m_size;
    unsigned int m_length;

    // data for every tile
    std::vector<std::reference_wrapper<const TileType>> m_tileTypes;
};


#endif //FIREFIGHTINGGAMETHING_MAP_H

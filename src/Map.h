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

    Map(glm::uvec2 size, const TileType& defaultTile);
    void addTilesForRendering(mpu::gph::Renderer2D& renderer); //!< adds all tiles of the map to the renderer

    // changing the map
    void setTileType(const glm::uvec2& id, const TileType& type); //!< set type for tile at id

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

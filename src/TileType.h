/*
 * fireFightingGameThing
 * TileType.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the TileType class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_TILETYPE_H
#define FIREFIGHTINGGAMETHING_TILETYPE_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class TileType
 *
 * usage:
 *
 */
class TileType
{
public:
    //!< create a new tile type using a texture sprite
    TileType(std::string refName, mpu::gph::Sprite2D displaySprite)
        : name(std::move(refName)), sprite(std::move(displaySprite)) {}

    // data
    const std::string name;
    const mpu::gph::Sprite2D sprite;
};

#endif //FIREFIGHTINGGAMETHING_TILETYPE_H

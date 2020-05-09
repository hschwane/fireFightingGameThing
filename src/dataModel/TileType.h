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
 * a type of tile used on the map
 *
 */
class TileType
{
public:
    //!< create a new tile type using a texture sprite
    TileType(std::string refName, mpu::gph::Sprite2D displaySprite)
        : m_name(std::move(refName)), m_sprite(std::move(displaySprite)) {}

    //!< loads a tile type from a configuration file
    static TileType loadFromFile(const std::string& file)
    {
        // TODO:fixme
//        mpu::CfgFile cfg(file);
//        std::string name = cfg.getValue<std::string>("Tile","name");
//        std::string spritePath = cfg.getValue<std::string>("Tile","sprite");
//        return TileType(name,mpu::gph::Sprite2D(PROJECT_RESOURCE_PATH"data/core/sprites/"+ spritePath));
    }

    const std::string& getName() const {return m_name;} //!< the name of this tile type in the user interface
    const mpu::gph::Sprite2D& getSprite() const {return m_sprite;} //!< the sprite that this tile uses for rendering

private:
    // data
    std::string m_name;
    mpu::gph::Sprite2D m_sprite;
};

#endif //FIREFIGHTINGGAMETHING_TILETYPE_H

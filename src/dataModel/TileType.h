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
    TileType(std::string refName, std::shared_ptr<mpu::gph::Sprite2D> displaySprite)
        : m_displayName(std::move(refName)), m_spriteResource(std::move(displaySprite))
        {
            assert_critical(m_spriteResource,"TileType", "Constructing TileType from nullptr sprite!");
        }

    const std::string& getName() const {return m_displayName;} //!< the name of this tile type in the user interface
    const mpu::gph::Sprite2D& getSprite() const {return *m_spriteResource;} //!< the sprite that this tile uses for rendering

private:
    std::string m_displayName;
    std::shared_ptr<mpu::gph::Sprite2D> m_spriteResource;
};

//-------------------------------------------------------------------
// helper functions to load and store tiles
/**
 * class TileData
 * @brief stores all data from a .tile file and can read from a string / store into a string
 *          errors during parsing will throw an exception
 */
class TileData
{
public:
    TileData() = default;
    explicit TileData(const std::string& toml);
    toml::value toToml();

    std::string displayName;
    std::string contentPack;
    std::string spriteFilename;
};

#endif //FIREFIGHTINGGAMETHING_TILETYPE_H

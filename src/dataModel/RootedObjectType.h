/*
 * fireFightingGameThing
 * RootedObject.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the RootedObject class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_ROOTEDOBJECTTYPE_H
#define FIREFIGHTINGGAMETHING_ROOTEDOBJECTTYPE_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
//--------------------

//-------------------------------------------------------------------
/**
 * class RootedObjectType
 *
 * Rooted objects are objects pinned to the ground on a certain tile. Only one object is allowed per tile.
 * Objects might burn, open, be moved, be destroyed or change in other ways during the game.
 * RootedObjectType specifies the type of a rooted object, its properties and initial state.
 * RootedObject represents an instance of a RootedObject type and stores the currend state of an object.
 *
 */
class RootedObjectType
{
public:
    //!< create a new rooted object type using a texture sprite
    RootedObjectType(std::string refName, std::shared_ptr<mpu::gph::Sprite2D> displaySprite)
        : m_displayName(std::move(refName)), m_spriteResource(std::move(displaySprite))
    {
        assert_critical(m_spriteResource,"TileType", "Constructing RootedObjectType from nullptr sprite!");
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
 * class RootedObjectData
 * @brief stores all data from a .robj file and can read from a string / store into a string
 *          errors during parsing will throw an exception
 */
class RootedObjectData
{
public:
    RootedObjectData() = default;
    explicit RootedObjectData(const std::string& toml);
    toml::value toToml();

    std::string displayName;
    std::string contentPack;
    std::string spriteFilename;
};

#endif //FIREFIGHTINGGAMETHING_ROOTEDOBJECTTYPE_H

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

#ifndef FIREFIGHTINGGAMETHING_ROOTEDOBJECT_H
#define FIREFIGHTINGGAMETHING_ROOTEDOBJECT_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
#include <memory>
#include <string>
#include "dataModel/RootedObjectType.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class RootedObject
 *
 * Rooted objects are objects pinned to the ground on a certain tile. Only one object is allowed per tile.
 * Objects might burn, open, be moved, be destroyed or change in other ways during the game.
 *
 */
class RootedObject
{
public:
    RootedObject(glm::ivec2 tile, std::shared_ptr<RootedObjectType> type)
        : m_rootTile(tile), m_objectType(type)
    {}

    void draw(mpu::gph::Renderer2D& renderer); //!< draws the object on the screen
    const RootedObjectType& getType() const {return *m_objectType;} //!< access to the object type

private:
    glm::ivec2 m_rootTile; //! the main tile this object is rooted on
    std::shared_ptr<RootedObjectType> m_objectType;
};


#endif //FIREFIGHTINGGAMETHING_ROOTEDOBJECT_H

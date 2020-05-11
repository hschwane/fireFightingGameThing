/*
 * fireFightingGameThing
 * Operation.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Operation class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_OPERATION_H
#define FIREFIGHTINGGAMETHING_OPERATION_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
#include "dataModel/Map.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class Operation
 *
 * An operation is the basic gameplay block of ffgt (like a level). Each operation has a map, characters, missions, etc.
 * In contrast to levels in other games, multiple operations can be active at the same time. The player has
 * to multitask different operations and split the available resources.
 *
 */
class Operation
{
public:

    static std::unique_ptr<Operation> makeDemoOperation();

    void draw(mpu::gph::Renderer2D& renderer);
    void handlePlayerInput();
    void update();

    const Map& getMap() {return m_opArea;} //!< returns map representing the operation area

private:
    std::vector<std::unique_ptr<RootedObject>> m_rootedObjects; //!< holds all rooted objects in the operation area
    std::vector<std::shared_ptr<TileType>> m_usedTileTypes; //!< tile types used by the current map
    Map m_opArea; //!< the operation area

};


#endif //FIREFIGHTINGGAMETHING_OPERATION_H

/*
 * fireFightingGameThing
 * Operation.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the Operation class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "Operation.h"
#include "resourceManagement.h"
#include "rendering/mapRendering.h"
//--------------------

// function definitions of the Operation class
//-------------------------------------------------------------------

std::unique_ptr<Operation> Operation::makeDemoOperation()
{
    std::unique_ptr <Operation> op = std::make_unique<Operation>();

    // load needed tile types
//    op->m_usedTileTypes.emplace_back( getRM().load<TileType>("core/tiles/grass.tile"));
//    op->m_usedTileTypes.emplace_back( getRM().load<TileType>("core/tiles/water.tile"));
//    op->m_usedTileTypes.emplace_back( getRM().load<TileType>("core/tiles/soil.tile"));
//    op->m_usedTileTypes.emplace_back( getRM().load<TileType>("core/tiles/stone.tile"));

    // create a small demo map
//    op->m_opArea = Map({10,10}, *op->m_usedTileTypes[0]);
//    op->m_opArea.setTileType({1,4}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({2,4}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({3,4}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({1,5}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({3,5}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({1,6}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({2,6}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({3,6}, *op->m_usedTileTypes[3]);
//    op->m_opArea.setTileType({4,4}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({5,4}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({6,4}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({4,5}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({5,5}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({6,5}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({4,6}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({5,6}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({6,6}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({4,7}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({5,7}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({6,7}, *op->m_usedTileTypes[2]);
//    op->m_opArea.setTileType({7,4}, *op->m_usedTileTypes[1]);
//    op->m_opArea.setTileType({7,5}, *op->m_usedTileTypes[1]);
//    op->m_opArea.setTileType({7,6}, *op->m_usedTileTypes[1]);
//    op->m_opArea.setTileType({7,7}, *op->m_usedTileTypes[1]);

    // add a tree
//    op->m_rootedObjects.emplace_back( std::make_unique<RootedObject>(
//            glm::uvec2(5,5), std::make_shared<RootedObjectType>("Tree", getRM().load<mpu::gph::Sprite2D>("core/sprites/tree.sprite"))));
//    op->m_opArea.setRootedObject({5,5}, *op->m_rootedObjects[0]);

    return op;
}

void Operation::draw(mpu::gph::Renderer2D& renderer)
{
    drawMap(renderer,m_opArea);
}

void Operation::handlePlayerInput()
{

}

void Operation::update()
{

}

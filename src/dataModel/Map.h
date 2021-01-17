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
#include "gameElements/RootedObject.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class Map
 *
 * The map for one operation area. Handles different types of tiles and stores references to objects on them.
 * This way you can iterate over the map and do things for every tile.
 */
class Map
{
public:
    // construction
    explicit Map(glm::ivec2 size = {10, 10}, const TileType& defaultTile = *noneTile());

    // helper
    static glm::ivec2 tileAtWorld(glm::vec2 position); //!< returns tile id at world position
    bool isValid(glm::ivec2 tile) const; //!< is that index a valid tile?

    // iterate
    void forEachTile(std::function<void(Map&, const glm::ivec2&)> func); //!< executes func on every tile of the map
    void forEachTile(std::function<void(const Map&, const glm::ivec2&)> func) const; //!< executes func on every tile of the map
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB,std::function<void(Map&,const glm::ivec2&)> func); //!< executes func on every tile in the rectangle
    void forEachTileInRect(const glm::vec2& posA, const glm::vec2& posB,std::function<void(const Map&,const glm::ivec2&)> func) const; //!< executes func on every tile in the rectangle

    // changing and reading the map
    void setTile(const glm::ivec2& id, const TileType& type, int variant = 0); //!< set type for tile at id
    const TileType& getTileType(const glm::ivec2& id) const
    {
        return *m_tileTypes[getTileId(id)];
    } //!< returns the tile type at id
    int getTileVariant(const glm::ivec2& id) const
    {
        return m_tileVariants[getTileId(id)];
    }  //!< returns tile variant at id
    void setRootedObject(const glm::ivec2& id,RootedObject& robj); //!< places a rooted object. if an object already exists on that space an error is printed in the log
    void removeRootedObject(const glm::ivec2& id); //!< remove a rooted object from tile id
    RootedObject* getRootedObject(const glm::ivec2& id)
    {
        return m_rootedObjects[getTileId(id)];
    }  //!< access a rooted object on tile id
    const RootedObject* getRootedObject(const glm::ivec2& id) const
    {
        return m_rootedObjects[getTileId(id)];
    }  //!< access a rooted object on tile id

    // map properties
    glm::ivec2 getSize() const { return m_size; } //!< returns size of the map

private:
    // some internal helper functions
    unsigned int getTileId(const glm::ivec2& id2d) const; //!< computes memory location from tile id
    glm::ivec2 getTileId2d(uint32_t id) const; //!< computes 2d id of tile from memory location

    // size of the map
    glm::ivec2 m_size;
    unsigned int m_length;

    // data for every tile
    std::vector<const TileType*> m_tileTypes; //!< every tile has a type
    std::vector<int> m_tileVariants; //!< tiles can have different variations
    std::vector<RootedObject*> m_rootedObjects; //!< every tile can have one or zero rooted object
};


#endif //FIREFIGHTINGGAMETHING_MAP_H

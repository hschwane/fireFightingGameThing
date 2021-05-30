/*
 * fireFightingGameThing
 * defaultElements.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */
#ifndef FIREFIGHTINGGAMETHING_BUILDINELEMENTS_H
#define FIREFIGHTINGGAMETHING_BUILDINELEMENTS_H

// includes
//--------------------
# include "tilemap/TileType.h"
//--------------------

/**
 * @brief none tile is used to define non-rectangular maps, means that ne tile is present at that location
 */
std::shared_ptr<TileType> noneTile();

/**
 * @brief constructs a missing tile. When a tile can not be found on disk the missing tile is
 */
std::unique_ptr<TileType>  makeMissingTile();

#endif //FIREFIGHTINGGAMETHING_BUILDINELEMENTS_H

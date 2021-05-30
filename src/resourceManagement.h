/*
 * fireFightingGameThing
 * resourceManagement.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */
#ifndef FIREFIGHTINGGAMETHING_RESOURCEMANAGEMENT_H
#define FIREFIGHTINGGAMETHING_RESOURCEMANAGEMENT_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
#include "tilemap/TileType.h"
//--------------------

//-------------------------------------------------------------------
// create resources from classes that are part of the data model
using TileRC = mpu::ResourceCache<TileType,TileData>;
std::unique_ptr<TileData> preloadTile(mpu::gph::Sprite2DRC* sprtc, const std::string& data);
std::unique_ptr<TileType> finalLoadTile(std::unique_ptr<TileData> pd);

//-------------------------------------------------------------------
// defining the resource manager
using ResourceManagerType = mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC,TileRC>;
ResourceManagerType& getRM(); //!< returns the resource management system

// instantiate some templates, so they can be linked
//-------------------------------------------------------------------
extern template class mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC,TileRC>;

#endif //FIREFIGHTINGGAMETHING_RESOURCEMANAGEMENT_H

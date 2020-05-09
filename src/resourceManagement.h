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
//--------------------

using ResourceManagerType = mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC>;

ResourceManagerType& getRM(); //!< returns the resource management system

// instantiate some templates, so they can be linked
//-------------------------------------------------------------------
extern template class mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC>;

#endif //FIREFIGHTINGGAMETHING_RESOURCEMANAGEMENT_H

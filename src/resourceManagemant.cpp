/*
 * fireFightingGameThing
 * resourceManagemant.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "resourceManagement.h"
//--------------------

// function definitions
//-------------------------------------------------------------------

ResourceManagerType& getRM()
{
    // pointer to resource caches to resolve recursive dependencies
    static mpu::ImageRC* imgrc = nullptr;

    // construct a resource manager
    static ResourceManagerType resourceManager(
            // add support for images
            {mpu::preloadImage,mpu::finalLoadImage,MPU_LIB_RESOURCE_PATH,
             mpu::getDefaultImage(), "Image-8bit"},
            // add support for sprites
            {[&](const std::string& data){ return mpu::gph::preloadSprite(imgrc,data); },
             mpu::gph::finalLoadSprite2D, MPU_LIB_RESOURCE_PATH,
             mpu::gph::getDefaultSprite(), "Sprite2D"}
             );

    // populate the pointers for dynamic dependencies, only once
    [[maybe_unused]] static bool once = [&]()
            {
                imgrc = &resourceManager.get<mpu::Image8>();
                return true;
            } ();

    return resourceManager;
}

// instantiate some templates, so they can be linked
//-------------------------------------------------------------------
template class mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC>;
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
#include "buildinElements.h"
//--------------------

// function definitions
//-------------------------------------------------------------------
std::unique_ptr<TileData> preloadTile(mpu::gph::Sprite2DRC* sprtc, const std::string& data)
{
    auto tileData = std::make_unique<TileData>(data);
    sprtc->preload(tileData->contentPack + "/sprites/" + tileData->spriteFilename);
    return tileData;
}

std::unique_ptr<TileType> finalLoadTile(mpu::gph::Sprite2DRC* sprtc, std::unique_ptr<TileData> pd)
{
    return std::make_unique<TileType>(pd->displayName, sprtc->load(pd->contentPack + "/sprites/" + pd->spriteFilename) );
}

ResourceManagerType& getRM()
{
    // pointer to resource caches to resolve recursive dependencies
    static mpu::ImageRC* imgrc = nullptr;
    static mpu::gph::Sprite2DRC* sprtrc = nullptr;

    // construct a resource manager
    static ResourceManagerType resourceManager(
            // add support for images
            {mpu::preloadImage,mpu::finalLoadImage,PROJECT_RESOURCE_PATH "data/",
             mpu::getDefaultImage(), "Image-8bit"},
            // add support for sprites
            {[&](const std::string& data){ return mpu::gph::preloadSprite(imgrc,data); },
             mpu::gph::finalLoadSprite2D, PROJECT_RESOURCE_PATH "data/",
             mpu::gph::getDefaultSprite(), "Sprite2D"},
             // add support for tiles
            {[&](const std::string& data){ return preloadTile(sprtrc,data); },
             [&](std::unique_ptr<TileData> data){ return finalLoadTile(sprtrc,std::move(data)); },
             PROJECT_RESOURCE_PATH "data/", makeMissingTile(), "Tile"}
             );

    // populate the pointers for dynamic dependencies, only once
    [[maybe_unused]] static bool once = [&]()
            {
                imgrc = &resourceManager.get<mpu::Image8>();
                sprtrc = &resourceManager.get<mpu::gph::Sprite2D>();
                return true;
            } ();

    return resourceManager;
}

// instantiate some templates, so they can be linked
//-------------------------------------------------------------------
template class mpu::ResourceManager<mpu::ImageRC,mpu::gph::Sprite2DRC,TileRC>;
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
    for(const auto& filename : tileData->spriteFilenames)
        sprtc->preload(tileData->contentPack + "/sprites/" + filename);
    for(const auto& filename : tileData->transitionFilenames)
        sprtc->preload(tileData->contentPack + "/sprites/" + filename);
    return tileData;
}

std::unique_ptr<TileType> finalLoadTile(mpu::gph::Sprite2DRC* sprtc, std::unique_ptr<TileData> pd)
{
    std::vector<std::shared_ptr<mpu::gph::Sprite2D>> spriteVariants;
    std::vector<std::shared_ptr<mpu::gph::Sprite2D>> spriteTransitions;

    for(const auto& filename : pd->spriteFilenames)
        spriteVariants.emplace_back(sprtc->load(pd->contentPack + "/sprites/" + filename));
    for(const auto& filename : pd->transitionFilenames)
        spriteTransitions.emplace_back(sprtc->load(pd->contentPack + "/sprites/" + filename));

    return std::make_unique<TileType>(pd->displayName, spriteVariants, pd->frequencies, spriteTransitions,
                                      pd->precedence);
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

    // populate the pointers for recursive dependencies, only once
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
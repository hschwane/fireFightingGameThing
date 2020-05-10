/*
 * fireFightingGameThing
 * defaultElements.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
# include "buildinElements.h"
//--------------------

std::shared_ptr<TileType> noneTile()
{
    static auto _none_tile = std::make_shared<TileType>("none",
            std::shared_ptr<mpu::gph::Sprite2D>(std::make_shared<mpu::gph::Sprite2D>(PROJECT_RESOURCE_PATH"data/default/none.png")));
    return _none_tile;
}

std::unique_ptr<TileType> makeMissingTile()
{
    return std::make_unique<TileType>("_Tile_missing_",
            std::make_shared<mpu::gph::Sprite2D>(PROJECT_RESOURCE_PATH "/data/default/missingTile.png"));
}

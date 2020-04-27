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
# include "defaultElements.h"
//--------------------

TileType& ttNone()
{
    static TileType _none_tile("none",mpu::gph::Sprite2D(PROJECT_RESOURCE_PATH"data/default/none.png"));
    return _none_tile;
}

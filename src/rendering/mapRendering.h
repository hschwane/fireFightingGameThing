/*
 * fireFightingGameThing
 * mapRendering.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */
#ifndef FIREFIGHTINGGAMETHING_MAPRENDERING_H
#define FIREFIGHTINGGAMETHING_MAPRENDERING_H

// includes
//--------------------
#include <mpUtils/mpUtils.h>
#include <mpUtils/mpGraphics.h>
#include "layer.h"
#include "dataModel/Map.h"
//--------------------

inline void drawMap(mpu::gph::Renderer2D& renderer, const Map& mapToDraw)
{
    mapToDraw.forEachTile([&](const Map& m, const glm::uvec2& id )
    {
        int v = m.getTileVariant(id);
        renderer.addSprite(m.getTileType(id).getSprite(v), glm::translate(glm::vec3({id, 0})), MAP_LAYER);

        const RootedObject* robj = m.getRootedObject(id);
        if(robj && robj->getRootTile() == id)
            robj->draw(renderer);
    });
}

#endif //FIREFIGHTINGGAMETHING_MAPRENDERING_H

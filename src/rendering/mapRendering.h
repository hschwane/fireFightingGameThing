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
#include "tilemap/Map.h"
//--------------------

inline void drawMap(mpu::gph::Renderer2D& renderer, const Map& mapToDraw)
{
    mapToDraw.forEachTile([&](const Map& m, const glm::ivec2& id)
    {
        // draw base sprite
        int variant = m.getTileVariant(id);
        const TileType& tile = m.getTileType(id);
        renderer.addSprite(tile.getSprite(variant), glm::translate(glm::vec3({id, 0})),
                         MAP_LAYER);

        // draw transition sprite
        std::unordered_map<const TileType*, unsigned int> transitions;
        auto checkTransition = [&](int x, int y, unsigned int b)
        {
          glm::ivec2 j(id.x + x, id.y + y);
          if(!m.isValid(j))
              return;

          const TileType* t = &m.getTileType(j);
          if(t->hasTransitions() && t->getPrecedence() > tile.getPrecedence())
              transitions[t] |= (1 << b);
        };

        checkTransition(0, 1, 0);
        checkTransition(-1, 0, 1);
        checkTransition(1, 0, 2);
        checkTransition(0, -1, 3);

        for(const auto& item : transitions)
        {
          float layer = MAP_LAYER - item.first->getPrecedence();
          renderer.addSprite(item.first->getTransition(item.second - 1),
                             glm::translate(glm::vec3({id, 0})), layer);
        }

        // draw rooted object
        const RootedObject* robj = m.getRootedObject(id);
        if(robj && robj->getRootTile() == id)
          robj->draw(renderer);
    });


}

#endif //FIREFIGHTINGGAMETHING_MAPRENDERING_H

/*
 * fireFightingGameThing
 * MapEditorScene.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MapEditorScene class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_MAPEDITORSCENE_H
#define FIREFIGHTINGGAMETHING_MAPEDITORSCENE_H

// includes
//--------------------
#include "dataModel/Map.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class MapEditorScene
 *
 * class used to edit a map
 *
 */
class MapEditorScene : public mpu::gph::Scene
{
public:
    MapEditorScene();
    ~MapEditorScene() override =default;

    void onActivation() override;
    void onDeactivation() override;
    void update() override;
    void draw() override;

private:

    void addKeybindings(); //!< adds keybindings used for the editor

    TileType ttGrass;
    TileType ttConcrete;
    Map activeMap;
    mpu::gph::Camera2D m_camera;

    glm::vec2 selectionStart;
    bool selecting = false;

};


#endif //FIREFIGHTINGGAMETHING_MAPEDITORSCENE_H

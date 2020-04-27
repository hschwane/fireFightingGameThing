/*
 * fireFightingGameThing
 * MapEditor.h
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MapEditor class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

#ifndef FIREFIGHTINGGAMETHING_MAPEDITOR_H
#define FIREFIGHTINGGAMETHING_MAPEDITOR_H

// includes
//--------------------
#include "dataModel/Map.h"
#include "gameState.h"
//--------------------

//-------------------------------------------------------------------
/**
 * class MapEditor
 *
 * class used to edit a map
 *
 */
class MapEditor : public GameStateBase
{
public:
    MapEditor();
    ~MapEditor() override =default;

private:
    void onActivation() override;
    void onDeactivation() override;
    void handleImGui() override;
    void update(MouseController& mouseController) override;
    void draw(mpu::gph::Renderer2D& renderer) override;

private:

    void addKeybindings(); //!< adds keybindings used for the editor

    TileType ttGrass;
    TileType ttConcrete;
    Map activeMap;
    mpu::gph::Camera2D m_camera;

    glm::vec2 selectionStart;
    bool selecting = false;

};


#endif //FIREFIGHTINGGAMETHING_MAPEDITOR_H

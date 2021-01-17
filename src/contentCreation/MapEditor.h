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
#include "resourceManagement.h"
#include <gameElements/RootedObject.h>

#include <random>
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

    void onActivation() override;
    void onDeactivation() override;
    void handleImGui() override;
    void update(MouseController& mc) override;
    void draw(mpu::gph::Renderer2D& renderer, MouseController& mc) override;

private:

    std::unique_ptr<RootedObject> testTree;

    std::vector<std::shared_ptr<TileType>> m_activeTiles;
    int m_selectedTile{0};

    mpu::gph::Sprite2D m_tileSelectionPreview;

    void addKeybindings(); //!< adds keybindings used for the editor

    Map activeMap;
    mpu::gph::Camera2D m_camera;

    glm::vec2 selectionStart;
    bool selecting = false;

    std::default_random_engine rng;
};


#endif //FIREFIGHTINGGAMETHING_MAPEDITOR_H

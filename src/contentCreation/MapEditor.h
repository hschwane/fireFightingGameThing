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
    void update(MouseController& mc) override;
    void draw(mpu::gph::Renderer2D& renderer, MouseController& mc) override;

private:

    std::vector<TileType> m_loadedTiles;
    std::vector<std::reference_wrapper<TileType>> m_activeTiles;
    int m_selectedTile{0};

    mpu::gph::Sprite2D m_tileSelectionPreview;

    void addKeybindings(); //!< adds keybindings used for the editor

    Map activeMap;
    mpu::gph::Camera2D m_camera;

    glm::vec2 selectionStart;
    bool selecting = false;

};


#endif //FIREFIGHTINGGAMETHING_MAPEDITOR_H

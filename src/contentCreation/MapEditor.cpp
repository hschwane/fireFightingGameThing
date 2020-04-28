/*
 * fireFightingGameThing
 * MapEditor.cpp
 *
 * @author: Hendrik Schwanekamp
 * @mail:   hendrik.schwanekamp@gmx.net
 *
 * Implements the MapEditor class
 *
 * Copyright (c) 2020 Hendrik Schwanekamp
 *
 */

// includes
//--------------------
#include "MapEditor.h"
#include "rendering/mapRendering.h"
//--------------------


// function definitions of the MapEditor class
//-------------------------------------------------------------------
MapEditor::MapEditor()
    : m_camera({0,0},1.0,"EditorCamera"),
      ttGrass(TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/grass.cfg")),
      ttConcrete(TileType::loadFromFile(PROJECT_RESOURCE_PATH"data/core/tiles/concrete.cfg"))

{
    // setup input handling
    m_camera.addInputs();
    addKeybindings();
    activeMap = Map({100,100},ttGrass);
}

void MapEditor::onActivation()
{
}

void MapEditor::onDeactivation()
{
}

void MapEditor::handleImGui()
{
}

void MapEditor::update(MouseController& mc)
{
    if(mc.selectionState() == SelectionState::completed)
    {
        activeMap.forEachTileInRect(mc.selctionBeginPos(), mc.selectionEndPos(), [this](Map& map, const glm::uvec2& tile)
        {
            map.setTileType(tile,ttConcrete);
        });
    }

    // add mouse movement to camera and update
    m_camera.moveX(mc.getCameraMovement().x);
    m_camera.moveY(mc.getCameraMovement().y);
    m_camera.update();
}

void MapEditor::draw(mpu::gph::Renderer2D& renderer)
{
    renderer.setView(m_camera.viewMatrix());
    drawMap(renderer,activeMap);
}

void MapEditor::addKeybindings()
{
    using namespace mpu::gph;
    namespace ip = mpu::gph::Input;

    ip::mapScrollToInput("EditorCameraZoom");
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_W,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveDownUp",GLFW_KEY_S,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_D,ip::ButtonBehavior::whenDown,ip::AxisBehavior::positive);
    ip::mapKeyToInput("EditorCameraMoveLeftRight",GLFW_KEY_A,ip::ButtonBehavior::whenDown,ip::AxisBehavior::negative);
}


